/*  This code is copyright
 *  Declan Green 07/03/2020
 *  Turning Targets v0.3
 *  BN: Arduino Uno
 *  VID: 2341
 *  PID: 0043
 *  SN: 85336303532351107182
 */
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

/*  TEST MODE SWITCH
 *  1 = short timings for bench testing (shows "TEST MODE" at startup)
 *  0 = real match timings - set this before taking it to the range
 */
#define TEST_MODE 1

#if TEST_MODE
const unsigned long LOAD_WAIT       = 6000;    // "Load" to "Attention"
const unsigned long PRECISION_FACE  = 3000;    // Precision stage face time
const unsigned long SERIES_150_FACE = 5000;    // 150 Seconds Series face time
const unsigned long SERIES_20_FACE  = 2000;    // 20 Seconds Series face time
const unsigned long TP1_P1_FACE     = 5000;    // T&P1 Practice 1 face time
#else
const unsigned long LOAD_WAIT       = 60000;   // 60 seconds
const unsigned long PRECISION_FACE  = 300000;  // 300 seconds
const unsigned long SERIES_150_FACE = 150000;  // 150 seconds
const unsigned long SERIES_20_FACE  = 20000;   // 20 seconds
const unsigned long TP1_P1_FACE     = 120000;  // 2 minutes
#endif

// These timings are short already, so they are the same in both modes
const unsigned long EDGE_TIME       = 7000;    // Edge before face, and Unload before face
const unsigned long RAPID_FACE      = 3000;    // Rapid Fire face time
const unsigned long SERIES_10_FACE  = 10000;   // 10 Seconds Series face time
const unsigned long APPEAR_EDGE     = 5000;    // Interval between appearances
const unsigned long TP1_P2_FACE     = 2000;    // T&P1 Practice 2 appearance
const unsigned long APPEAR_3S_FACE  = 3000;    // T&P1 P3 / Multi-Target P3 appearance
const unsigned long MT_P1_FACE      = 15000;   // Multi-Target Practice 1
const unsigned long MT_P2_FACE      = 10000;   // Multi-Target Practice 2
const unsigned long MT_P4_FACE      = 8000;    // Multi-Target Practice 4

// MP3 tracks on the SD card
const int TRACK_UNLOAD    = 1;
const int TRACK_ATTENTION = 2;

LiquidCrystal_I2C lcd(0x27,20,4); //Set the LCD address to 0x27

// Create the Player object
DFRobotDFPlayerMini player;

//The relay connects to pin 5. HIGH = targets to EDGE, LOW = targets to FACE
const int Relay_1 = 5; //Sets the Pin number on the Arduino Uno Board
int upButton = 10;
int downButton = 11;
int selectButton = 12;
int menu = 1;
int led8 = 8; //Connected to LED 20 Sec Series
int led9 = 9; //Connected to LED Precision Stage
int led7 = 7; //Connected to LED Rapid Fire
int led6 = 6; //Connected to LED 150 Sec Series
int led4 = 4; //Connected to LED 10 Sec Series

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

void setup() {

  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
   Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);
    // Play MP3 file on the SD card
    player.play(19); //Plays DRC Initializing System - Please Wait
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }


  pinMode(Relay_1, OUTPUT);
  lcd.init();
  lcd.backlight();
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(led4, OUTPUT); // Declare the LED as an Output
  pinMode(led6, OUTPUT); // Declare the LED as an Output
  pinMode(led7, OUTPUT); //Declare the LED as an Output
  pinMode(led8, OUTPUT); //Declare the LED as an Output
  pinMode(led9, OUTPUT); //Declare the LED as an Output

