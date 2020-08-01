find_package (Eigen3 3.3 REQUIRED NO_MODULE)
aux_source_directory(. DIR_MULTIDIMENSION_SRC)
add_library(multidimension ${DIR_MULTIDIMENSION_SRC})
# add_executable(podvr_test.exe podvr_test.cc)
# configure_file(config.hh.in config.hh)
target_include_directories(multidimension PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(multidimension PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(multidimension Eigen3::Eigen)

# target_link_libraries(podvr_test.exe Eigen3::Eigen)
# install(TARGETS ydvr_multidimension DESTINATION lib)
# install(FILES .h DESTINATION include)

install(FILES md_oscillator.hh DESTINATION include/multidimension)
install(FILES md_podvr.hh DESTINATION include/multidimension)
install(FILES mdindex.hh DESTINATION include/multidimension)
install(FILES orthogonal_md_dvr.hh DESTINATION include/multidimension)
install(FILES orthogonal_md_oscillator.hh DESTINATION include/multidimension)
install(FILES simultaneous_diagonalization.hh DESTINATION include/multidimension)

# install(FILES ydvr_core.hh DESTINATION include)

