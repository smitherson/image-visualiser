cmake_minimum_required(VERSION 2.8)

project(image-visualiser )

find_package(OpenCV REQUIRED)

include_directories( ${PROJECT_SOURCE_DIR}/include )

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/ImageVisualiser.cpp
)

add_library(image-visualiser SHARED ${SOURCE_FILES})

add_subdirectory(${PROJECT_SOURCE_DIR}/example/)  

#Tests empty for now
include_directories( ${DOCTEST_DIR} )
if (DOCTEST_DIR)
  set (TESTS_SOURCE_FILES
  )
  add_executable(image-visualiser-tests ./tests/main_dummy.cpp  ${TESTS_SOURCE_FILES})
  target_link_libraries(image-visualiser-tests image-visualiser ${OpenCV_LIBS} ${Boost_LIBRARIES})
endif()
