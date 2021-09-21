#include <Wire.h>
#include "Nunchuk.h"
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();
int maxJoystickVal = 127;
int minJoystickVal = -127;
int maxSensorVal = 250;  //max 511
int minSensorVal = -250; //min -511
int minMidiVal = 0;
int maxMidiVal = 127;
int accelX;
int accelY;
int accelZ;
int joyX;
int joyY;
int btnC;
int btnZ;
int btnCPrev = 0;
int btnZPrev = 0;
bool isSetupState = false;
int accelMode = 0; //0 - off, 1 - x, 2 - y, 3 - z, 4 - xyz
int accelModeMax = 4;
int setupMode = 0; //0 - joyX, 1 - joyY, 2 - accelX, 3 - accelY, 4 - accelZ
int setupModeMax = 4;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Wire.begin();
  // Change TWI speed for nuchuk, which uses Fast-TWI (400kHz)
  Wire.setClock(400000);
  nunchuk_init_power(); // A1 and A2 is power supply
  nunchuk_init();
  Serial.begin(115200);
}

void loop()
{

  if (nunchuk_read())
  {

    mapAllInputs();
    iterateSetupState();

    if (isSetupState)
    {

      iterateSetupMode();
      setupControllers();
    }
    else
    {
      iterateAccelMode();
      if (btnC == 1 && btnZ == 0)
      {
        MIDI.sendControlChange(1, joyY, 1);
        MIDI.sendControlChange(2, joyX, 1);
        sendAccelData();
      }
    }
  }
}
void iterateAccelMode()
{
  if (btnZ == 1 && btnZPrev == 0 && btnC == 0)
  {
    accelMode += 1;
    if (accelMode > accelModeMax)
      accelMode = 0;
    ledBlinkAccelMode(accelMode);
    btnZPrev = 1;
  }
  else if (btnZ == 0 && btnZPrev == 1 && btnC == 0)
  {
    btnZPrev = 0;
  }
}

void iterateSetupMode()
{
  if (btnZ == 1 && btnZPrev == 0 && btnC == 0)
  {
    setupMode += 1;
    if (setupMode > setupModeMax)
      setupMode = 0;
    ledBlinkSetupMode(setupMode);
    btnZPrev = 1;
  }
  else if (btnZ == 0 && btnZPrev == 1 && btnC == 0)
  {
    btnZPrev = 0;
  }
}

void setupControllers()
{
  if (btnZ == 0 && btnC == 1)
  {
    switch (setupMode)
    {
    case 0:
      MIDI.sendControlChange(1, joyY, 1);
      break;
    case 1:
      MIDI.sendControlChange(2, joyX, 1);
      break;
    case 2:
      MIDI.sendControlChange(3, accelX, 1);
      break;
    case 3:
      MIDI.sendControlChange(4, accelY, 1);
      break;
    case 4:
      MIDI.sendControlChange(5, accelZ, 1);
      break;
    default:
      break;
    }
  }
}
void iterateSetupState()
{
  if (btnC == 1 && btnZ == 1 && joyY == 0)
  {
    if (isSetupState)
    {
      ledBlinkExitSetup();
      isSetupState = false;
    }
  }
  else if (btnC == 1 && btnZ == 1 && joyY == 127)
  {
    if (isSetupState == false)
    {
      ledBlinkEnterSetup();
      setupMode = 0;
      isSetupState = true;
    }
  }
}

void mapAllInputs()
{
  accelX = map(nunchuk_accelX(), minSensorVal, maxSensorVal, minMidiVal, maxMidiVal);
  accelY = map(nunchuk_accelY(), minSensorVal, maxSensorVal, minMidiVal, maxMidiVal);
  accelZ = map(nunchuk_accelZ(), minSensorVal, maxSensorVal, minMidiVal, maxMidiVal);
  joyX = map(nunchuk_joystickX(), minJoystickVal, maxJoystickVal, minMidiVal, maxMidiVal);
  joyY = map(nunchuk_joystickY(), minJoystickVal, maxJoystickVal, minMidiVal, maxMidiVal);
  btnC = nunchuk_buttonC();
  btnZ = nunchuk_buttonZ();
}

void sendAccelData()
{
  switch (accelMode)
  {
  case 1:
    MIDI.sendControlChange(3, accelX, 1);
    break;
  case 2:
    MIDI.sendControlChange(4, accelY, 1);
    break;
  case 3:
    MIDI.sendControlChange(5, accelZ, 1);
    break;
  case 4:
    MIDI.sendControlChange(3, accelX, 1);
    MIDI.sendControlChange(4, accelY, 1);
    MIDI.sendControlChange(5, accelZ, 1);
    break;
  default:
    break;
  }
}

void playNote()
{
  if (btnC == 1 and btnCPrev == 0)
  {
    MIDI.sendNoteOn(42, 127, 1);
    btnCPrev = 1;
  }
  else if (btnC == 0 and btnCPrev == 1)
  {
    MIDI.sendNoteOff(42, 0, 1);
    btnCPrev = 0;
  }
}
void ledBlinkAccelMode(int mode)
{
  ledBlink(mode + 1, 250);
}
void ledBlinkSetupMode(int mode)
{
  ledBlink(mode + 1, 250);
}
void ledBlinkEnterSetup()
{
  ledBlink(5, 500);
}
void ledBlinkExitSetup()
{
  ledBlink(5, 100);
}
void ledBlink(int times, int blinkDelay)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(blinkDelay);
    digitalWrite(LED_BUILTIN, LOW);
    delay(blinkDelay);
  }
}