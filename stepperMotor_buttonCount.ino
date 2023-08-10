#include <AccelStepper.h>

const int motorInterfaceType = 1;
AccelStepper stepper(motorInterfaceType, 5, 6);

const int buttonPin = 2; 
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int buttonPressCount = 0;

void setup() {
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
  
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == LOW) {
        buttonPressCount++;
        
        if (buttonPressCount == 1) {
          rotateClockwise();
        } else if (buttonPressCount == 2) {
          rotateCounterclockwise();
        }
      }
    }
  }
  
  if (buttonState == HIGH) {
    buttonPressCount = 0;
    stepper.stop();
    stepper.setCurrentPosition(0);
  }
  
  lastButtonState = reading;
}

void rotateClockwise() {
  stepper.moveTo(360);
  stepper.run();
}

void rotateCounterclockwise() {
  stepper.moveTo(-360);
  stepper.run();
}
