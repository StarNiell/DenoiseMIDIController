#include "MIDIUSB.h"

class Potentiometer {
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

// Class "Expr" defines a MIDI control of type "Expression".
// It will send a CC message to a device using USB MIDI 
// only when the position of the potentiometer changes.
class Button {
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
        int Val = digitalRead(HWPin);
        //if ( abs(Val - NewVal) > 1 ) NewVal = Val;      // Is there's a difference of one or more than the threshold value?
        if (Val != NewVal) NewVal = Val;      // Is there's a difference of one or more than the threshold value?
        //delay(4);     // Wait a bit before taking the next sample (Note: Remove comment if there is jitter in the potentiometer readings).
      }
      if (CCValue != NewVal) {        // Send MIDI CC only if value has changed
        CCValue = NewVal;
        midiEventPacket_t event = {0x09, (byte)(0x90 | Channel), CCIdx, CCValue};     //Note: The "Byte" casting is there to resolve a "narrowing conversion" warning at compile time.
        MidiUSB.sendMIDI(event);      // Send to MIDI buffer.
        MidiUSB.flush();              // Transmit buffer immediately.
      }
    };
};


//Declaration of objects of class "Expr".
Potentiometer Pot1;   
Potentiometer Pot2;   /* Un-comment this line if you want a 2nd expression pedal */
Potentiometer Pot3;   /* Un-comment this line if you want a 3rd expression pedal */
Potentiometer Pot4;   /* Un-comment this line if you want a 4th expression pedal */
Button Button1;   /* Un-comment this line if you want a 4th expression pedal */
Button Button2;   /* Un-comment this line if you want a 4th expression pedal */

void setup() {
  Pot1.init(A0, 0, 7);       // Initialize the expression pedal     (Arduino Analog Pin, MIDI channel, CC Number) 
  Pot2.init(A1, 0, 11);    /* Un-comment this line if you want a 2nd expression pedal */
  Pot3.init(A2, 0, 13);    /* Un-comment this line if you want a 3rd expression pedal */
  Pot4.init(A3, 0, 15);    /* Un-comment this line if you want a 4th expression pedal */
  Button1.init(14, 0, 16);    /* Un-comment this line if you want a 4th expression pedal */
  Button2.init(15, 0, 17);    /* Un-comment this line if you want a 4th expression pedal */
}

void loop() {
  Pot1.DoProcess();     // Process Expression Pedal 1
  Pot2.DoProcess();   /* Un-comment this line if you want a 2nd expression pedal */
  Pot3.DoProcess();   /* Un-comment this line if you want a 3rd expression pedal */
  Pot4.DoProcess();   /* Un-comment this line if you want a 4th expression pedal */
  Button1.DoProcess();   /* Un-comment this line if you want a 4th expression pedal */
  Button2.DoProcess();   /* Un-comment this line if you want a 4th expression pedal */
}

/**** End of code ****/
