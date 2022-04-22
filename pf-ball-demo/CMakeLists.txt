# requires minimum cmake version
cmake_minimum_required(VERSION 3.5)

project(vGazeDemo)

find_package(event-driven REQUIRED)
find_package(YARP REQUIRED COMPONENTS os sig dev math cv)

set(module_name atp)
add_executable(${module_name} attend_track_predict.cpp attend_track_predict.h)
target_link_libraries(${module_name} PRIVATE  YARP::YARP_os
                                              YARP::YARP_init
                                              YARP::YARP_dev
                                              YARP::YARP_math
                                              ev::event-driven)

install(TARGETS ${module_name} DESTINATION ${CMAKE_INSTALL_BINDIR})

set(module_name hough)
add_executable(${module_name} module.cpp houghAlgorithm.cpp module.h houghAlgorithm.h)
target_link_libraries(${module_name} PRIVATE  YARP::YARP_os
                                              YARP::YARP_init
                                              YARP::YARP_dev
                                              YARP::YARP_math
                                              ev::event-driven)

install(TARGETS ${module_name} DESTINATION ${CMAKE_INSTALL_BINDIR})

set(module_name pf)
add_executable(${module_name} vControlLoopDelay.cpp vParticle.cpp vControlLoopDelay.h vParticle.h)
target_link_libraries(${module_name} PRIVATE  YARP::YARP_os
                                              YARP::YARP_init
                                              YARP::YARP_dev
                                              YARP::YARP_math
                                              ev::event-driven)
install(TARGETS ${module_name} DESTINATION ${CMAKE_INSTALL_BINDIR})

set(module_name gazeControl)
add_executable(${module_name} vTrackToRobot.cpp vTrackToRobot.h)
target_link_libraries(${module_name} PRIVATE  YARP::YARP_os
                                              YARP::YARP_init
                                              YARP::YARP_dev
                                              YARP::YARP_math
                                              ev::event-driven)
install(TARGETS ${module_name} DESTINATION ${CMAKE_INSTALL_BINDIR})
