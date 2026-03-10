cmake_minimum_required(VERSION 4.0)
project(YourProjectName)

find_package(OpenCV REQUIRED)

add_executable(YourExecutableName test.cpp)

target_link_libraries(YourExecutableName PRIVATE ${OpenCV_LIBS})