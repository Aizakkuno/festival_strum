#include <XBOXUSB.h>
#include <xboxEnums.h>

#include <Keyboard.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXUSB Xbox(&Usb);

bool controllerDisconnected = false;

uint8_t bindControllerState = 0;
bool bindControllerButtonPrompted = false;
ButtonEnum lastBindButton = NONE;

uint8_t bindKeyboardState = 0;
bool bindKeyPrompted = false;

ButtonEnum validButtons[12] = {A, B, X, Y, UP, DOWN, LEFT, RIGHT, BACK, START, LB, RB};

ButtonEnum GreenButton = A;
ButtonEnum RedButton = B;
ButtonEnum YellowButton = Y;
ButtonEnum BlueButton = X;
ButtonEnum OrangeButton = LB;
ButtonEnum StrumUp = UP;
ButtonEnum StrumDown = DOWN;
ButtonEnum SelectButton = BACK;
AnalogHatEnum TiltHat = RightHatY;

bool lastGreenButtonPressed = false;
bool lastRedButtonPressed = false;
bool lastYellowButtonPressed = false;
bool lastBlueButtonPressed = false;
bool lastOrangeButtonPressed = false;
bool lastStrumUpPressed = false;
bool lastStrumDownPressed = false;
bool lastSelectButtonPressed = false;

unsigned long lastGreenButtonChange = 0;
unsigned long lastRedButtonChange = 0;
unsigned long lastYellowButtonChange = 0;
unsigned long lastBlueButtonChange = 0;
unsigned long lastOrangeButtonChange = 0;
unsigned long lastStrumUpChange = 0;
unsigned long lastStrumDownChange = 0;
unsigned long lastSelectButtonChange = 0;

uint16_t TiltThreshold = 20000;
uint8_t debounceDelay = 50;

char Key1 = 'd';
char Key2 = 'f';
char Key3 = 'j';
char Key4 = 'k';
char Key5 = 'l';
char OverdriveKey = ' ';

bool key1Pressed = false;
bool key1Pressed = false;
bool key3Pressed = false;
bool key4Pressed = false;
bool key5Pressed = false;
bool overdriveKeyPressed = false;

void setup() {
  Serial.begin(115200);

  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }

  Serial.println(F("\r\nXBOX USB Library Started"));

  Keyboard.begin();
}

ButtonEnum getWhichButtonClicked() {
  for (int i = 0; i < 12; i++) {
    ButtonEnum button = validButtons[i];

    if (Xbox.getButtonClick(button)) {
      return button;
    }
  }

  return NONE;
}

