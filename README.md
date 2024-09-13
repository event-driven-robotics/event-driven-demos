# iCub Gazebo Simulator

```sh
$ git clone https://github.com/event-driven-robotics/event-driven-demos.git
git checkout tutorials
cd gazebo-docker/ 
docker build -t gazebo:latest
```

```sh
docker images 
docker run -it --name gz --hostname gz --gpus all --network=host -v /tmp/.X11-unix/:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY "${@:3}" "${@}" gazebo:latest
```

```sh
docker exec -it gz bash
yarpserver 
```

```sh
docker exec -it gz bash
yarpmanager 
```

open Tutorial on iCub Gazebo and run all 

```sh
cd /usr/local/src/tutorial_cartesian-interface/build/
./tutorial_cartesian-interface
```