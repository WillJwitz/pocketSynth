#pragma once

#define OSC1 0
#define OSC2 1

void audio_patch_init();
void set_waveform(int osc, int type);
void play_note(float freq);
void stop_note();