void loop() {
  Usb.Task();

  if (!Xbox.Xbox360Connected) {
    if (!controllerDisconnected) {
      Serial.print(F("Controller not connected/initialized, waiting..."));

      controllerDisconnected = true;
    }// } else {
    //   Serial.print(F("."));
    // }

    // delay(1000);

    // block code until connected
    return;
  } else {
    controllerDisconnected = false;
  }

  if (Xbox.getButtonClick(XBOX)) {
    bindControllerState = 1;
  }

  // im not a c++ native so this is gonna be unnecessarily long code
  if (bindControllerState == 1) {
    if (!bindControllerButtonPrompted) {
      Serial.println(F("Please press the green button!"));

      bindControllerButtonPrompted = true;
    }

    ButtonEnum buttonPressed = getWhichButtonClicked();
    if (buttonPressed != NONE && buttonPressed != lastBindButton) {
      GreenButton = buttonPressed;
      lastBindButton = buttonPressed;

      bindControllerButtonPrompted = false;

      bindControllerState += 1;
    }
  } else if (bindControllerState == 2) {
    if (!bindControllerButtonPrompted) {
      Serial.println(F("Please press the red button!"));

      bindControllerButtonPrompted = true;
    }

    ButtonEnum buttonPressed = getWhichButtonClicked();
    if (buttonPressed != NONE && buttonPressed != lastBindButton) {
      RedButton = buttonPressed;
      lastBindButton = buttonPressed;

      bindControllerButtonPrompted = false;

      bindControllerState += 1;
    }
  } else if (bindControllerState == 3) {
    if (!bindControllerButtonPrompted) {
      Serial.println(F("Please press the yellow button!"));

      bindControllerButtonPrompted = true;
    }

    ButtonEnum buttonPressed = getWhichButtonClicked();
    if (buttonPressed != NONE && buttonPressed != lastBindButton) {
      YellowButton = buttonPressed;
      lastBindButton = buttonPressed;

      bindControllerButtonPrompted = false;

      bindControllerState += 1;
    }
  } else if (bindControllerState == 4) {
    if (!bindControllerButtonPrompted) {
      Serial.println(F("Please press the blue button!"));

      bindControllerButtonPrompted = true;
    }

    ButtonEnum buttonPressed = getWhichButtonClicked();
    if (buttonPressed != NONE && buttonPressed != lastBindButton) {
      BlueButton = buttonPressed;
      lastBindButton = buttonPressed;

      bindControllerButtonPrompted = false;

      bindControllerState += 1;
    }
  } else if (bindControllerState == 5) {
    if (!bindControllerButtonPrompted) {
      Serial.println(F("Please press the orange button!"));

      bindControllerButtonPrompted = true;
    }

    ButtonEnum buttonPressed = getWhichButtonClicked();
    if (buttonPressed != NONE && buttonPressed != lastBindButton) {
      OrangeButton = buttonPressed;
      lastBindButton = buttonPressed;

      bindControllerButtonPrompted = false;

      bindControllerState += 1;
    }
  } else if (bindControllerState == 6) {
    if (!bindControllerButtonPrompted) {
      Serial.println(F("Please strum up!"));

      bindControllerButtonPrompted = true;
    }

    ButtonEnum buttonPressed = getWhichButtonClicked();
    if (buttonPressed != NONE && buttonPressed != lastBindButton) {
      StrumUp = buttonPressed;
      lastBindButton = buttonPressed;

      bindControllerButtonPrompted = false;

      bindControllerState += 1;
    }
  } else if (bindControllerState == 7) {
    if (!bindControllerButtonPrompted) {
      Serial.println(F("Please strum down!"));

      bindControllerButtonPrompted = true;
    }

    ButtonEnum buttonPressed = getWhichButtonClicked();
    if (buttonPressed != NONE && buttonPressed != lastBindButton) {
      StrumDown = buttonPressed;
      lastBindButton = buttonPressed;

      bindControllerButtonPrompted = false;

      bindControllerState += 1;
    }
  } else if (bindControllerState == 8) {
    if (!bindControllerButtonPrompted) {
      Serial.println(F("Please press the select button!"));

      bindControllerButtonPrompted = true;
    }

    ButtonEnum buttonPressed = getWhichButtonClicked();
    if (buttonPressed != NONE && buttonPressed != lastBindButton) {
      SelectButton = buttonPressed;
      lastBindButton = buttonPressed;

      bindControllerButtonPrompted = false;

      bindControllerState += 1;
    }
  } else if (bindControllerState == 9) {
    if (!bindControllerButtonPrompted) {
      Serial.println("Please tilt your controller neck up!");

      bindControllerButtonPrompted = true;
    }

    if (Xbox.getAnalogHat(LeftHatY) > TiltThreshold) {
      TiltHat = LeftHatY;

      bindControllerButtonPrompted = false;

      bindControllerState = 0;
    } else if (Xbox.getAnalogHat(RightHatY) > TiltThreshold) {
      TiltHat = RightHatY;

      bindControllerButtonPrompted = false;

      bindControllerState = 0;

      Serial.println("Done binding controller.");
    }
  }

  // check for incoming serial data:
  if (bindKeyboardState == 0 && Serial.available() > 0) {
    // read incoming serial data:
    String inString = Serial.readString();
    inString.trim();

    if (inString.equalsIgnoreCase("bind")) {
      bindKeyboardState = 1;
    }
  }

  if (bindKeyboardState == 1) {
    if (!bindKeyPrompted) {
      Serial.println(F("Please send the keybind for Key 1!"));

      bindKeyPrompted = true;
    }

    if (Serial.available() > 0) {
      Key1 = Serial.read();

      bindKeyPrompted = false;

      bindKeyboardState += 1;
    }
  } else if (bindKeyboardState == 2) {
    if (!bindKeyPrompted) {
      Serial.println(F("Please send the keybind for Key 2!"));

      bindKeyPrompted = true;
    }

    if (Serial.available() > 0) {
      Key2 = Serial.read();

      bindKeyPrompted = false;

      bindKeyboardState += 1;
    }
  } else if (bindKeyboardState == 3) {
    if (!bindKeyPrompted) {
      Serial.println(F("Please send the keybind for Key 3!"));

      bindKeyPrompted = true;
    }

    if (Serial.available() > 0) {
      Key3 = Serial.read();

      bindKeyPrompted = false;

      bindKeyboardState += 1;
    }
  } else if (bindKeyboardState == 4) {
    if (!bindKeyPrompted) {
      Serial.println(F("Please send the keybind for Key 4!"));

      bindKeyPrompted = true;
    }

    if (Serial.available() > 0) {
      Key4 = Serial.read();

      bindKeyPrompted = false;

      bindKeyboardState += 1;
    }
  } else if (bindKeyboardState == 5) {
    if (!bindKeyPrompted) {
      Serial.println(F("Please send the keybind for Key 5!"));

      bindKeyPrompted = true;
    }

    if (Serial.available() > 0) {
      Key5 = Serial.read();

      bindKeyPrompted = false;

      bindKeyboardState += 1;
    }
  } else if (bindKeyboardState == 6) {
    if (!bindKeyPrompted) {
      Serial.println(F("Please send the keybind for Overdrive!"));

      bindKeyPrompted = true;
    }

    if (Serial.available() > 0) {
      OverdriveKey = Serial.read();

      bindKeyPrompted = false;

      bindKeyboardState = 0;

      Serial.println("Done binding keys.");
    }
  }

  while (Serial.available() > 0) {
    Serial.read();
  }

  if (bindKeyboardState > 0 || bindControllerState > 0) return;

  unsigned long currentTime = millis();

  bool greenButtonPressed;

  // if enough time has gone by to allow the button state to change and it has
  // changed, update the state, otherwise assume its the last state
  if (((currentTime - lastGreenButtonChange) > debounceDelay) &&
      (lastGreenButtonPressed != Xbox.getButtonPress(GreenButton))) {

    greenButtonPressed = !lastGreenButtonPressed;

    lastGreenButtonChange = currentTime;
  } else {
    greenButtonPressed = lastGreenButtonPressed;
  }

  bool redButtonPressed;
  if (((currentTime - lastRedButtonChange) > debounceDelay) &&
      (lastRedButtonPressed != Xbox.getButtonPress(RedButton))) {

    redButtonPressed = !lastRedButtonPressed;

    lastRedButtonChange = currentTime;
  } else {
    redButtonPressed = lastRedButtonPressed;
  }

  bool yellowButtonPressed;
  if (((currentTime - lastYellowButtonChange) > debounceDelay) &&
      (lastYellowButtonPressed != Xbox.getButtonPress(YellowButton))) {

    yellowButtonPressed = !lastYellowButtonPressed;

    lastYellowButtonChange = currentTime;
  } else {
    yellowButtonPressed = lastYellowButtonPressed;
  }

  bool blueButtonPressed;
  if (((currentTime - lastBlueButtonChange) > debounceDelay) &&
      (lastBlueButtonPressed != Xbox.getButtonPress(BlueButton))) {

    blueButtonPressed = !lastBlueButtonPressed;

    lastBlueButtonChange = currentTime;
  } else {
    blueButtonPressed = lastBlueButtonPressed;
  }

  bool orangeButtonPressed;
  if (((currentTime - lastOrangeButtonChange) > debounceDelay) &&
      (lastOrangeButtonPressed != Xbox.getButtonPress(OrangeButton))) {

    orangeButtonPressed = !lastOrangeButtonPressed;

    lastOrangeButtonChange = currentTime;
  } else {
    orangeButtonPressed = lastOrangeButtonPressed;
  }

  bool strumUpPressed;
  if (((currentTime - lastStrumUpChange) > debounceDelay) &&
      (lastStrumUpPressed != Xbox.getButtonPress(StrumUp))) {

    strumUpPressed = !lastStrumUpPressed;

    lastStrumUpChange = currentTime;
  } else {
    strumUpPressed = lastStrumUpPressed;
  }

  bool strumDownPressed;
  if (((currentTime - lastStrumDownChange) > debounceDelay) &&
      (lastStrumDownPressed != Xbox.getButtonPress(StrumDown))) {

    strumDownPressed = !lastStrumDownPressed;

    lastStrumDownChange = currentTime;
  } else {
    strumDownPressed = lastStrumDownPressed;
  }

  bool selectButtonPressed;
  if (((currentTime - lastSelectButtonChange) > debounceDelay) &&
      (lastSelectButtonPressed != Xbox.getButtonPress(SelectButton))) {

    selectButtonPressed = !lastSelectButtonPressed;

    lastSelectButtonChange = currentTime;
  } else {
    selectButtonPressed = lastSelectButtonPressed;
  }

  if ((strumUpPressed && !lastStrumUpPressed) ||
      (strumDownPressed && !lastStrumDownPressed)) {

    if (greenButtonPressed) {
      if (key1Pressed) {
        Keyboard.release(Key1);
      } else {
        key1Pressed = true;
      }
      
      Keyboard.press(Key1);
    }

    if (redButtonPressed) {
      if (key2Pressed) {
        Keyboard.release(Key2);
      } else {
        key2Pressed = true;
      }
      
      Keyboard.press(Key2);
    }

    if (yellowButtonPressed) {
      if (key3Pressed) {
        Keyboard.release(Key3);
      } else {
        key3Pressed = true;
      }
      
      Keyboard.press(Key3);
    }

    if (blueButtonPressed) {
      if (key4Pressed) {
        Keyboard.release(Key4);
      } else {
        key4Pressed = true;
      }
      
      Keyboard.press(Key4);
    }

    if (orangeButtonPressed) {
      if (key5Pressed) {
        Keyboard.release(Key5);
      } else {
        key5Pressed = true;
      }
      
      Keyboard.press(Key5);
    }
  }
  // } else {
  //   Keyboard.release(Key1);
  //   Keyboard.release(Key2);
  //   Keyboard.release(Key3);
  //   Keyboard.release(Key4);
  //   Keyboard.release(Key5);
  // }

  if ((Xbox.getAnalogHat(TiltHat) > TiltThreshold || selectButtonPressed) &&
      !overdriveKeyPressed) {

    Keyboard.press(OverdriveKey);

    overdriveKeyPressed = true;
  } else {
    Keyboard.release(OverdriveKey);

    overdriveKeyPressed = false;
  }

  // release keys not pressed anymore
  // keys should release when resetting during strumming or if theyre unpressed
  if (!greenButtonPressed && key1Pressed) {
    Keyboard.release(Key1);

    key1Pressed = false;
  }

  if (!redButtonPressed && key2Pressed) {
    Keyboard.release(Key2);

    key2Pressed = true;
  }

  if (!yellowButtonPressed && key3Pressed) {
    Keyboard.release(Key3);

    key3Pressed = false;
  }

  if (!blueButtonPressed && key4Pressed) {
    Keyboard.release(Key4);

    key4Pressed = false;
  }

  if (!orangeButtonPressed && key5Pressed) {
    Keyboard.release(Key5);

    key5Pressed = false;
  }

  lastGreenButtonPressed = greenButtonPressed;
  lastRedButtonPressed = redButtonPressed;
  lastYellowButtonPressed = yellowButtonPressed;
  lastBlueButtonPressed = blueButtonPressed;
  lastOrangeButtonPressed = orangeButtonPressed;
  lastStrumUpPressed = strumUpPressed;
  lastStrumDownPressed = strumDownPressed;
  lastSelectButtonPressed = selectButtonPressed;

  delay(1);
}
