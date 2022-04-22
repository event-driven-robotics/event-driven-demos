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

// \defgroup Modules Modules
// \defgroup vCircle vCircle
// \ingroup Modules
// \brief detects circles using the Hough transform

#ifndef __VCIRCLEDETECTION__
#define __VCIRCLEDETECTION__

#include <yarp/os/all.h>
#include <event-driven/core.h>
#include <yarp/sig/all.h>
#include <vector>

#include "houghAlgorithm.h"

class detectionManager : public yarp::os::Thread, public yarp::os::RFModule
{
private:

    ev::BufferedPort< ev::AE > input_port;
    yarp::os::BufferedPort<yarp::sig::ImageOf <yarp::sig::PixelBgr> > debug_port;
    yarp::os::BufferedPort<yarp::os::Bottle> output_port;
    yarp::os::RpcServer rpc_port;

    std::vector<circularHoughDetector *> detectors;
    unsigned int fifoSize;
    double send_response_threshold;
    bool active;

    void run();

public:

    detectionManager() {}

    bool configure(yarp::os::ResourceFinder &rf);
    bool updateModule();
    bool interruptModule();
    bool respond(const yarp::os::Bottle& command, yarp::os::Bottle& reply);


};



#endif
