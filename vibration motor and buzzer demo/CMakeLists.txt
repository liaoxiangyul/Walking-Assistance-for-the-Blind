cmake_minimum_required(VERSION 2.6)
project(motorbuzzer)

# Add  wringPi library
find_library(wiringPi_LIB wiringPi)

# executable file
add_executable(motorbuzzer motorbuzzer.cpp)

# link library
target_link_libraries(motorbuzzer ${wiringPi_LIB})
