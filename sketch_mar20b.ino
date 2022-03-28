/*  This code is copyright
 *  Declan Green 07/03/2020
 *  Turning Targets v0.2
 *  BN: Arduino Uno
 *  VID: 2341
 *  PID: 0043
 *  SN: 85336303532351107182
 */
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


LiquidCrystal_I2C lcd(0x27,20,4); //Set the LCD address to 0x27 for a 16 chars and 2 line display

// Create the Player object
DFRobotDFPlayerMini player;

//The relay connects to pins 10 and 11 
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

const int RELAY_PIN1 = 5; //Defines Pin (relay_Pin1) 5 as a relay

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
  lcd.write(0);  
  lcd.print("     DRC     ");
  lcd.write(0);
  lcd.setCursor(0,1);  
  lcd.print("Turning  Targets ");
  digitalWrite(Relay_1, LOW); //Ensures Relay Back to Off
  delay(2000); //2 Sec delay
 
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
      lcd.print("Rapid Fire");
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
      lcd.print("20 Seconds Series");
      lcd.setCursor(0, 1);
      lcd.print(">10 Seconds Series");
      break;
    case 6:
      lcd.clear();
      lcd.print(">T&P1 Practice 1");
      lcd.setCursor(0, 1);
      lcd.print("T&P1 Practice 2");
      break;      
    case 7:
      lcd.clear();
      lcd.print("T&P1 Practice 1");
      lcd.setCursor(0, 1);
      lcd.print(">T&P1 Practice 2");
      break;     
    case 8:
      lcd.clear();
      lcd.print(">T&P1 Practice 3");
      lcd.setCursor(0, 1);
      lcd.print("Multi-TargetP1");
      break; 
    case 9:
      lcd.clear();
      lcd.print("T&P1 Practice 3");
      lcd.setCursor(0, 1);
      lcd.print(">Multi-Target P1");
      break;
    case 10:
      lcd.clear();
      lcd.print(">Multi-Target P2");
      lcd.setCursor(0, 1);
      lcd.print("Multi-Target P3");
      break;
    case 11:
      lcd.clear();
      lcd.print("Multi-Target P2");
      lcd.setCursor(0, 1);
      lcd.print(">Multi-Target P3");
      break;
    case 12:
      lcd.clear();
      lcd.print(">Multi-Target P4");
      lcd.setCursor(0, 1);
      lcd.print("About");
      break;
    case 13:
      lcd.clear();
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

/*  The Following Code 
 *  Is For The Functionallity
 *  Of The Turning Targets
 *  1) Precision Stage
 *  2) Rapid Fire Stage
 *  3)150 Seconds Series
 *  4) 20 Seconds Series
 *  10 Seconds Series
 */

void action1() { //Precision Stage
  player.play(7);
  digitalWrite(9, HIGH); // Turn LED 9 on  
  lcd.clear();
  lcd.print(">Commencing");
  lcd.setCursor(0,1);  
  lcd.print("Precision Stage ");

//mp3.playMp3FolderTrack(19);
  //DFMiniMp3.play(1);
  delay(6000); //6 second delay, change to 60 seconds
  //Announce Attention
  //mp3.playMp3FolderTrack(0);  // Attention Callout
  //Starts the Relay Sequence for Precision Stage Selection

  digitalWrite(Relay_1, HIGH); //Ensures Relay On and Turned To Edge

  delay(7000); //Creates a 7 second delay
  lcd.clear();
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  
  lcd.print(">Face for 300 Secs"); //This creates a 300 second Wait
  lcd.setCursor(0,1);  
  lcd.print(" Cycle 1 ");
  delay(3000); //3 sec delay, change to 300 secs
  digitalWrite(Relay_1, HIGH); //Turns Relay Back to EDGE
  delay(1000); //Creates a 1 sec delay
  //  mp3.playMp3FolderTrack(4);  // Unload
  delay(7000); //7 Second Delay  
  digitalWrite(Relay_1, LOW); //Ensures Relay Back to Face
  lcd.clear();
  lcd.print("Precision Stage");
  lcd.setCursor(0,1);  
  lcd.print("Stage 1 Complete");
  delay(7000);
  digitalWrite(9, LOW); // Turn LED 9 on
  }

