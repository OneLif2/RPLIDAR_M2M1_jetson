cmake_minimum_required(VERSION 3.4...3.18)
project(mapdemo)
message(STATUS "CMAKE_PROJECT_NAME" "${CMAKE_PROJECT_NAME}")

message(STATUS "PROJECT_SOURCE_DIR" "${PROJECT_SOURCE_DIR}")

add_subdirectory(pybind11)
set(MAIN_DIR "${PROJECT_SOURCE_DIR}/slamware_sdk_linux-aarch64-gcc7/samples/mapdemo/src")
set(SLAM_DIR "${PROJECT_SOURCE_DIR}/slamware_sdk_linux-aarch64-gcc7/linux-aarch64-release/include")

message(STATUS "MAIN_DIR = " "${MAIN_DIR}")
message(STATUS "python include dirs " "${PYTHON_INCLUDE_DIRS}")
message(STATUS "SLAM_DIR = " "${SLAM_DIR}")

message(STATUS "define include dir path")
add_subdirectory(slamware_sdk_linux-aarch64-gcc7/linux-aarch64-release) #go to this dir find CMakeLists.txt
message(STATUS "define library dir path")
link_directories(slamware_sdk_linux-aarch64-gcc7/linux-aarch64-release/lib) #go to lib find lib
message(STATUS "build importable .so file")
pybind11_add_module(mapdemo ${MAIN_DIR}/main_pybind11.cpp)

message(STATUS "link library dir to mapdemo")
target_link_libraries(mapdemo PRIVATE slamware_core_platform)
message(STATUS "link library file to mapdemo according to Makefile")
target_link_libraries(mapdemo PUBLIC stdc++ dl z rt m pthread rpos_robotplatforms_rpslamware rpos_framework boost_atomic boost_chrono boost_date_time boost_regex boost_system boost_thread boost_filesystem boost_random base64 jsoncpp rlelib crypto curl ssl)
