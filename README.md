# DenoiseMIDIController

## Description
This project help you to build a USB MIDI Controller with 4 Knobs and 2 buttons.
The name "Denoise" is only for fun... because this project was born to automate a VST Host software dedicated to hamradio.
The VST used in this project are:
* BL Denoise
* DD Gate

## Devices
A USB capable Arduino board is usefull for this project.

**NOTE**: Arduino R3 or Arduino Mini or Arduino Nano are not USB capable!

You can use:
* Arduino Pro Micro (or simply Arduino Micro)
* Arduino Leonardo

## Analog Input for 4 Knobs (Potentiometers)
You can use values between 50K ~ 500K Linear potentiometers. 
Connect the left pin to the GND (ground), the right pin to VCC (+5V) and the center pin to the follow ports:
* A0 - Potentiometer1
* A1 - Potentiometer2
* A2 - Potentiometer3
* A3 - Potentiometer4

## Digital Input for 2 Buttons
Put an pin on VCC (+5V) and the other pin to follow ports: 
* 14 - Button1
* 15 - Button2


**NOTE**: Add a 10K resistor between these ports and the GND





