/*
  Capacitive-Touch Arduino Keyboard Piano
  
  Plays piano tones through a buzzer when the user taps touch-sensitive piano "keys"
  
  Created  18 May 2013
  Modified 23 May 2013
  by Tyler Crumpton and Nicholas Jones
  
  This code is released to the public domain. For information about the circuit,
  visit the Instructable tutorial at http://www.instructables.com/id/Capacitive-Touch-Arduino-Keyboard-Piano/
*/

#include <CapacitiveSensor.h>
#include "Tone.h"

#define COMMON_PIN      13    // The common 'send' pin for all keys
#define BUZZER_PIN_1    A0   // The output pin for the piezo buzzer
#define BUZZER_PIN_2    A1
#define BUZZER_PIN_3    A2
#define NUM_OF_SAMPLES  10   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   50  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS     12    // Number of keys that are on the keyboard

// This macro creates a capacitance "key" sensor object for each key on the piano keyboard:
#define CS(Y) CapacitiveSensor(COMMON_PIN, Y)

// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
//int notes[]={NOTE_CS4,NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_DS4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_A4,NOTE_AS4,NOTE_B4}; // C-Major scale
int notes[]={NOTE_CS4,NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_DS4,NOTE_B4,NOTE_A4,NOTE_AS4,NOTE_FS4,NOTE_G4,NOTE_GS4};

// Defines the pins that the keys are connected to:
//CapacitiveSensor keys[] = {CS(3), CS(4), CS(5), CS(6), CS(7), CS(8), CS(9), CS(10)};
CapacitiveSensor keys[] = {CS(2), CS(3), CS(4), CS(5), CS(6), CS(7), CS(8), CS(9), CS(10), CS(11), CS(12), CS(A4)};
Tone freqs[3];

void setup() { 
  // Turn off autocalibrate on all channels:
  for(int i=0; i<NUM_OF_KEYS; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }
  // Set the buzzer as an output:
  freqs[0].begin(BUZZER_PIN_1);
  freqs[1].begin(BUZZER_PIN_2);
  freqs[2].begin(BUZZER_PIN_3);
  Serial.begin(9600);
}

boolean onKeys[] = { false, false, false, false, false, false, false, false, false, false, false, false};
boolean old[] = { false, false, false, false, false, false, false, false, false, false, false, false};

int currFreqs[3] ={ 0, 0, 0 };
void playTone(int f) {
  for(int i = 0; i < 3; i++) {
    if(currFreqs[i] == 0) {
      currFreqs[i] = f;
      freqs[i].play(f);
      break;
    }
  }
}

void stopTone(int f) {
  for(int i = 0; i < 3; i++) {
    if(currFreqs[i] == f) {
      currFreqs[i] = 0;
      freqs[i].stop();
      break;
    }
  }
}

void loop() {    
  // Loop through each key:
  for (int i = 0; i < NUM_OF_KEYS; ++i) {
    // If the capacitance reading is greater than the threshold, play a note:
    int detect = keys[i].capacitiveSensor(NUM_OF_SAMPLES);
    if(i == 9) Serial.println(detect);
    old[i] = onKeys[i];
    if(detect > CAP_THRESHOLD) {
      // tone(BUZZER_PIN, notes[i]); // Plays the note corresponding to the key pressed
      onKeys[i] = true;
    } else {
      onKeys[i] = false;
    }
  }
  for(int i = 0; i < NUM_OF_KEYS; i++) {
    if(old[i] != onKeys[i]) {
      if(onKeys[i]) {
        playTone(notes[i]);
      } else {
        stopTone(notes[i]);
      }
    }
  }
  
}
