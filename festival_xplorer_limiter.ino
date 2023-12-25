#include <XBOXUSB.h>
#include <xboxEnums.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXUSB Xbox(&Usb);

bool controllerDisconnected = false;
bool connected = false;
int calibrationState = 1; // 0:not, 1:green, 2:red, 3:yellow...
bool calibrationPrompt = false;

char controllerBinds[] = {'d', 'f', 'j', 'k', 'l', ' '};

int Green;
int Red;
int Yellow;
int Blue;
int Orange;
int Strum1;
int Strum2;
int Starpower;

void setup() {
  Serial.begin(115200);

  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }

  Serial.print(F("\r\nXBOX USB Library Started"));
}

void loop() {
  Usb.Task()

  if (!Xbox.Xbox360Connected) {
    if (!controllerDisconnected) {
      Serial.print("Controller not connected, waiting.");

      controllerDisconnected = true;
    } else {
      Serial.print(".");
    }

    // block code until connected
    return;
  } else if (controllerDisconnected) {
    Serial.println();

    controllerDisconnected = false;
  }

  if (Xbox.getButtonClick(XBOX)) {
    calibrationState = 1;
  }

  if (calibrationState == 1) {
    if (calibrationPrompt) {
      Serial.println("Please enter ")
    }
  }
}
