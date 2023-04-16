#include <iostream>
#include <wiringPi.h>

// Define button pins, abortdjust according to actual wiring
#define BUTTON_PIN 4

// Button state enum
enum ButtonState {
    IDLE,
    PRESSED,
    HELD
};

// button state variable
volatile ButtonState buttonState = IDLE;
volatile unsigned long buttonHoldStartTime = 0;

// Button interrupt callback function
void buttonInterrupt() {
    if (digitalRead(BUTTON_PIN) == HIGH) {
        // button pressed
        buttonState = PRESSED;
        buttonHoldStartTime = millis();
    } else {
        // button release
        buttonState = IDLE;
    }
}

int main() {
    // Initialize the WiringPi library
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi." << std::endl;
        return 1;
    }

    // Set button pin to input mode and enable pull-down resistor
    pinMode(BUTTON_PIN, INPUT);
    pullUpDnControl(BUTTON_PIN, PUD_DOWN);

    // Register button interrupt callback function
    wiringPiISR(BUTTON_PIN, INT_EDGE_BOTH, buttonInterrupt);

    // main loop
    while (true) {
        if (buttonState == PRESSED && millis() - buttonHoldStartTime >= 3000) {
            // Press and hold the button for more than 3 seconds
            std::cout << "Restarting program..." << std::endl;
			// run restart script
            system("sudo sh /home/team34/final/restart_program.sh");
            break;
        }
       
    }

    return 0;
}