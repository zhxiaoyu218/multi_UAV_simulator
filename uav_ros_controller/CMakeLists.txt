
cmake_minimum_required(VERSION 2.8.3)
project(uav_ros_controller)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  actionlib
  roscpp
  rospy
  std_msgs
)

## Generate messages in the 'msg' folder

# add_message_files(
#   FILES
# 	twist.msg
# )
# generate_messages(DEPENDENCIES gazebo_ros)

# add_message_files(
# 	FILES
# 	Vel.msg
# )

# generate_messages(
# 	DEPENDENCIES;
# 	std_msgs;
# )


catkin_package()

# include_directories(
# # include
#   ${catkin_INCLUDE_DIRS}
# )

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/project590.cpp
# )



add_executable(uav_controller src/uav_controller.cpp)
target_link_libraries(uav_controller ${catkin_LIBRARIES})
add_dependencies(uav_controller ${catkin_EXPORTED_TARGETS})

