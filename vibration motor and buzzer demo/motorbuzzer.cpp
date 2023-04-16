#include <stdio.h> 
#include <iostream>
#include <wiringPi.h>


// Define BUZZER and VIBRATION_MOTOR_PIN pins, abortdjust according to actual wiring
#define VIBRATION_MOTOR_PIN 1
#define BUZZER 24

int main()
{
    // Initialize the WiringPi library
    wiringPiSetup();  
    // Set the pin to output mode
    pinMode(VIBRATION_MOTOR_PIN, OUTPUT);  
    pinMode(BUZZER, OUTPUT);
    
    std::cout << "Starting vibration motor program..." << std::endl;

    while (true)
    {
        std::cout << "Turning on vibration motor..." << std::endl;
		
		// vibration motor high level vibration
        digitalWrite(VIBRATION_MOTOR_PIN,HIGH); 
		
		// The buzzer sounds at a low level
        digitalWrite(BUZZER,LOW);
        
		delay(3000);  

        std::cout << "Turning off vibration motor..." << std::endl;
		// stop vibrating
        digitalWrite(VIBRATION_MOTOR_PIN,LOW);  
		// stop sounding
        digitalWrite(BUZZER,HIGH);
        delay(3000);  
    }

    return 0;
}
