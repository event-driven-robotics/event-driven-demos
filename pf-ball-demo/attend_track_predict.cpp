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

#include "attend_track_predict.h"
using namespace yarp::os;

int main(int argc, char * argv[])
{
    /* initialize yarp network */
    yarp::os::Network yarp;
    if(!yarp.checkNetwork()) {
        yError() << "Could not connect to yarp";
        return -1;
    }

    /* prepare and configure the resource finder */
    yarp::os::ResourceFinder rf;
    rf.setDefaultContext( "eventdriven" );
    rf.setDefaultConfigFile( "vATP.ini" );
    rf.configure( argc, argv );

    /* create the module */
    robot_control module;

    /* run the module: runModule() calls configure first and, if successful, it then runs */
    return module.runModule(rf);
}

robot_control::robot_control() {};

bool robot_control::configure(yarp::os::ResourceFinder &rf)
{

    setName(rf.check("name", Value("/vATP")).asString().c_str());

    if(!left_machine.open(getName() + "/left")) {
        yError() << "Could not open left state machine";
        return false;
    }

    if(!right_machine.open(getName() + "/right")) {
        yError() << "Could not open right state machine";
        return false;
    }

    return true;
}

bool robot_control::interruptModule()
{
    left_machine.interrupt();
    right_machine.interrupt();
    return true;
}

//double getPeriod();
bool robot_control::updateModule()
{
    return true;
}



state_machine::state_machine()
{
    start_message.addVocab(createVocab('S', 'T', 'A', 'R'));
    start_message.addInt(0);
    start_message.addInt(0);
    start_message.addInt(0);

    stop_message.addVocab(createVocab('S', 'T', 'O', 'P'));

    machine_state = searching;
}

bool state_machine::open(const std::string &name)
{

    useCallback();
    if(!BufferedPort<Bottle>::open(name + "/message:i")) {
        yError() << "Couldn't open message port";
        return false;
    }

    if(!detector_rpc.open(name + "/detector_commands:o")) {
        yError() << "Couldn't open left detector commands rpc";
        return false;
    }

    if(!tracker_rpc.open(name + "/tracker_commands:o")) {
        yError() << "Couldn't open left tracker commands rpc";
        return false;
    }

    info_prefix = name;

    return true;

}

#define R_ATTEND_POINT createVocab('A', 'T', 'T')
#define R_TRACK_STATUS createVocab('T', '_', 'S', 'T')
#define R_PRED_POINT createVocab('T', 'R', 'A', 'J')

void state_machine::onRead(Bottle &message)
{
    int32_t m_type = message.get(0).asVocab();

    switch(machine_state)
    {

    case(searching):

        if(m_type == R_ATTEND_POINT)
        {
            detector_rpc.write(stop_message);

            start_message.clear();
            start_message.addVocab(createVocab('S', 'T', 'A', 'R'));
            start_message.addInt((int)message.get(1).asDouble());
            start_message.addInt((int)message.get(2).asDouble());
            start_message.addInt((int)message.get(3).asDouble());
            tracker_rpc.write(start_message);

            machine_state = tracking;
            yInfo() << info_prefix << "Attention point found, beginning to track";
            yInfo() << info_prefix << start_message.toString();
        } else {
            yWarning() << info_prefix << "[searching]" << message.toString();
        }

        break;


    case(tracking):

        if(m_type == R_TRACK_STATUS) {
            if(message.get(1).asInt() == 0) {
                //tracking lost
                tracker_rpc.write(stop_message);
                detector_rpc.write(start_message);
                machine_state = searching;
                yInfo() << info_prefix << "Tracking lost, performing detection";

            } else if(message.get(1).asInt() == 1) {
                //tracking started
                //yInfo() << "Tracking Started";
            }
        } else if(m_type == R_PRED_POINT) {
            yInfo() << info_prefix << "Received prediction point";
        } else {
            yWarning() << info_prefix << "[tracking]" << message.toString();
        }

        break;



    default:
        yWarning() << info_prefix << "Machine in unconfigured state";
        break;


    }

}



