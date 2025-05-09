#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "audio_patch.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=149.1999969482422,237.1999969482422
AudioSynthWaveform       waveform2;      //xy=150.1999969482422,270.20001220703125
AudioMixer4              mixer1;         //xy=437.20001220703125,270.1999969482422
AudioOutputI2S           i2s1;           //xy=741.2000122070312,284.20001220703125
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(waveform2, 0, mixer1, 1);
AudioConnection          patchCord3(mixer1, 0, i2s1, 0);
AudioConnection          patchCord4(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=438.20001220703125,327.20001220703125
// GUItool: end automatically generated code

void audio_patch_init(){
  AudioMemory(12);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.75);
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);

  waveform1.begin(WAVEFORM_SINE);
  waveform2.begin(WAVEFORM_SINE);
}
void set_waveform(int osc, int type){
  if(osc == OSC1) waveform1.begin(type);
  if(osc == OSC2) waveform2.begin(type);
}
void play_note(float freq){
  waveform1.frequency(freq);
  waveform2.frequency(freq);
  waveform1.amplitude(1.0);
  waveform2.amplitude(1.0);
}
void stop_note(){
  waveform1.amplitude(0.0);
  waveform2.amplitude(0.0);
}
