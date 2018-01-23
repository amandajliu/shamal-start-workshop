#include <Servo.h>
Servo myservo;
bool locked = true; // keeps track of the state of the lock

void setup() {
  
  myservo.attach(9); // controls the servo with pin 9
  Serial.begin(9600);

}
void loop() {
  changeLock(); // this will call your new function!
}

////// Exercise 1.3 //////
void changeLock() {
  if (locked) { // if locked, then servo should unlock
    // TODO: turn the servo from 0 degrees to 90 degrees. See example Sweep code for hint!
  }
  if (!locked) { // if unlocked, then servo should lock
    // TODO: turn the servo from 90 degrees to 0 degrees. See example Sweep code for hint!
  }
}


