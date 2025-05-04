#include "program.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

class Menu() : public Program{
public:
  Menu();

  ~Menu();  

  void onEncoderLeft() override;
  void onEncoderRight() override;
  void onClick() override;
  void onLongClick() override;
  void onBack() override;

private:

  const char* items[] = {
    "Waveform Select",
    "Sequencer"
    "BPM"
    "Play"
  }

  int selector = 0;
  int items_len = 4;
}

#endif
