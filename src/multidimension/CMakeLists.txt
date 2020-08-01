find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_library(ydvr_multidimension SHARED 
  md_oscillator.cc
  md_podvr.cc
  orthogonal_md_dvr.cc
  orthogonal_md_oscillator.cc
  simultaneous_diagonalization.cc
  )
# add_executable(podvr_test.exe podvr_test.cc)
# configure_file(config.hh.in config.hh)
target_include_directories(ydvr_multidimension PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(ydvr_multidimension PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(ydvr_multidimension Eigen3::Eigen)
# target_link_libraries(podvr_test.exe Eigen3::Eigen)
install(TARGETS ydvr_multidimension DESTINATION lib)
# install(FILES .h DESTINATION include)


install(FILES md_oscillator.hh DESTINATION include)
install(FILES md_podvr.hh DESTINATION include)
install(FILES mdindex.hh DESTINATION include)
install(FILES orthogonal_md_dvr.hh DESTINATION include)
install(FILES orthogonal_md_oscillator.hh DESTINATION include)
install(FILES simultaneous_diagonalization.hh DESTINATION include)

# install(FILES ydvr_core.hh DESTINATION include)

