cmake_minimum_required(VERSION 2.8.3)
project(minoru_driver)
find_package(catkin REQUIRED COMPONENTS
	roscpp
	std_msgs
	sensor_msgs)

# Dependencies - OpenCV:
find_package(OpenCV REQUIRED)
link_directories(${OpenCV_LIBRARY_DIRS})

catkin_package()

include_directories(${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

add_executable(minoru_driver src/minoru_driver.cpp)
target_link_libraries(minoru_driver ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
