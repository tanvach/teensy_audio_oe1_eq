/* DAP Bass enhance example SGTL5000 only

This example code is in the public domain
*/

#include <Audio.h>
#include <Wire.h>


int updateFilter[5];
int led = 13;
boolean led_status = true;

// Create the Audio components.  These should be created in the
// order data flows, inputs/sources -> processing -> outputs
//

AudioInputI2S       audioInput;         // audio shield: mic or line-in
AudioOutputI2S      audioOutput;        // audio shield: headphones & line-out

// Create Audio connections between the components
//
AudioConnection c1(audioInput, 0, audioOutput, 0); // left passing through
AudioConnection c2(audioInput, 1, audioOutput, 1); // right passing through

// Create an object to control the audio shield.
// 
AudioControlSGTL5000 audioShield;

void setup() {
  pinMode(led, OUTPUT);
//  Serial.begin(9600);
  
  // Audio connections require memory to work.
  AudioMemory(4);
  
  // Enable the audio shield and initally disable the output volume.
  audioShield.enable();
  audioShield.volume(0);
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);

  // Bass Enhance with SGTL5000
  audioShield.audioPreProcessorEnable();
  // audioShield.enhanceBass((float)lr_level,(float)bass_level,(uint8_t)hpf_bypass,(uint8_t)cutoff);
  // 1: Pass through most of LR channel
  // 140: somewhat aggressive bass boost. Usable range ~ 100 - 160. Lower is more bass
  // 0: enable high pass filter
  // 4: Cutoff freq ~175Hz
  audioShield.enhanceBass((float)1,(float)140,(uint8_t)0,(uint8_t)4);
  audioShield.enhanceBassEnable();
  // please see http://www.pjrc.com/teensy/SGTL5000.pdf page 50 for valid values for BYPASS_HPF and CUTOFF

  // Parametric EQ based on AutoEQ output
  audioShield.eqSelect(1);
  audioShield.eqFilterCount(7);
  calcBiquad(FILTER_PARAEQ, 58, 7.0, 0.23, 524288, 44100, updateFilter);
  audioShield.eqFilter(0,updateFilter);
  calcBiquad(FILTER_PARAEQ, 217, -10.4, 1.58, 524288, 44100, updateFilter);
  audioShield.eqFilter(1,updateFilter);
  calcBiquad(FILTER_PARAEQ, 712, 2.7, 3.73, 524288, 44100, updateFilter);
  audioShield.eqFilter(2,updateFilter);
  calcBiquad(FILTER_PARAEQ, 1062, 3.8, 2.25, 524288, 44100, updateFilter);
  audioShield.eqFilter(3,updateFilter);
  calcBiquad(FILTER_PARAEQ, 1581, -7.6, 2.60, 524288, 44100, updateFilter);
  audioShield.eqFilter(4,updateFilter);
  calcBiquad(FILTER_PARAEQ, 2530, -4.3, 2.91, 524288, 44100, updateFilter);
  audioShield.eqFilter(5,updateFilter);
  calcBiquad(FILTER_PARAEQ, 3321, 3.8, 1.66, 524288, 44100, updateFilter);
  audioShield.eqFilter(6,updateFilter);

  // High pass filter adds noise for some reason. We don't need it.
  audioShield.adcHighPassFilterDisable();

  // A bit of analog gain for BMR drivers
  audioShield.volume(0.7);
}

void loop() {
  // Event loop not needed
}
