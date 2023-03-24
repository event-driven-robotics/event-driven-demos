#!/bin/bash
echo "Killing all HPE tasks"
echo "======================="
killall python3
echo "Killed MoveEnet"
killall edpr-hpe
echo "Killed EDPR HPE app"
killall atis-bridge-sdk
echo "ATIS-bridge killed"
killall yarpserver
echo "YARP server killed"
