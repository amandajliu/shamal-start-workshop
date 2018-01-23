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
    for (int pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if (!locked) { // if unlocked, then servo should lock
    for (int pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}


