find_package (Eigen3 3.3 REQUIRED NO_MODULE)
# add_library(ydvr SHARED)
set(SCALAR double CACHE STRING "Default yDVR precision")
option(USE_MULTIDIMENSION "Use the multi-dimensional vibration module." ON)

# add_subdirectory(core)


configure_file(config.hh.in config.hh)

# target_include_directories(ydvr PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
# target_link_libraries(ydvr Eigen3::Eigen)

# install(TARGETS ydvr DESTINATION lib)

add_library(ydvr SHARED 
  abstract_representation.cc
  dvr.cc
  harmonic.cc
  log.cc
  oscillator.cc
  oscillator_taylor.cc
  podvr.cc
  representation.cc
  sincdvr.cc
  )
# add_executable(podvr_test.exe podvr_test.cc)
# configure_file(config.hh.in config.hh)
target_include_directories(ydvr PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(ydvr Eigen3::Eigen)
# target_link_libraries(podvr_test.exe Eigen3::Eigen)
install(TARGETS ydvr DESTINATION lib)
# install(FILES .h DESTINATION include)

install(FILES abstract_representation.hh DESTINATION include)
install(FILES dvr.hh DESTINATION include)
install(FILES harmonic.hh DESTINATION include)
install(FILES log.hh DESTINATION include)
install(FILES oscillator.hh DESTINATION include)
install(FILES oscillator_taylor.hh DESTINATION include)
install(FILES podvr.hh DESTINATION include)
install(FILES representation.hh DESTINATION include)
install(FILES sincdvr.hh DESTINATION include)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/config.hh" DESTINATION include)

install(FILES ydvr.hh DESTINATION include)

if(USE_MULTIDIMENSION)
  add_subdirectory(multidimension)
  list(APPEND EXTRA_LIBS multidimension)
endif()
