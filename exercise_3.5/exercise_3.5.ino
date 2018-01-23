#include <Servo.h>
Servo myservo;
bool locked = true;
String guess; // stores the user's guess
String code = "1257";

int cathodes[3] = { 2, 3, 4 };
int anodes[3] = { 7, 6, 5 };
// 2-dimensional array of pixels:
int pixels[3][3] = {
  {HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH}
};

void setup() {
  myservo.attach(9);

  Serial.begin(9600);
  for (int thisPin = 0; thisPin < 3; thisPin++) {
    // initialize the output pins:
    pinMode(anodes[thisPin], OUTPUT);
    pinMode(cathodes[thisPin], OUTPUT);
    // take the row pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(cathodes[thisPin], HIGH);
  }
}

void loop() {
  /////// Exercise 3.5 ////////
  // use one of our functions to update the LEDs here
  
  while (Serial.available()) {
    char c = Serial.read(); // reads each character from Serial one at a time
    int c_int = c - '0'; // converts the character into an integer

    /////// Exercise 3.5 ////////
    // c_int is the integer of the checkbox that was clicked
    // use c_int to turn on the correct LED (hint: use one of the functions below!)
    /////////////////////////////

    guess += c; // add the character to our total input guess so far
    if (c == '\n') { // \n is a line break, so the user has finished entering a guess
      guess.trim(); // removes white space
      if (guess.length() > 0) {
        if (guess == code) { // check if the guess is the correct password!
          locked = !locked;
          changeLock();
        }
      }
      guess = ""; // clear guess

    }
  }
}

void refreshScreen() {
  //  iterate over the cols (anodes):
  for (int thisCol = 0; thisCol < 3; thisCol++) {
    // take the col pin (anode) high:
    digitalWrite(anodes[thisCol], HIGH);
    // iterate over the rows (cathodes):
    for (int thisRow = 0; thisRow < 3; thisRow++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the col is HIGH and the row is LOW, // the LED where they meet turns on:
      digitalWrite(cathodes[thisRow], thisPixel);
      if (thisPixel == LOW) {
        digitalWrite(cathodes[thisRow], HIGH);
      }
    }
    // take the col pin low to turn off the whole row:
    digitalWrite(anodes[thisCol], LOW);
  }
}

void changeLock() {
  if (locked) {
    for (int pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if (!locked) {
    for (int pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}

void convertIndexToLED(int i) {
  int col = i % 3;
  int row = i / 3;

  pixels[col][row] = LOW;
  refreshScreen();
}


