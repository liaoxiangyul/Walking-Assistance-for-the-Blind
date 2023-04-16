#include <iostream>
#include <wiringPiI2C.h>
#include <cmath>
// The default I2C communication address of the BMA220 accelerometer is 0x0a
#define BMA220_ADDR 0x0a
#define SCALE_FACTOR 16384.0f


int main() {
  int fd = wiringPiI2CSetup(BMA220_ADDR);

  if (fd == -1) {
    std::cerr << "Failed to initialize I2C device." << std::endl;
    return 1;
  }

  // Initialize BMA220 sensor,Set to normal mode, output data rate is 100Hz
  wiringPiI2CWriteReg8(fd, 0x0D, 0x10);
  wiringPiI2CWriteReg8(fd, 0x0E, 0x10);

  // Read acceleration values
  while (true) {
    int16_t x = (int16_t)((wiringPiI2CReadReg8(fd, 0x04) << 8) | wiringPiI2CReadReg8(fd, 0x05));
    int16_t y = (int16_t)((wiringPiI2CReadReg8(fd, 0x06) << 8) | wiringPiI2CReadReg8(fd, 0x07));
    int16_t z = (int16_t)((wiringPiI2CReadReg8(fd, 0x08) << 8) | wiringPiI2CReadReg8(fd, 0x09));

  // Convert Data to Gravity Acceleration Units
    float acc_x = static_cast<float>(x) / SCALE_FACTOR;
    float acc_y = static_cast<float>(y) / SCALE_FACTOR;
    float acc_z = static_cast<float>(z) / SCALE_FACTOR;

    std::cout << "Acceleration: x=" << acc_x << "g, y=" << acc_y << "g, z=" << acc_z << "g" << std::endl;

  // Algorithm for judging fall down
    double acceleration = sqrt(pow(acc_x, 2) + pow(acc_y, 2) + pow(acc_z, 2)) - 1;
        if (acceleration > 1.90) {
            std::cout << "Warning! Fall Down Detected！" << std::endl;
            break;
        }
        else {
        std::cout << "NO Fall Down Detected" << std::endl;
  }}

  return 0;
} 