//Startup LED Sequence

  digitalWrite(9, HIGH); // Turn the Red LED on 220 Ohm Resistor Connected
  delay(200);
  digitalWrite(7, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(6, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(8, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, LOW); // Turn the LED off
  delay(200);
  digitalWrite(8, LOW); // Turn theLED off
  delay(200);
  digitalWrite(6, LOW); // Turn the LED off
  delay(200);
  digitalWrite(7, LOW); // Turn the LED off
  delay(200);
  digitalWrite(9, LOW); // Turn the LED off
  delay(200);
  digitalWrite(9, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(7, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(6, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(8, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, LOW); // Turn the LED off
  delay(200);
  digitalWrite(8, LOW); // Turn the LED off
  delay(200);
  digitalWrite(6, LOW); // Turn the LED off
  delay(200);
  digitalWrite(7, LOW); // Turn the LED off
  delay(200);
  digitalWrite(9, LOW); // Turn the LED off
  delay(200);
  digitalWrite(9, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(7, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(6, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(8, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, LOW); // Turn the LED off
  delay(200);
  digitalWrite(8, LOW); // Turn the LED off
  delay(200);
  digitalWrite(6, LOW); // Turn the LED off
  delay(200);
  digitalWrite(7, LOW); // Turn the LED off
  delay(200);
  digitalWrite(9, LOW); // Turn the LED off
  delay(200);
  digitalWrite(9, HIGH); // Turn the LED on
  digitalWrite(7, HIGH); // Turn the LED on
  digitalWrite(6, HIGH); // Turn the LED on
  digitalWrite(8, HIGH); // Turn the LED on
  digitalWrite(4, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, LOW); // Turn the LED off
  digitalWrite(8, LOW); // Turn the LED off
  digitalWrite(6, LOW); // Turn the LED off
  digitalWrite(7, LOW); // Turn the LED off
  digitalWrite(9, LOW); // Turn the LED off
  delay(200);
  digitalWrite(9, HIGH); // Turn the LED on
  digitalWrite(7, HIGH); // Turn the LED on
  digitalWrite(6, HIGH); // Turn the LED on
  digitalWrite(8, HIGH); // Turn the LED on
  digitalWrite(4, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, LOW); // Turn the LED off
  digitalWrite(8, LOW); // Turn the LED off
  digitalWrite(6, LOW); // Turn the LED off
  digitalWrite(7, LOW); // Turn the LED off
  digitalWrite(9, LOW); // Turn the LED off
  delay(200);
  digitalWrite(9, HIGH); // Turn the LED on
  digitalWrite(7, HIGH); // Turn the LED on
  digitalWrite(6, HIGH); // Turn the LED on
  digitalWrite(8, HIGH); // Turn the LED on
  digitalWrite(4, HIGH); // Turn the LED on
  delay(200);
  digitalWrite(4, LOW); // Turn the LED off
  digitalWrite(8, LOW); // Turn the LED off
  digitalWrite(6, LOW); // Turn the LED off
  digitalWrite(7, LOW); // Turn the LED off
  digitalWrite(9, LOW); // Turn the LED off
  delay(200);

//Print the Welcome Screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("      DRC");
  lcd.setCursor(0,1);
  lcd.print("Turning  Targets");
#if TEST_MODE
  lcd.setCursor(0,2);
  lcd.print("   TEST MODE");
  Serial.println("TEST MODE - short timings");
#endif
  digitalWrite(Relay_1, LOW); //Ensures Relay Back to Off
  delay(2000); //2 Sec delay
  updateMenu(); //Show the menu straight away
}

void loop() {
   if (!digitalRead(downButton)){
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }

}
void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">Precision Stage");
      lcd.setCursor(0, 1);
      lcd.print(" Rapid Fire");
      break;
    case 2:
      lcd.clear();
      lcd.print(" Precision Stage");
      lcd.setCursor(0, 1);
      lcd.print(">Rapid Fire");
      break;
    case 3:
      lcd.clear();
      lcd.print(">150 Sec Series");
      lcd.setCursor(0, 1);
      lcd.print(" 20 Sec Series");
      break;
    case 4:
      lcd.clear();
      lcd.print(" 150 Sec Series");
      lcd.setCursor(0, 1);
      lcd.print(">20 Sec Series");
      break;
    case 5:
      lcd.clear();
      lcd.print(" 20 Sec Series");
      lcd.setCursor(0, 1);
      lcd.print(">10 Sec Series");
      break;
    case 6:
      lcd.clear();
      lcd.print(">T&P1 Practice 1");
      lcd.setCursor(0, 1);
      lcd.print(" T&P1 Practice 2");
      break;
    case 7:
      lcd.clear();
      lcd.print(" T&P1 Practice 1");
      lcd.setCursor(0, 1);
      lcd.print(">T&P1 Practice 2");
      break;
    case 8:
      lcd.clear();
      lcd.print(">T&P1 Practice 3");
      lcd.setCursor(0, 1);
      lcd.print(" Multi-Target P1");
      break;
    case 9:
      lcd.clear();
      lcd.print(" T&P1 Practice 3");
      lcd.setCursor(0, 1);
      lcd.print(">Multi-Target P1");
      break;
    case 10:
      lcd.clear();
      lcd.print(">Multi-Target P2");
      lcd.setCursor(0, 1);
      lcd.print(" Multi-Target P3");
      break;
    case 11:
      lcd.clear();
      lcd.print(" Multi-Target P2");
      lcd.setCursor(0, 1);
      lcd.print(">Multi-Target P3");
      break;
    case 12:
      lcd.clear();
      lcd.print(">Multi-Target P4");
      lcd.setCursor(0, 1);
      lcd.print(" About");
      break;
    case 13:
      lcd.clear();
      lcd.print(" Multi-Target P4");
      lcd.setCursor(0, 1);
      lcd.print(">About");
      break;
    case 14:
      menu = 13;
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 5:
      action5();
      break;
    case 6:
      action6();
      break;
    case 7:
      action7();
      break;
    case 8:
      action8();
      break;
    case 9:
      action9();
      break;
    case 10:
      action10();
      break;
    case 11:
      action11();
      break;
    case 12:
      action12();
      break;
    case 13:
      action13();
      break;
  }
}

/*  Helpers used by all the sequences
 */

void edge() { digitalWrite(Relay_1, HIGH); } //Turn targets to EDGE
void face() { digitalWrite(Relay_1, LOW); }  //Turn targets to FACE

void show(const char* line1, const char* line2) { //Two lines on the LCD
  lcd.clear();
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

void returnToMenu() {
  show("  Returning to", "   Main Menu!");
  delay(5000);
}

/*  A standard timed series, as in the sequence documents:
 *  Announce LOAD -> wait -> Announce ATTENTION + EDGE -> 7 secs -> FACE
 *  -> faceTime -> EDGE + Announce UNLOAD -> 7 secs -> FACE
 */
void timedSeries(int loadTrack, const char* name, unsigned long faceTime) {
  player.play(loadTrack);
  show(name, "Load");
  delay(LOAD_WAIT);
  player.play(TRACK_ATTENTION);
  edge();
  show(name, "Attention");
  delay(EDGE_TIME);
  face();
  show(name, "Face");
  delay(faceTime);
  edge();
  player.play(TRACK_UNLOAD);
  show(name, "Unload");
  delay(EDGE_TIME);
  face();
  show(name, "Complete");
  delay(3000);
}

/*  One exposure: EDGE -> 7 secs -> FACE for faceTime -> EDGE -> 7 secs -> FACE
 */
void exposure(const char* name, unsigned long faceTime) {
  show("Commencing", name);
  edge();
  delay(EDGE_TIME);
  face();
  show(name, "Face");
  delay(faceTime);
  edge();
  show(name, "Edge");
  delay(EDGE_TIME);
  face();
}

/*  Repeated appearances: EDGE, then each appearance is FACE for faceTime
 *  followed by EDGE for edgeTime. Ends on FACE.
 */
void appearances(const char* name, int count, unsigned long faceTime, unsigned long edgeTime) {
  show("Commencing", name);
  edge();
  delay(edgeTime);
  for (int i = 1; i <= count; i++) {
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print("Appearance ");
    lcd.print(i);
    face();
    delay(faceTime);
    edge();
    delay(edgeTime);
  }
  face();
}

/*  The Following Code
 *  Is For The Functionallity
 *  Of The Turning Targets
 *  1) Precision Stage
 *  2) Rapid Fire Stage
 *  3) 150 Seconds Series
 *  4) 20 Seconds Series
 *  5) 10 Seconds Series
 *  6-8) Timed & Precision 1 Practices
 *  9-12) Multi-Target Practices
 */

void action1() { //Precision Stage
  digitalWrite(9, HIGH); // Turn LED 9 on
  timedSeries(7, "Precision Stage", PRECISION_FACE);
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action2() { //Rapid Fire Stage
  digitalWrite(7, HIGH); // Turn the LED on
  player.play(8);
  show(">Commencing", "Rapid Fire Stage");
  delay(LOAD_WAIT);
  player.play(TRACK_ATTENTION);

  // 5 cycles of EDGE for 7 secs then FACE for 3 secs
  for (int cycle = 1; cycle <= 5; cycle++) {
    edge();
    lcd.clear();
    lcd.print(" Cycle ");
    lcd.print(cycle);
    lcd.setCursor(0,1);
    lcd.print("Edge for 7 Secs");
    delay(EDGE_TIME);
    face();
    lcd.setCursor(0,1);
    lcd.print("Face for 3 Secs");
    delay(RAPID_FACE);
  }

  edge(); //EDGE and Unload together
  player.play(TRACK_UNLOAD);
  show(" Unload ", "");
  delay(EDGE_TIME);
  face();
  show("Rapid Fire Stage", "Complete");
  delay(3000);
  returnToMenu();
  digitalWrite(7, LOW); // Turn the LED off
}

void action3() { //150 Seconds Series
  digitalWrite(6, HIGH); // Turn LED 6 on
  timedSeries(5, "150s Sighter", SERIES_150_FACE);
  timedSeries(5, "150s Series 1", SERIES_150_FACE);
  returnToMenu();
  digitalWrite(6, LOW); // Turn the LED OFF
}

void action4() { //20 Seconds Series
  digitalWrite(8, HIGH); // Turn the Corresponding LED on
  timedSeries(4, "20 Sec Series", SERIES_20_FACE);
  returnToMenu();
  digitalWrite(8, LOW); // Turn the Corresponding LED off
}

void action5() { //10 Seconds series
  digitalWrite(4, HIGH); // Turn the LED on
  timedSeries(3, "10 Sec Series", SERIES_10_FACE);
  returnToMenu();
  digitalWrite(4, LOW); // Turn the Corresponding LED off
}

void action6() { //T&P1 Practice 1 - 12 shots in 2 minutes
  digitalWrite(9, HIGH); // Turn LED 9 on
  exposure("T&P1 Practice 1", TP1_P1_FACE);
  returnToMenu();
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action7() { //T&P1 Practice 2 - 6 appearances of 2 secs, 5 sec intervals
  digitalWrite(9, HIGH); // Turn LED 9 on
  appearances("T&P1 Practice 2", 6, TP1_P2_FACE, APPEAR_EDGE);
  returnToMenu();
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action8() { //T&P1 Practice 3 - 3 appearances of 3 secs, 5 sec intervals
  digitalWrite(9, HIGH); // Turn LED 9 on
  appearances("T&P1 Practice 3", 3, APPEAR_3S_FACE, APPEAR_EDGE);
  returnToMenu();
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action9() { //Multi-Target Practice 1 - 6 shots in 15 secs
  digitalWrite(9, HIGH); // Turn LED 9 on
  exposure("Multi-Target P1", MT_P1_FACE);
  returnToMenu();
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action10() { //Multi-Target Practice 2 - 3 shots each target in 10 secs
  digitalWrite(9, HIGH); // Turn LED 9 on
  exposure("Multi-Target P2", MT_P2_FACE);
  returnToMenu();
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action11() { //Multi-Target Practice 3 - 3 appearances of 3 secs, 5 sec intervals
  digitalWrite(9, HIGH); // Turn LED 9 on
  appearances("Multi-Target P3", 3, APPEAR_3S_FACE, APPEAR_EDGE);
  returnToMenu();
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action12() { //Multi-Target Practice 4 - 3 shots each target in 8 secs
  digitalWrite(9, HIGH); // Turn LED 9 on
  exposure("Multi-Target P4", MT_P4_FACE);
  returnToMenu();
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action13() { //
  player.play(16);  //Sg Gnr Hartman Any Fecking Time Sweetheart
  show("Programmed by", "Declan Green '22");
  delay(10000);

}
