project(PointClout_align)
cmake_minimum_required(VERSION 3.10)

add_definitions(-w)

find_package(PCL 1.7 REQUIRED)
include_directories(
    include
    ${PCL_INCLUDE_DIRS}
)
 
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


add_executable(pointcloud_r  node.cpp)
target_link_libraries(pointcloud_r ${PCL_LIBRARIES})
