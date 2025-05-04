#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


AudioSynthWaveformSine sine1;       // Create sine wave object
AudioOutputI2S i2s1;                // Audio output to the SGTL5000 shield
AudioConnection patchCord1(sine1, 0, i2s1, 0); // sine -> i2s left
AudioConnection patchCord2(sine1, 0, i2s1, 1); // sine -> i2s right
AudioControlSGTL5000 sgtl5000_1;     // Control object for the audio shield

int led = 13;

void setup() {
  AudioMemory(12);  // Allocates memory for audio objects

  sgtl5000_1.enable();         // Turn on the audio shield
  sgtl5000_1.volume(0.5);      // Set output volume (0.0 to 1.0)

  sine1.frequency(440);        // Set sine wave frequency (A4 note)
  sine1.amplitude(0.5);        // Set sine wave amplitude (0.0 to 1.0)

  pinMode(led, OUTPUT);
}

void loop() {
  // light flashing to indicate that things are actaully running
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}
