// Nerf target practice timer

#include "pitches.h"
#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS3231.h>

#define BUZZER_PIN 4
#define NUM_NOTES 3
#define BUTTON_PIN 2

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// state if timer is running
int timerRunning = 0;

// used to find difference in start and end time
unsigned long startTime;
unsigned long elapsedTime;

// Input state managers
int input_cur = 1;
int input_pas = 1;

void setup() {

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Top: 16.15 s");

  Serial.begin(9600); // serial monitor output

  pinMode(BUTTON_PIN, INPUT_PULLUP); // change the pin mode of the button
}
 
void loop() {

  // Manage button pressed states, this is used to record a difference in input to judge if state has changed
  if(digitalRead(BUTTON_PIN) == 0) {
    input_pas = input_cur;
    input_cur = 0;
  } else {
    input_pas = input_cur;
    input_cur = 1;
  }

  // If the button has been pressed and the timer isn't running
  if((input_cur == 0 && input_pas == 1) && (timerRunning == 0)) {
    
    lcd.setCursor(0, 1);
    lcd.print("          ");
    
    startMusic();

    startTime = millis();
    timerRunning = 1;
  } else if((input_cur == 0 && input_pas == 1) && (timerRunning == 1)) { // If the button has been pressed and the timer is already running
    timerRunning = 0;

    lcd.setCursor(0, 1);
    lcd.print("          ");
    lcd.setCursor(0, 1);
    lcd.print(((elapsedTime - startTime) / float(1000))); lcd.print(" s");

    endMusic();
  }

  // While the timer is running update the elapsed time and show it to the screen
  if(timerRunning == 1){
    lcd.setCursor(0, 1);
    elapsedTime = millis();
    lcd.print((elapsedTime - startTime)/float(1000)); lcd.print(" s");
  }
}

void startMusic() {
  srand(millis());
  int choice = rand() % 4;
  switch (choice) {
    case 0:
      startMusicNotes(NOTE_B4, NOTE_B5);
      break;
    case 1:
      startMusicNotes(NOTE_C4, NOTE_C5);
      break;
    case 2:
      startMusicNotes(NOTE_G4, NOTE_G5);
      break;
    case 3:
      startMusicNotes(NOTE_E4, NOTE_E5);
      break;
  }
}

void startMusicNotes(int a, int b) {
    tone(4, a, 200);
    delay(2000);
    tone(4, a, 200);
    delay(400);
    tone(4, a, 200);
    delay(400);
    tone(4, a, 200);
    delay(400);
    tone(4, b, 200);
    delay(0);
}

void endMusic() {
  srand(millis());
  int choice = rand() % 4;
  switch (choice) {
    case 0:
      endMusicOne();
      break;
    case 1:
      endMusicTwo();
      break;
    case 2:
      endMusicThree();
      break;
    case 3:
      endMusicFour();
      break;
  }
}

void endMusicOne() {
    tone(4, NOTE_C5, 200);
    delay(400);
    tone(4, NOTE_E5, 200);
    delay(400);
    tone(4, NOTE_G5, 200);
    delay(400);
    tone(4, NOTE_F5, 400);
    delay(0);
}

void endMusicTwo() {
    tone(4, NOTE_C5, 200);
    delay(400);
    tone(4, NOTE_E5, 200);
    delay(400);
    tone(4, NOTE_G5, 200);
    delay(400);
    tone(4, NOTE_C6, 400);
    delay(0);
}

void endMusicThree() {
    tone(4, NOTE_B5, 200);
    delay(400);
    tone(4, NOTE_DS6, 200);
    delay(400);
    tone(4, NOTE_FS6, 200);
    delay(400);
    tone(4, NOTE_F6, 400);
    delay(0);
}

void endMusicFour() {
    tone(4, NOTE_C6, 200);
    delay(400);
    tone(4, NOTE_AS5, 200);
    delay(400);
    tone(4, NOTE_A5, 200);
    delay(400);
    tone(4, NOTE_C6, 400);
    delay(0);
}