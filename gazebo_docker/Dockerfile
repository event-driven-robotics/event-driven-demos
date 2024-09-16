ARG FROM=eventdrivenrobotics/yarp:jammy_v3.7.2

FROM $FROM

ARG SOURCE_FOLDER=/usr/local/src
ARG GAZEBO_YARP_PLUGINS_BRANCH=v4.5.2
ARG ICUB_MAIN_VERSION=v2.0.2
ARG ICUB_MODELS_VERSION=v1.26.0

RUN apt update && \
	apt install -y \
	curl \
	git \
	gnupg2 \
     coinor-libipopt-dev \
     openssh-server \
     openssh-client \
     libtinyxml-dev \
     && apt-get autoremove \
     && apt-get clean \
     && rm -rf /tmp/* /var/lib/apt/lists/* /var/tmp/*

RUN cd $SOURCE_FOLDER/yarp/build && cmake .. && make -j `nproc` install

RUN curl -sSL http://get.gazebosim.org | sh

RUN cd $SOURCE_FOLDER && \
     git clone https://github.com/robotology/icub-main.git && \
     cd icub-main && \
     git checkout $ICUB_MAIN_VERSION && \
     mkdir build && \
     cd build/ && \
     cmake .. -DENABLE_icubmod_cartesiancontrollerclient=ON \
              -DENABLE_icubmod_cartesiancontrollerserver=ON \
              -DENABLE_icubmod_gazecontrollerclient=ON && \
     make -j `nproc` install

RUN cd $SOURCE_FOLDER && \
     git clone https://github.com/robotology/gazebo-yarp-plugins.git && \
     cd gazebo-yarp-plugins && \
     git checkout $GAZEBO_YARP_PLUGINS_BRANCH && \
     mkdir build && \
     cd build/ && \
     cmake .. && \
     make -j `nproc` install

RUN cd $SOURCE_FOLDER && \
     git clone https://github.com/robotology/icub-models.git && \
     cd icub-models && \
     git checkout $ICUB_MODELS_VERSION && \
     mkdir build && \
     cd build/ && \
     cmake .. && \
     make -j `nproc` install

RUN cd $SOURCE_FOLDER && \
     git clone https://github.com/event-driven-robotics/event-driven-demos.git && \
     cd tutorial_cartesian-interface && \
     mkdir build && \
     cd build/ && \
     cmake .. \
     make -j `nproc` install
     
RUN cd $SOURCE_FOLDER && \
     cd tutorial_joint-interface && \
     mkdir build && \
     cd build/ && \
     cmake .. \
     make -j `nproc` install

COPY models /usr/local/share/models
COPY worlds /usr/local/share/worlds
ENV GAZEBO_MODEL_PATH /usr/local/share/iCub/robots/:/usr/local/share/:/usr/local/share/models
ENV GAZEBO_PLUGIN_PATH /usr/local/lib

COPY iCubGazeboControl.xml /usr/local/share/yarp/applications/
