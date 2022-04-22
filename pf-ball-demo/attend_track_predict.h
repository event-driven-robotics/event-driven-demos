/*
 *   Copyright (C) 2018 Event-driven Perception for Robotics
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

#ifndef _ICUBATPSTATEMACHINE_
#define _ICUBATPSTATEMACHINE_

#include "yarp/os/all.h"


class state_machine : public yarp::os::BufferedPort<yarp::os::Bottle> {

protected:

    enum states {
        initialise,
        searching,
        tracking
    };

    std::string info_prefix;
    yarp::os::Bottle start_message;
    yarp::os::Bottle stop_message;

    states machine_state;

    yarp::os::RpcClient detector_rpc;
    yarp::os::RpcClient tracker_rpc;

public:

    state_machine();
    void onRead(yarp::os::Bottle &message);
    bool open(const std::string &name);

};

class robot_control : public yarp::os::RFModule
{

protected:

    state_machine left_machine;
    state_machine right_machine;

public:

    robot_control();
    bool configure(yarp::os::ResourceFinder &rf);
    bool interruptModule();
    bool updateModule();

};

#endif
