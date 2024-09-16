# iCub Gazebo Simulator

## Docker environment to run iCub in simulation. 

First, please follow the instructions at this [link](https://docs.docker.com/engine/install/) to install Docker on your computer. 

Create the docker image
```sh
$ git clone https://github.com/event-driven-robotics/event-driven-demos.git
git checkout tutorials
cd gazebo-docker/ 
docker build -t gazebo:latest
```

Create a docker container named _gz_
```sh
docker images 
docker run -it --name gz --hostname gz --gpus all --network=host -v /tmp/.X11-unix/:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY "${@:3}" "${@}" gazebo:latest
```

Run yarpserver 
```sh
docker exec -it gz bash
yarpserver 
```
Open a new terminal and run yarpmanager, which will open the relative GUI
```sh
docker exec -it gz bash
yarpmanager 
```

Under Application, open "Tutorial on iCub Gazebo" and run all modules. This should open the Gazebo simulator and all modules should become green colour. The robot is ready to be controlled in the joint and cartesian space. 

## Run the cartesian controller example code:
```sh

cd /usr/local/src/event-driven-demos/tutorial_cartesian/build/
./tutorial_cartesian
```

## Run the joint controllers' examples codes:
```sh

cd /usr/local/src/event-driven-demos/tutorial_joint/build/
./tutorial_joint
```
