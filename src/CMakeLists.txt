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
configure_file(config.h.in config.h)
target_include_directories(ydvr PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(ydvr Eigen3::Eigen)
# target_link_libraries(podvr_test.exe Eigen3::Eigen)
install(TARGETS ydvr DESTINATION lib)
# install(FILES .h DESTINATION include)

install(FILES abstract_representation.h DESTINATION include)
install(FILES dvr.h DESTINATION include)
install(FILES harmonic.h DESTINATION include)
install(FILES log.h DESTINATION include)
install(FILES md_oscillator.h DESTINATION include)
install(FILES md_podvr.h DESTINATION include)
install(FILES mdindex.h DESTINATION include)
install(FILES orthogonal_md_dvr.h DESTINATION include)
install(FILES orthogonal_md_oscillator.h DESTINATION include)
install(FILES oscillator.h DESTINATION include)
install(FILES oscillator_taylor.h DESTINATION include)
install(FILES podvr.h DESTINATION include)
install(FILES representation.h DESTINATION include)
# install(FILES rotation.h DESTINATION include)
install(FILES simultaneous_diagonalization.h DESTINATION include)
install(FILES sincdvr.h DESTINATION include)
install(FILES stationary_state.h DESTINATION include)
install(FILES ydvr.h DESTINATION include)

