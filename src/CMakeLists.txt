find_package (Eigen3 3.3 REQUIRED NO_MODULE)
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
  simultaneous_diagonalization.cc
  # rotation.cc
  sincdvr.cc
  ydvr.cc
  )
# add_executable(podvr_test.exe podvr_test.cc)
configure_file(config.hh.in config.hh)
target_include_directories(ydvr PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(ydvr Eigen3::Eigen)
# target_link_libraries(podvr_test.exe Eigen3::Eigen)
install(TARGETS ydvr DESTINATION lib)
# install(FILES .h DESTINATION include)

install(FILES abstract_representation.hh DESTINATION include)
install(FILES dvr.hh DESTINATION include)
install(FILES harmonic.hh DESTINATION include)
install(FILES log.hh DESTINATION include)
install(FILES md_oscillator.hh DESTINATION include)
install(FILES md_podvr.hh DESTINATION include)
install(FILES mdindex.hh DESTINATION include)
install(FILES orthogonal_md_dvr.hh DESTINATION include)
install(FILES orthogonal_md_oscillator.hh DESTINATION include)
install(FILES oscillator.hh DESTINATION include)
install(FILES oscillator_taylor.hh DESTINATION include)
install(FILES podvr.hh DESTINATION include)
install(FILES representation.hh DESTINATION include)
# install(FILES rotation.hh DESTINATION include)
install(FILES simultaneous_diagonalization.hh DESTINATION include)
install(FILES sincdvr.hh DESTINATION include)
install(FILES stationary_state.hh DESTINATION include)
install(FILES ydvr.hh DESTINATION include)