void action2() { //Rapid Fire Stage
  player.play(8);
  digitalWrite(7, HIGH); // Turn the LED on
  lcd.clear();
  lcd.print(">Commencing");
  lcd.setCursor(0,1);  
  lcd.print("Rapid Fire Stage ");
  
  delay(2000); //Change this to 60 seconds
//Announce Attention
// mp3.playMp3FolderTrack(0);  // Attention
// Starts the Relay Sequence for Rapid Fire Selection

//Cycle One Start
  digitalWrite(Relay_1, HIGH); //Turn Target to Edge for Starting Cycle One
  lcd.clear();
  lcd.print(" Cycle 1 ");
  lcd.setCursor(0,1);  
  lcd.print("Edge for 7 Secs");
  delay(7000);  
  lcd.clear();
  lcd.print(" Cycle 1 ");
  lcd.setCursor(0,1);  
  lcd.print("Face for 3 Secs");
  digitalWrite(Relay_1, LOW); //Ensures Relay Back to Off and Turned to Face
  delay(3000);
//Cycle One End

//Cycle Two Start  
  lcd.clear();
  lcd.print(" Cycle 2 ");
  lcd.setCursor(0,1);  
  lcd.print("Edge for 7 Secs");
  digitalWrite(Relay_1, HIGH); //Turn Target to Edge for Starting Cycle Two
  delay(7000);  
  lcd.clear();
  lcd.print(" Cycle 2 ");
  lcd.setCursor(0,1);  
  lcd.print("Face for 3 Secs");
  digitalWrite(Relay_1, LOW); //Ensures Relay Back to Off and Turned to Face
  delay(3000);
//Cycle Two End

//Cycle Three Start
  lcd.clear();
  lcd.print(" Cycle 3 ");
  lcd.setCursor(0,1);  
  lcd.print("Edge for 7 Secs");
  digitalWrite(Relay_1, HIGH); //This HIGH Flips the relay pin to Edge
  delay(7000);
  
  lcd.clear();
  lcd.print(" Cycle 3 ");
  lcd.setCursor(0,1);  
  lcd.print("Face for 3 Secs");
  digitalWrite(Relay_1, LOW); //Ensures Relay Back to Off and Turned to Face
  delay(3000);
//Cycle Three End

//Cycle Four Start
  lcd.clear();
  lcd.print(" Cycle 4 ");
  lcd.setCursor(0,1);  
  lcd.print("Edge for 7 Secs");
  digitalWrite(Relay_1, HIGH); //This HIGH Flips the relay pin to Edge
  delay(7000);

  lcd.clear();
  lcd.print(" Cycle 4 ");
  lcd.setCursor(0,1);  
  lcd.print("Face for 3 Secs");
  digitalWrite(Relay_1, LOW); //Ensures Relay Back to Off and Turned to Face
  delay(3000);
//Cycle Four End

//Cycle Five Start
  lcd.clear();
  lcd.print(" Cycle 5 ");
  lcd.setCursor(0,1);  
  lcd.print("Edge for 7 Secs");
  digitalWrite(Relay_1, HIGH); //This HIGH Flips the relay pin to Edge
  delay(7000);

  lcd.clear();
  lcd.print(" Cycle 5 ");
  lcd.setCursor(0,1);  
  lcd.print("Face for 3 Secs");
  digitalWrite(Relay_1, LOW); //Ensures Relay Turned to Face
  delay(3000);
//Cycle Five End
  lcd.clear();
  lcd.print(" Unload ");
  digitalWrite(Relay_1, HIGH); //This HIGH Flips the relay pin to Edge
  delay(7000);
player.play(1);  // Unload Voice Command
      
  lcd.clear();
  lcd.print("Rapid Fire Stage");
  lcd.setCursor(0,1);  
  lcd.print("Complete - Wait!");
  delay(7000);
  digitalWrite(Relay_1, LOW); //Target Face Show
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(5000);
  digitalWrite(7, LOW); // Turn the LED off
}

