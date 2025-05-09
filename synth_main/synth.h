#ifndef SYNTH_H
#define SYNTH_H
#include "program.h"
#include <U8g2lib.h>
#include "audio_patch.h"
#include <Audio.h>


class Synth : public Program{
public:
   Synth(U8G2* disp);

  ~Synth();  

  void onEncoderLeft() override; // input
  void onEncoderRight() override; // input
  void onClick() override; // input
  void load() override; // startup to load visuals and other tasks when program is changed to active

  void refreshDisplay();


private:
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
  
};

#endif
