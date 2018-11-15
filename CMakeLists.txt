# cmake needs this line
cmake_minimum_required(VERSION 2.8)

# Define project name
project(image-visualiser )


include_directories( ${PROJECT_SOURCE_DIR}/include )
include_directories( ${DOCTEST_DIR} )

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/ImageVisualiser.cpp
)

set (TESTS_SOURCE_FILES
)

add_library(image-visualiser SHARED ${SOURCE_FILES})

add_executable(image-visualiser-tests ./tests/main_dummy.cpp  ${TESTS_SOURCE_FILES})
target_link_libraries(image-visualiser-tests image-visualiser ${OpenCV_LIBS} ${Boost_LIBRARIES})

