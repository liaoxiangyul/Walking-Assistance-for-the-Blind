cmake_minimum_required(VERSION 3.0)

project(button)


# Add wringPi library

find_library(wiringPi_LIB wiringPi)


# executable file
add_executable(button button.cpp)

# link library
target_link_libraries(button ${wiringPi_LIB})
