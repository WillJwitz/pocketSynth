#include "main_menu.h"
#include "program.h"
#include <U8g2lib.h>
#include <Arduino.h>
#include <string.h>

typedef unsigned short ushort;
/* var reference
char** itemsList;
Program** execList;
unsigned short len; 
inline static U8G2* displayObj = nullptr;
*/
Menu::Menu(U8G2* disp, unsigned short s){
  displayObj = disp;
  len = s;
  index = 0;
  itemList = new const char*[len];
  execList = new Program*[len];
  for(int i = 0; i < len; i++){
    itemList[i] = nullptr;
    execList[i] = nullptr;
  }
}

Menu::~Menu(){
  delete[] itemList;
  delete[] execList;
}
void Menu::onEncoderLeft(){
  index--;
  refreshDisplay();  
}
void Menu::onEncoderRight(){
  index++;
  refreshDisplay();  
}
void Menu::onClick(){}
void Menu::load(){
  Serial.println("Items");
  for(int i = 0; i < len; i++){
    Serial.println(itemList[i]);
  }
  refreshDisplay();  
}
void Menu::setItem(const char* nm, Program* prog, unsigned short ind){
  if(ind < len){
    itemList[ind] = nm;
    execList[ind] = prog;
  }
}
void Menu::refreshDisplay(){
  Serial.println("refreshing");
  displayObj->setDrawColor(1);
  displayObj->clearBuffer();  //clear buffer


  if (!displayObj) {
    Serial.println("displayObj is null!");
    return;
  } else { Serial.println("DisplayObj is good");}
  displayObj->setFont(u8g2_font_ncenB08_tr);
  int height = displayObj->getMaxCharHeight();

  int i = -1;
  Serial.print("i ");
  Serial.println(i);
  while(i < 2){
    Serial.println("while loop interior");
    // Below logic to safeguard c++'s bad modulo implementation
    int safe = index + i;
    if(safe < 0){
      safe = safe * -1;
      safe = safe - len;
      if(safe < 0);
        safe = safe * -1;
      safe = safe % len;
    } else {
      safe = safe % len;
    }
    // --------------------------------------------------------
    const char* buff = itemList[safe];
    int width = displayObj->getStrWidth(buff);  // get width

    int x = (128 - width) / 2; // horiz center
    int y = (64 + height) / 2; // vert center
    y += (height * i); // adjust height to stack entries
    /*
    Serial.print("displaying ");
    Serial.print(buff);
    Serial.print(" at ");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.println(".");
    */

    displayObj->drawStr(x, y, buff);
    if(i == 0){
      displayObj->drawStr(x + width + 1, y, "<");
    }
    i = i + 1;
  }
  
  displayObj->sendBuffer();
  Serial.println("buffer sent");
}
