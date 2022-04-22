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

#include "module.h"
#include <vector>
using std::vector;

int main(int argc, char * argv[])
{
    /* initialize yarp network */
    yarp::os::Network yarp;
    if(!yarp.checkNetwork()) {
        yError() << "Could not find YARP network";
        return false;
    }

    /* prepare and configure the resource finder */
    yarp::os::ResourceFinder rf;
    rf.setDefaultContext( "eventdriven" );
    rf.setDefaultConfigFile( "vCircleDetector.ini" );
    rf.configure( argc, argv );

    /* create the module */
    detectionManager detector_module;
    return detector_module.runModule(rf);
}

bool detectionManager::configure(yarp::os::ResourceFinder &rf)
{
    setName((rf.check("name", yarp::os::Value("/vCircleDetect")).asString()).c_str());
    if(!rpc_port.open(getName()))
        return false;
    attach(rpc_port);

    //sensory size
    int width = rf.check("width", yarp::os::Value(304)).asInt();
    int height = rf.check("height", yarp::os::Value(240)).asInt();

    int radmin = rf.check("radmin", yarp::os::Value(25)).asInt();
    int radmax = rf.check("radmax", yarp::os::Value(45)).asInt();

    send_response_threshold = rf.check("threshold", yarp::os::Value(0.25)).asDouble();
    active = rf.check("start", yarp::os::Value(true)).asBool();

    for(int r = radmin; r <= radmax; r+=2) {

        detectors.push_back(new circularHoughDetector);
        if(!detectors.back()->initialise(r, 0.42, height, width))
            return false;

    }

    fifoSize = 2 * 2 * radmax * M_PI;

    if(!input_port.open(getName() + "/AE:i"))
        return false;
    if(!debug_port.open(getName() + "/debug:o"))
        return false;
    if(!output_port.open(getName() + "/detection:o"))
        return false;

    return start();
}

bool detectionManager::interruptModule()
{
    input_port.close();
    debug_port.interrupt();
    debug_port.close();
    output_port.interrupt();
    output_port.close();
    vector<circularHoughDetector *>::iterator i;
    for(i = detectors.begin(); i < detectors.end(); i++) {
        (*i)->stop();
    }

    return this->stop();
}

bool detectionManager::updateModule()
{
    return !Thread::isStopping();
}

void detectionManager::run()
{
    vector<ev::AE> q; q.resize(fifoSize);
    yarp::os::Stamp yarp_stamp;
    unsigned int input_q_i = 0, q_i = 0;
    yInfo() << "Waiting for connection";
    ev::packet<ev::AE> *input_q = input_port.read();
    if(!input_q) return;
    yInfo() << "Running!";

    while(!Thread::isStopping()) {

        //get a set of events equal to fifoSize
        while(q_i < fifoSize) {

            if(input_q_i >= input_q->size()) {

                unsigned int upqs = input_port.getPendingReads();
                if(upqs < 1) upqs = 1;
                for(unsigned int i = 0; i < upqs; i++) {
                    input_q = input_port.read();
                    if(!input_q) return;
                }
                input_q_i = 0;

            }

            q[q_i++] = (*input_q)[input_q_i++];

        }

        if(!active) continue;

        vector<circularHoughDetector *>::iterator i;
        for(i = detectors.begin(); i < detectors.end(); i++) {
            (*i)->process(q);
        }

        double max_response = 0;
        vector<circularHoughDetector *>::iterator max_detector = detectors.begin();
        for(i = detectors.begin(); i < detectors.end(); i++) {

            double response = (*i)->waittilldone();
            if(response >= max_response) {
                max_response = response;
                max_detector = i;
            }
        }

        if(max_response > send_response_threshold) {
            yarp::os::Bottle &output_data = output_port.prepare();
            output_data.clear();
            output_data.addVocab(yarp::os::createVocab32('A', 'T', 'T'));
            output_data.addDouble((*max_detector)->x());
            output_data.addDouble((*max_detector)->y());
            output_data.addDouble((*max_detector)->r());
            output_data.addDouble(max_response);
            output_port.write();
        }

        static double prev_time = yarp::os::Time::now();
        double dt = yarp::os::Time::now() - prev_time;
        if( dt > 0.033 && debug_port.getOutputCount()) {

            debug_port.prepare() = (*max_detector)->makeDebugImage();
            debug_port.write();
            prev_time += dt;

        }

        q_i = 0;

    }


}

#define CMD_START yarp::os::createVocab('S', 'T', 'A', 'R')
#define CMD_STOP yarp::os::createVocab('S', 'T', 'O', 'P')

bool detectionManager::respond(const yarp::os::Bottle& command, yarp::os::Bottle& reply)
{

    reply.clear();
    switch(command.get(0).asVocab()) {

    case CMD_START:
        input_port.resume();
        reply.addString("starting detection");
        break;
    case CMD_STOP:
        input_port.interrupt();
        reply.addString("stopping detection");
        break;

    default:
        reply.addString("error. try START or STOP");
        return false;
    }

    return true;

}
