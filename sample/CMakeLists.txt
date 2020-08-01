include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/src/multidimension")

add_executable(harmonic_test.exe harmonic_test.cc)
target_link_libraries(harmonic_test.exe ydvr)

add_executable(sincdvr_test.exe sincdvr_test.cc)
target_link_libraries(sincdvr_test.exe ydvr)

add_executable(mddvr_test.exe mddvr_test.cc)
target_link_libraries(mddvr_test.exe ydvr)
