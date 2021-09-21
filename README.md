# midinun-uno
Arduino Uno MIDI control with a Wii Nunchuck, over USB

Use your Wii Nunchuck's accelerometer and joystick as a MIDI controller for your DAW, using Arduino UNO.
Both original and OEM nunchucks will work.
> This tutorial is for Windows only, if you are using linux or mac you have to find an alternative to The Hairless Midi and the virtual MIDI device for you DAW (both are described below)

## Connect nunchuck to arduino

First of all you have to modify the nunchuck so it can connect to arduino with ease, but you can implement any connection you like.

 - ### Disassemble the nunchuck plug
    Just unscrew and remove the plastics
    https://drive.google.com/file/d/1mGgTGFGz2FJIF2qDlXDSn_Pbg-U6LwbP/view?usp=sharing
- ### Cut the nunchuck plug
    You have to be careful when you cut the plug because you have to leave a bit of cable on the plug so you can recognize the colors later as you connect it to arduino
    https://drive.google.com/file/d/1mrbmE_CRcV2hLByeLcvtbhF2u1vbB4vF/view?usp=sharing
- ### Solder classic header pins to nunchuck
    You only need 4 out of nunchuck's 5 cables. Specificaly you need the cables in position 1,3,4 and 6
    https://drive.google.com/file/d/19P9fyTnkYa96uxpV5z21OEeV9g-0wqVK/view?usp=sharing
    Use male pins for classic headers and solder them color by color with the nunchuck's exposed cables
    https://drive.google.com/file/d/1mi1AaBxKj4iAN5-v_ls14wkiqmwjNLV8/view?usp=sharing

Then you have to connect the nunchuck to the arduino.
| Cable Color | Arduino Pin |
| ------ | ------ |
| White | A5 |
| Yellow | A4 |
| Green | 3.3v |
| Red | GND |
https://drive.google.com/file/d/1mG5OvNKQgYk-enxVBwAeopp7cNtc--WO/view?usp=sharing
https://drive.google.com/file/d/19P9fyTnkYa96uxpV5z21OEeV9g-0wqVK/view?usp=sharing

Now you have the nunchuck connected to the arduino

## Setup arduino libraries
The code uses 2 libraries.
 - Nunchuck.h (https://github.com/infusion/Fritzing/tree/master/Nunchuk)
 - arduino_midi_library v4.3.1 (https://github.com/FortySevenEffects/arduino_midi_library/tree/4.3.1/src)
    You have to install arduino_midi_library using Tools->Manage Lirbraries... in the Arduino IDE. Be sure to use the correct version

## Upload the code to arduino

Now we are ready to read the nunchuck's sensors and send MIDI control change commands


## Serial to MIDI
Because arduino UNO doesn't support MIDI over USB connection we have to use a middleware software named The Hairless MIDI.
https://projectgus.github.io/hairless-midiserial/


## Virtual MIDI Device (for your DAW)

## Setup MIDI Controllers