void action3() { //150 Seconds Series
  player.play(5);  //Announce 150 Seconds Series - Load
  delay(5000);
  digitalWrite(6, HIGH); // Turn LED 6 on
  lcd.clear();
  lcd.print("Commencing");
  lcd.setCursor(0,1);  
  lcd.print("150 Seconds Series");
  lcd.setCursor(0,1);  
  lcd.print("Sighter Series");
// Start of Sighter Series
  player.play(2);  // Attention
  digitalWrite(Relay_1, HIGH); //Turn Target to Edge for Starting
  delay(6000); //Needs changed to 60 Seconds Delay
  //Announce Attention
// mp3.playMp3FolderTrack(0);  // Attention
  lcd.clear();
  lcd.print(">150 Seconds Series");
  delay(7000); //7 Seconds Delay
  digitalWrite(Relay_1, LOW); //Turn Target to Face
  lcd.clear();
  lcd.print(">   FACE");
  delay(5000); //Needs changed to 150 Seconds Delay
  player.play(1);  // Unload
  delay(7000); //7 Second Delay  
  digitalWrite(Relay_1, HIGH); //Ensures Relay Back to Edge
//End of Sighter Series

// Start of First Series
  digitalWrite(Relay_1, HIGH); //Turn Target to Edge for Starting
  delay(6000); //Needs changed to 60 Seconds Delay
  //Announce Attention
  player.play(2);  // Attention
  lcd.clear();
  lcd.print(">First Series");
  delay(7000); //7 Seconds Delay
  digitalWrite(Relay_1, LOW); //Turn Target to Face
  lcd.clear();
  lcd.print(">   FACE");
  delay(5000); //Needs changed to 150 Seconds Delay
  player.play(1);  // Unload
  delay(7000); //7 Second Delay  
  digitalWrite(Relay_1, LOW); //Ensures Relay Back to Face

  digitalWrite(6, LOW); // Turn the LED OFF
}

void action4() { //20 Seconds Series
  digitalWrite(8, HIGH); // Turn the Corresponding LED on
  player.play(4);//Announce 120 Seconds Series - Load
//Announce Attention
  delay(5000);
  player.play(2);  // Attention
  digitalWrite(Relay_1, HIGH); //Turn Target to Edge for Starting
  lcd.clear();
  lcd.print(">20 Seconds Series");
  delay(6000); //Change this to 60 seconds
  digitalWrite(Relay_1, LOW); //Turn Target to FACE
  delay(2000); //Change to 20 seconds
  digitalWrite(Relay_1, HIGH); //Turn Target to Edge
  player.play(1);  // Unload
  delay(7000);
  digitalWrite(Relay_1, LOW); //Turn Target to FACE  
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(5000);
  digitalWrite(8, LOW); // Turn the Corresponding LED off
}

void action5() { //10 Seconds series
  digitalWrite(4, HIGH); // Turn the LED on
  player.play(3);
  delay(5000);
  digitalWrite(Relay_1, HIGH); //Turn Target to Edge for Starting
  lcd.clear();
  lcd.print("Commencing");//
  lcd.setCursor(0,1);  
  lcd.print("10 Seconds Series");
  
  delay(6000); //6 Seconds Delay needs changes to 60 seconds
//Announce Attention  
  player.play(2);  // Attention
  lcd.clear();
  lcd.print("Attention");
  delay(7000);
  digitalWrite(Relay_1, LOW); //Turn Target to FACE
  lcd.clear();
  lcd.print(" Face ");
  delay(10000); //10 sec delay
  digitalWrite(Relay_1, HIGH); //Turn Target to Edge
  lcd.clear();
  lcd.print(" Edge ");
player.play(1); // Unload
  delay(7000); //7 sec delay
  digitalWrite(Relay_1, LOW); //Turn Target to FACE  
  lcd.clear();
  lcd.print("10 Sec Series");
  lcd.setCursor(0,1);  
  lcd.print(" Complete ");
  delay(5000);
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(5000);
  digitalWrite(4, LOW); // Turn the Corresponding LED off
}

