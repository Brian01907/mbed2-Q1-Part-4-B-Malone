#include <stdio.h>
#include "mbed.h"

DigitalIn button(BUTTON1);
volatile bool buttonPressed = false;  // Flag to indicate 
Mutex buttonMutex; 

void button_isr() {
    buttonMutex.lock();  // Acquire
    buttonPressed = true;  // Set the
    buttonMutex.unlock();  // Release 
}

int main() {
    button.rise(&button_isr);

    while (1) {
        buttonMutex.lock();  // Acquire
        if (buttonPressed) {
            printf("Button pressed\n");
            buttonPressed = false;  // Reset
        }
        buttonMutex.unlock();  // Release
    }
}

