/*
 *   Copyright (C) 2017 Event-driven Perception for Robotics
 *   Author: arren.glover@iit.it
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __VHOUGH__
#define __VHOUGH__

#include <yarp/sig/all.h>
#include <event-driven/core.h>
#include <vector>

class circularHoughDetector : public yarp::os::Thread
{

private:

    //data
    yarp::sig::ImageOf<yarp::sig::PixelInt> H;
    yarp::sig::ImageOf<yarp::sig::PixelMono> duplicate_check;
    int xlim;
    int ylim;
    typedef struct { int x; int y;} pixel;
    std::vector<pixel> pixel_offsets;
    pixel max_response;
    int radius;
    unsigned int perimeter;
    double inv_perimeter;

    std::mutex processing; /// for thread safety when starting computation
    std::mutex done;

    //current data
    std::vector<ev::AE> *q; /// pointer to list of events to add to Hough space

    /// update the Hough space given adds and subs
    void performHough();

    /// calls performHough in separate thread
    void run();
    void onStop();

public:

    circularHoughDetector();

    bool initialise(double radius, double thickness, int height, int width);

    void process(std::vector<ev::AE> &q);
    double waittilldone();
    int x();
    int y();
    int r();


    yarp::sig::ImageOf<yarp::sig::PixelBgr> makeDebugImage();

};


#endif
