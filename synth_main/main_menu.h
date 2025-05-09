#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "program.h"
#include <U8g2lib.h>


class Menu : public Program{
public:
   Menu(U8G2* disp, unsigned short s);

  ~Menu();  

  void onEncoderLeft() override; // input
  void onEncoderRight() override; // input
  void onClick() override; // input
  void load() override; // startup to load visuals and other tasks when program is changed to active
  void setItem(const char* nm, Program* prog, unsigned short index); // Set parallel list items, this header impl. prevents any misalignment of the arrays
  void refreshDisplay();


private:
  U8G2* displayObj = nullptr;
  const char** itemList;
  Program** execList;
  unsigned short len;
  short index = 0;
};

#endif
