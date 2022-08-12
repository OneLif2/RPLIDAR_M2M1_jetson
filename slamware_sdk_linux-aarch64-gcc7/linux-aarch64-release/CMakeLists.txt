message(STATUS "SLAM_DIR = " "${SLAM_DIR}")

add_library(slamware_core_platform ${SLAM_DIR} )
target_include_directories(slamware_core_platform PUBLIC include)
set_target_properties(slamware_core_platform PROPERTIES LINKER_LANGUAGE CXX)