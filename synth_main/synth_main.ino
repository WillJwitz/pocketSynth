#include <U8g2lib.h>
#include <Encoder.h>

#include "program.h"
#include "main_menu.h"
#include "audio_patch.h"
#include "synth.h"

int led = 13;

// --- OLED Setup (bit-bang I2C) ---
#define OLED_SDA 25
#define OLED_SCL 24


U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ OLED_SCL, /* data=*/ OLED_SDA, /* reset=*/ U8X8_PIN_NONE);


// --- Rotary Encoder Pins ---
#define ENC_CLK 26
#define ENC_DT  27
#define ENC_SW  28

Encoder encoder(ENC_CLK, ENC_DT);
long lastEncoderValue = 0;

// --- Button Pad Pins ---
const int buttonRows[4] = {29, 30, 31, 32};
const int buttonCols[4] = {33, 34, 35, 36};

//--- Current Prog ---
Program* activeProg = nullptr;

//--- Menu ---
Menu mainMenu(&u8g2, 4);
Synth synthMenu(&u8g2);


// --- Setup ---
void setup() {
  // Serial for debugging
  Serial.begin(9600);
  // inintialize screen
  u8g2.begin();

  // main menu startup
 
  mainMenu.setItem("Synth", , 0);
  mainMenu.setItem("Play", nullptr, 1);
  mainMenu.setItem("Sequence", nullptr, 2);
  mainMenu.setItem("Info", nullptr, 3);
  activeProg = &mainMenu;
  activeProg->load();


  // Rotary encoder button
  pinMode(ENC_SW, INPUT_PULLUP);

  // Button matrix setup
  for (int i = 0; i < 4; i++) {
    pinMode(buttonRows[i], OUTPUT);
    digitalWrite(buttonRows[i], HIGH);
    pinMode(buttonCols[i], INPUT_PULLUP);
  }
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
}

// --- Main Loop ---
void loop() {

 
  
  // --- Rotary Encoder Read ---
  long newPos = encoder.read() / 4; // Divide if your encoder outputs 4x per tick
  if (newPos != lastEncoderValue) {
    short dif = newPos - lastEncoderValue;
    lastEncoderValue = newPos;
    if(dif == 1){
      activeProg->onEncoderRight();
      Serial.println(dif);
    }else if(dif == -1){
      activeProg->onEncoderLeft();
      Serial.println(dif);
    }
    Serial.print("Encoder: ");
    Serial.println(dif);
    
  }

  // --- Encoder Button Check ---
  if (digitalRead(ENC_SW) == LOW) {
    Serial.println("Encoder button pressed");
    activeProg->onClick();
    delay(200); // debounce
  }
  
  delay(10); // Slow down refresh
}
