cmake_minimum_required(VERSION 3.0.2)
project(obstacle_avoidance)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

add_executable(${PROJECT_NAME}_node src/obstacle_avoid.cpp)

add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

 target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
 )
