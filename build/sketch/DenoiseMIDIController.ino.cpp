#include <Arduino.h>
#line 1 "C:\\Users\\Aniello\\Desktop\\Folders\\Arduino Files\\DenoiseMIDIController\\DenoiseMIDIController.ino"
/*** Start of code ***/
/*
 Simple USB MIDI CC Send for expression pedals.
 This code was made for an Arduino Pro Micro but will work on any 
 Arduino with the ATmega32u4 microcontroller.
 
 Potentiometer wiring:
   - Right pole to Arduino GND pin.
   - Left pole to Arduino VCC pin
   - Center pole to Arduino analog input pin (Ex: A0)

 For this version, MIDI Channel and CC number are hardcoded in the initialization command (see "setup" function).
  
 Created January 22nd, 2022
 By Simon Girouard
*/

#include "MIDIUSB.h"

// Class "Expr" defines a MIDI control of type "Expression".
// It will send a CC message to a device using USB MIDI 
// only when the position of the potentiometer changes.
class Expr {
    int HWPin;
    byte Channel;
    byte CCIdx;
    byte CCValue;
  public:    
    void init(int _HWPin, byte _Channel, byte _CCIdx) {
      HWPin = _HWPin; 
      Channel = _Channel;
      CCIdx = _CCIdx;
      CCValue = 0x00;     // Default to "0" when initializing the object
    }
    void DoProcess() {
      int NewVal = CCValue;
      for (int i = 0; i < 3; i++) {     // Take 3 samples of the analog input
        int Val = (uint8_t) (map(analogRead(HWPin), 0, 1023, 0, 127));      //  Translate the analog pin's value from range 0 to 1023 into a MIDI range of 0 to 127.
        //if ( abs(Val - NewVal) > 1 ) NewVal = Val;      // Is there's a difference of one or more than the threshold value?
        if ( abs(Val - NewVal) > 1 ) NewVal = Val;      // Is there's a difference of one or more than the threshold value?
        //delay(4);     // Wait a bit before taking the next sample (Note: Remove comment if there is jitter in the potentiometer readings).
      }
      if (CCValue != NewVal) {        // Send MIDI CC only if value has changed
        CCValue = NewVal;
        midiEventPacket_t event = {0x0B, (byte)(0xB0 | Channel), CCIdx, CCValue};     //Note: The "Byte" casting is there to resolve a "narrowing conversion" warning at compile time.
        MidiUSB.sendMIDI(event);      // Send to MIDI buffer.
        MidiUSB.flush();              // Transmit buffer immediately.
      }
    };
};


//Declaration of objects of class "Expr".
Expr Expression1;   
//Expr Expression2;   /* Un-comment this line if you want a 2nd expression pedal */
//Expr Expression3;   /* Un-comment this line if you want a 3rd expression pedal */
//Expr Expression4;   /* Un-comment this line if you want a 4th expression pedal */

#line 59 "C:\\Users\\Aniello\\Desktop\\Folders\\Arduino Files\\DenoiseMIDIController\\DenoiseMIDIController.ino"
void setup();
#line 66 "C:\\Users\\Aniello\\Desktop\\Folders\\Arduino Files\\DenoiseMIDIController\\DenoiseMIDIController.ino"
void loop();
#line 59 "C:\\Users\\Aniello\\Desktop\\Folders\\Arduino Files\\DenoiseMIDIController\\DenoiseMIDIController.ino"
void setup() {
  Expression1.init(A0, 0, 7);       // Initialize the expression pedal     (Arduino Analog Pin, MIDI channel, CC Number) 
  //Expression2.init(A1, 0, 11);    /* Un-comment this line if you want a 2nd expression pedal */
  //Expression3.init(A2, 0, 13);    /* Un-comment this line if you want a 3rd expression pedal */
  //Expression4.init(A3, 0, 15);    /* Un-comment this line if you want a 4th expression pedal */
}

void loop() {
  Expression1.DoProcess();     // Process Expression Pedal 1
  //Expression2.DoProcess();   /* Un-comment this line if you want a 2nd expression pedal */
  //Expression3.DoProcess();   /* Un-comment this line if you want a 3rd expression pedal */
  //Expression4.DoProcess();   /* Un-comment this line if you want a 4th expression pedal */
}

/**** End of code ****/

