# midinun-uno
Use your Wii Nunchuk's accelerometer and joystick as a MIDI controller for your DAW, using Arduino UNO or Nano.
(Both original and OEM nunchuks will work.)

## Connect nunchuk to arduino

First of all you have to modify the nunchuk so it can connect to arduino with ease, but you can implement any connection you like.

 - ### Disassemble the nunchuk plug
    Just unscrew and remove the plastics
    https://drive.google.com/file/d/1mGgTGFGz2FJIF2qDlXDSn_Pbg-U6LwbP/view?usp=sharing
- ### Cut the nunchuk plug
    You have to be careful when you cut the plug because you have to leave a bit of cable on the plug so you can recognize the colors later as you connect it to arduino
    https://drive.google.com/file/d/1mrbmE_CRcV2hLByeLcvtbhF2u1vbB4vF/view?usp=sharing
- ### Solder classic header pins to nunchuk
    You only need 4 out of nunchuk's 5 cables. Specifically you need the cables in position 1,3,4 and 6
    https://drive.google.com/file/d/19P9fyTnkYa96uxpV5z21OEeV9g-0wqVK/view?usp=sharing
    Use male pins for classic headers and solder them color by color with the nunchuk's exposed cables
    https://drive.google.com/file/d/1mi1AaBxKj4iAN5-v_ls14wkiqmwjNLV8/view?usp=sharing

Then you have to connect the nunchuk to the arduino.
| Cable Color | Plug Position | Arduino Pin |
| ------ | ------ | ------ |
| White | 6 | A5 |
| Yellow | 1 |  A4 |
| Green | 3 | 3.3v |
| Red | 4 | GND |

https://drive.google.com/file/d/1mG5OvNKQgYk-enxVBwAeopp7cNtc--WO/view?usp=sharing
https://drive.google.com/file/d/19P9fyTnkYa96uxpV5z21OEeV9g-0wqVK/view?usp=sharing

Now you have the nunchuk connected to the arduino

## Setup arduino libraries
The code uses 2 libraries.
 - Nunchuk.h (https://github.com/infusion/Fritzing/tree/master/Nunchuk)
 - arduino_midi_library v4.3.1 (https://github.com/FortySevenEffects/arduino_midi_library/tree/4.3.1/src)
    You have to install arduino_midi_library using Tools->Manage Libraries... in the Arduino IDE. Be sure to use the correct version

## Upload the code to arduino

Now we are ready to read the nunchuk's sensors and send MIDI control change commands


## Serial to MIDI
Because Arduino UNO doesn't support MIDI over USB connection we have to use a middleware software named The Hairless MIDI, which converts MIDI commands from the serial port (arduino usb) and transmits them to a virtual MIDI device.

Just download and install the software:

https://projectgus.github.io/hairless-midiserial/

## Virtual MIDI Device (for your DAW)
Another software we will need is a virtual MIDI device which will be recognised and "visible" from your DAW so that you can use it as a MIDI remote control source.

The DAW will recognize it as a normal MIDI device.

There are many applications for this use but in this case we will use loopMIDI.

Just download and install the software:

https://www.tobias-erichsen.de/software/loopmidi.html

## Orchestrate the software
-   Make sure arduino is connected to the PC and that the nunchuk is properly connected to the arduino.
-   Run loopMIDI. There should be a default virtual MIDI device so we will use this one (**loopMIDI Port**).
-   Run The HairlessMIDI. Choose your arduino com port on the left side and on the right side choose **loopMIDI Port** as **MIDI Out**.
-   Open your DAW and in your preferences choose the virtual MIDI device **loopMIDI Port**.


## Usage Instructions
Using your DAW's learn function you can map any parameter to any of the nunchuk's 5 channels, joystick X-Y, accelerator X-Y-Z.

**System Modes**

The system has 2 modes, Play and Setup. When you boot the arduino, the system is in the Play mode. 

To enter Setup mode press and hold button **C**, then hold **Z** and the **push** the joystick Y axis to the end. The onboard led should blink slowly 5 times

To exit Setup mode press and hold button **C**, then hold **Z** and the **pull** the joystick Y axis to the end. The onboard led should blink quickly 5 times

### Setup Mode

- Bring your DAW in learning mode and choose a parameter to map.
- You can choose which nunchuk channel to assign by using button **Z**, which cycles through all available channels.
- For each channel chosen, the led blinks accordingly.
- To assign the selected channel to the DAW's parameter press button **C**. 

| Nunchuk Channel | Times Led Blinks |
| ------ | ------ |
| Joystick X (initial) | 1|
| Joystick Y | 2|
| Accelerator X | 3|
| Accelerator Y | 4|
| Accelerator Z | 5|

### Play Mode

By Holding the **C** button the system starts to send the MIDI control change commands to your DAW through the virtual MIDI device.

If you leave the **C** button every control change command stops.

By default the accelerometer channels are ignored. You can cycle through the channels you want to play with using button **Z**.

The led will blink accordingly.

| Accelerator Channel | Times Led Blinks |
| ------ | ------ |
| Off (default) | 1|
|  X | 2|
|  Y | 3|
|  Z | 4|
| XYZ | 5|
