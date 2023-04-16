cmake_minimum_required(VERSION 2.6)
project(final)

#Compile according to the rules of the C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add I2C, wringPi, OpenCV, Threads library
find_package(OpenCV REQUIRED)
find_library(I2C_LIB i2c)
find_library(wiringPi_LIB wiringPi)
find_package(Threads)

# executable file
add_executable(final final.cpp)

# link library
target_link_libraries(final ${OpenCV_LIBS} ${wiringPi_LIB} ${CMAKE_THREAD_LIBS_INIT})

