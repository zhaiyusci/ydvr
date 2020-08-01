cmake_minimum_required(VERSION 3.10)

project(yDVR
  VERSION 2.2.0
  DESCRIPTION "A nuclear motion quantum mechanics solver written in C++"
  LANGUAGES CXX
  )

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_EXTENSION OFF)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(doc)
  else()
    message(STATUS "Doxygen not found, not building doc")
  endif()
endif()

add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  add_subdirectory(test)
endif()
# target_include_directories(ydvr PUBLIC "${PROJECT_BINARY_DIR}")
add_subdirectory(sample)

# install(TARGETS ydvr DESTINATION lib)
# install(FILES "${PROJECT_BINARY_DIR}/*.h" DESTINATION include)


