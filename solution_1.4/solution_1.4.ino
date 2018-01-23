#include <Servo.h>
Servo myservo;
bool locked = true; // keeps track of the state of the lock
String guess; // stores the user's guess
String code = "1257"; // the correct password

void setup() {

  myservo.attach(9); // controls the servo with pin 9
  Serial.begin(9600);

}
void loop() {
  while (Serial.available()) {
    char c = Serial.read(); // reads each character from Serial one at a time
    guess += c; // add the character to our total input guess so far
    if (c == '\n') { // \n is a line break, so the user has finished entering a guess
      guess.trim(); 
      if (guess.length() > 0) {
        if (guess == code) { // check if the guess is the correct password!

          /////// Exercise 1.4 /////////
          locked = !locked;
          changeLock();
      }
      guess = ""; // clear guess
    }
  }
}

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


