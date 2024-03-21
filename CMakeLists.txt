cmake_minimum_required(VERSION 3.12)

project(image-visualiser VERSION 1.0.0
 DESCRIPTION "badly written image inspector for opencv debugging"
 LANGUAGES CXX)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV Include: ${OpenCV_INCLUDE_DIRS}")

#include_directories( ${PROJECT_SOURCE_DIR}/include )

add_library(image-visualiser SHARED  ${PROJECT_SOURCE_DIR}/src/ImageVisualiser.cpp)

target_include_directories(image-visualiser 
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
   
        ${OpenCV_INCLUDE_DIRS}
    PRIVATE
)


add_subdirectory(${PROJECT_SOURCE_DIR}/example/)  

#Tests empty for now
include_directories( ${DOCTEST_DIR} )
if (DOCTEST_DIR)
  set (TESTS_SOURCE_FILES
  )
  add_executable(image-visualiser-tests ./tests/main_dummy.cpp  ${TESTS_SOURCE_FILES})
  target_link_libraries(image-visualiser-tests image-visualiser ${OpenCV_LIBS} ${Boost_LIBRARIES})
endif()
