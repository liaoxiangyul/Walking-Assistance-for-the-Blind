# Walking-Assistance-for-the-Blind
The purpose of this project is to make a device that assists the blind to walk. It uses computer vision to identify traffic lights and gives corresponding vibration or sound feedback to inform the traffic lights at the current intersection. The further objective is adding the function of fall detection and alarm.


## 1.Install required libraries

 ### 1.1 OpenCV
 
  #### Step1 Download opencv
 ```cpp
 git clone https://github.com/opencv/opencv.git
 ```
  
 #### Step2 Install related dependencies
  ```cpp
  sudo apt-get install cmake
  sudo apt-get install build-essential libgtk2.0-dev libavcodec-dev libavformat-dev libjpeg-dev libswscale-dev libtiff5-dev
  sudo apt-get install libgtk2.0-dev
  sudo apt-get install pkg-config 
  ```
 #### Step3 Configure the installation path and compile
  ##### Open the path to the OpenCV installation
   ```cpp
   cd /home/team34/opencv
   ```
  ##### Compile
  ```cpp
  mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DOPENCV_GENERATE_PKGCONFIG=ON -DCMAKE_INSTALL_PREFIX=/usr/local ..
sudo make
sudo make install
```
#### Step4 Configure the OpenCV environment
```cpp
cd /etc/ld.so.conf.d/
sudo touch opencv4.conf
sudo sh -c 'echo "/usr/local/lib" > opencv4.conf'
sudo ldconfig
sudo cp -f /usr/local/lib64/pkgconfig/opencv4.pc  /usr/lib/pkgconfig/
```
##### Add environment variables
```cpp
sudo vim /etc/bash.bashrc
sudo apt-get install vim
```
##### Add at the end of the file
```cpp
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib/pkgconfig
export PKG_CONFIG_PATH
```
##### Test
```cpp
pkg-config --modversion opencv4
```
#### Step5 Program run verification
##### This is a program that directly calls the camera and requires an external camera on the Raspberry Pi
```cpp
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main()
{
	VideoCapture cap(0);
	Mat img;
	while (true)
	{
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}
    return 0;
}
```
 ##### Compile
 ```cpp
 cmake .
 make
 ./test
 ```


