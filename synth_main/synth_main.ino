#include <U8g2lib.h>
#include <Encoder.h>
#include "program.h"
#include "main_menu.h"

// --- OLED Setup (bit-bang I2C) ---
#define OLED_SDA 25
#define OLED_SCL 24

// 1-page buffer version to reduce memory usage
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ OLED_SCL, /* data=*/ OLED_SDA, /* reset=*/ U8X8_PIN_NONE);

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
Menu main = new Menu();

// --- Setup ---
void setup() {
  // Serial for debugging
  Serial.begin(9600);

  // OLED init
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 10, "OLED ready");
  u8g2.sendBuffer();

  // Rotary encoder button
  pinMode(ENC_SW, INPUT_PULLUP);

  // Button matrix setup
  for (int i = 0; i < 4; i++) {
    pinMode(buttonRows[i], OUTPUT);
    digitalWrite(buttonRows[i], HIGH);
    pinMode(buttonCols[i], INPUT_PULLUP);
  }
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
    }else if(dif == -1){
      activeProg->onEncoderLeft();
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

  /*
  // --- Basic OLED refresh (demo text) ---
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 10);
    u8g2.print("Enc: ");
    u8g2.print(lastEncoderValue);
  } while (u8g2.nextPage());
  */
  delay(50); // Slow down refresh
}
