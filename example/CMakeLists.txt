cmake_minimum_required(VERSION 2.8)

project(image-visualiser-example)

add_executable(image-visualiser-example ${PROJECT_SOURCE_DIR}/src/main_example.cpp)

file(COPY ${PROJECT_SOURCE_DIR}/test.png DESTINATION ./)

target_link_libraries(image-visualiser-example image-visualiser ${OpenCV_LIBS})
