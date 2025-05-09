#include "synth.h"
#include "program.h"
#include <U8g2lib.h>
#include <Arduino.h>
#include <string.h>
#include <Audio.h>

typedef unsigned short ushort;
/* 
  U8G2* displayObj = nullptr; // track oled object
  const char** itemList; // item names to display on menu
  int assigned[2] = {0,0}; // track assigned wave to oscillator
  unsigned short len; // len corresponds to num of menu items
  short index = 0; // index into menu items
  short wvi = 0; // index into waveforms
  char waveList*[4] = {
    "Sine",
    "Triangle",
    "Square",
    "Saw"};
  int forms[4] = {
    WAVEFORM_SINE,
    WAVEFORM_TRIANGLE,
    WAVEFORM_SQUARE,
    WAVEFORM_SAWTOOTH};
*/

Synth::Synth(U8G2* disp){
    displayObj = disp;
    len = 3;
    index = 0;
    itemList = new const char*[len];
    itemList[0] = "OSC1: ";
    itemList[1] = "OSC2: ";
    itemList[2] = "Back";
  }
}

Synth::Synth(){
  delete[] itemList;

}
void Synth::onEncoderLeft(){
  index = index - 1;
  if(index < 0) index = 0;
  index = index % len;
  refreshDisplay();  
}
void Synth::onEncoderRight(){
  index = index + 1;
  if(index < 0) index = 0;
  index = index % len;
  refreshDisplay();    
}
void Synth::onClick(){}

void Synth::load(){

  refreshDisplay();  
}

void Synth::refreshDisplay(){
  Serial.println("refreshing");
  displayObj->setDrawColor(1);
  displayObj->clearBuffer();  //clear buffer


  if (!displayObj) {
    Serial.println("displayObj is null!");
    return;
  } else { Serial.println("DisplayObj is good");}
  displayObj->setFont(u8g2_font_ncenB08_tr);
  int height = displayObj->getMaxCharHeight();

  // DISPLAY LOGIC HERE
  int x = 5;
  int y = 0 + height + 5;
  for(int i = 0; i < len; i++){
    char* buff1;
    if(i != 2){
      char* buff2;
      buff1 = itemList[i]; // get item name
      buff2 = waveList[assigned[i]]; // get wave value
      int width1 = displayObj->getStrWidth(buff1);
      int width2 = displayObj->getStrWidth(buff2);
      displayObj->drawStr(x, y, buff1);
      displayObj->drawStr(x + width1, y, buff2);
      if(index == i){ // this object is currently 'selected' so will draw a carrot
        displayObj->drawStr(x + width1 + width2 + 5, y, "<");
      }
    } else { // displaying the back option
      buff1 = itemList[i];
      int width = displayObj->getStrWidth(buff1);
      displayObj->drawStr(x, y, buff1);
      if(index == i){
        displayObj->drawStr(x + width + 5, y, buff1);
      }
    }
    y = y + height + 5; // push y down for next line
  }
  
  displayObj->sendBuffer();
  Serial.println("buffer sent");
}
