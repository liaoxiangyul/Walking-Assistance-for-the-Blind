cmake_minimum_required(VERSION 3.0)

project(BMA220)


# Add I2C and wringPi library
find_library(I2C_LIB i2c)
find_library(wiringPi_LIB wiringPi)


# executable file
add_executable(BMA220 BMA220.cpp)

# link library
target_link_libraries(BMA220 ${wiringPi_LIB})
