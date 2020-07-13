cmake_minimum_required(VERSION 3.1.0)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
project(yDVR VERSION 2.1)
add_library(ydvr SHARED 
abstract_representation.cc
dvr.cc
harmonic.cc
log.cc
md_oscillator.cc
md_podvr.cc
orthogonal_md_dvr.cc
orthogonal_md_oscillator.cc
oscillator.cc
oscillator_taylor.cc
podvr.cc
representation.cc
# rotation.cc
sincdvr.cc
ydvr.cc
  )
# add_executable(podvr_test.exe podvr_test.cc)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)
configure_file(config.h.in config.h)
target_include_directories(ydvr PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(ydvr Eigen3::Eigen)
# target_link_libraries(podvr_test.exe Eigen3::Eigen)
