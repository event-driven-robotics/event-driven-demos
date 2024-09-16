# requires minimum cmake version
cmake_minimum_required(VERSION 2.8.9)

# produce the cmake var PROJECT_NAME
project(tutorial_joint)

# mandatory use of these packages
find_package(YARP 3.5.1 REQUIRED)

# position
add_executable(${PROJECT_NAME}-position ${CMAKE_SOURCE_DIR}/src/position.cpp)
target_compile_definitions(${PROJECT_NAME}-position PRIVATE _USE_MATH_DEFINES)
target_link_libraries(${PROJECT_NAME}-position ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME}-position DESTINATION bin)

# positiondirect
add_executable(${PROJECT_NAME}-positiondirect ${CMAKE_SOURCE_DIR}/src/positiondirect.cpp)
target_compile_definitions(${PROJECT_NAME}-positiondirect PRIVATE _USE_MATH_DEFINES)
target_link_libraries(${PROJECT_NAME}-positiondirect ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME}-positiondirect DESTINATION bin)

# velocity
add_executable(${PROJECT_NAME}-velocity ${CMAKE_SOURCE_DIR}/src/velocity.cpp)
target_compile_definitions(${PROJECT_NAME}-velocity PRIVATE _USE_MATH_DEFINES)
target_link_libraries(${PROJECT_NAME}-velocity ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME}-velocity DESTINATION bin)