void action6() { //T&P1 Practice 1
  digitalWrite(9, HIGH); // Turn LED 9 on  
  lcd.clear();
  lcd.print("Commencing");
  lcd.setCursor(0,1);  
  lcd.print("T&P1 Practice 1");
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(7000);
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  delay(5000); //Needs Changed to 120 seconds (120000)
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(7000);
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action7() { //T&P1 Practice 2
  digitalWrite(9, HIGH); // Turn LED 9 on  
  lcd.clear();
  lcd.print("Commencing");
  lcd.setCursor(0,1);  
  lcd.print("T&P1 Practice 2");
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000); //5 Seconds Edge
  lcd.clear();
  lcd.print("Appearance 1");
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(2000); //Face for 2 Seconds
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 2");
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(2000); //Face for 2 Seconds
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 3");
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(2000); //Face for 2 Seconds
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 4");
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(2000); //Face for 2 Seconds
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 5");
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(2000); //Face for 2 Seconds
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 6");
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(2000); //Face for 2 Seconds
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(7000);
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action8() { //T&P1 Practice 3
  digitalWrite(9, HIGH); // Turn LED 9 on  
  lcd.clear();
  lcd.print("Commencing");
  lcd.setCursor(0,1);  
  lcd.print("T&P1 Practice 3");
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 1");
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  delay(3000); //
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 2");
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(3000); //
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 3");
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  delay(3000); // 
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE 
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(7000);
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action9() { //Multi-Target Practice 1
  digitalWrite(9, HIGH); // Turn LED 9 on  
  lcd.clear();
  lcd.print("Commencing");
  lcd.setCursor(0,1);  
  lcd.print("Multi-Target P1");
  delay(7000);
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(15000);
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  delay(7000);
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(7000);
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action10() { //Multi-Target Practice 2
  digitalWrite(9, HIGH); // Turn LED 9 on  
  lcd.clear();
  lcd.print("Commencing");
  lcd.setCursor(0,1);  
  lcd.print("Multi-Target P2");
  delay(7000);
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(10000);
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  delay(7000);
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(7000);
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action11() { //Multi-Target Practice 3
digitalWrite(9, HIGH); // Turn LED 9 on  
  lcd.clear();
  lcd.print("Commencing");
  lcd.setCursor(0,1);  
  lcd.print("Multi-Target P2");
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 1");
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  delay(3000); //
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 2");
  digitalWrite(Relay_1, LOW); //Relay Turned To FACE
  delay(3000); //
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  lcd.clear();
  lcd.print("Appearance 3");
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  delay(3000); // 
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE 
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(7000);
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action12() { //Multi-Target Practice 4
  digitalWrite(9, HIGH); // Turn LED 9 on  
  lcd.clear();
  lcd.print("Commencing");
  lcd.setCursor(0,1);  
  lcd.print("Multi-Target P4");
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  delay(8000);
  digitalWrite(Relay_1, HIGH); //Ensures Relay Turned To Edge
  delay(5000);
  digitalWrite(Relay_1, LOW); //Ensures Relay On and Turned To FACE
  lcd.clear();
  lcd.print("  Returning to");
  lcd.setCursor(0,1);  
  lcd.print("   Main Menu!");
  delay(5000);
  digitalWrite(9, LOW); // Turn LED 9 off
}

void action13() { //
  player.play(16);  //Sg Gnr Hartman Any Fecking Time Sweetheart
  lcd.clear();
  lcd.print("Programmed by");
  lcd.setCursor(0,1);  
  lcd.print("Declan Green '22");
  delay(10000);
  
}
