#include "src/userUsbHidKeyboard/USBHIDKeyboard.h"
#define gameMode false

#if (gameMode)
signed char littetList[20] = {'h', 'b',  'm',  0x1B, 'q',  'w', 'e',
                              'f', 'a',  's',  'd',  0x20, '1', '2',
                              '3', 0x20, 0x82, 0x20, '4'};
#else
signed char littetList[20] = {' ', '/',  '*',  '-', '7',  '8', '9',
                              '+', '4',  '5',  '6',  0x20, '1', '2',
                              '3', 0x0A, '0', 0x20, '.'};
#endif

unsigned char buttonPinList[9] = {32, 14, 15, 16, 17, 31, 30, 11, 33};

bool buttonFlags[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool buttonTmp[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char mainCount = 0;

void setup() {
  USBInit();
  pinMode(34, OUTPUT);
  digitalWrite(34, true);
}

void loop() { defScanButton(); }

void defScanButton() {
  delay(100);
  for (unsigned char i = 0; i < 5; i++) {

    pinMode(buttonPinList[i], OUTPUT);
    digitalWrite(buttonPinList[i], LOW);

    for (unsigned char j = 5; j < 9; j++) {

      pinMode(buttonPinList[j], INPUT_PULLUP);
      buttonTmp[mainCount] = !digitalRead(buttonPinList[j]);
      if (buttonFlags[mainCount] != buttonTmp[mainCount]) {
        buttonFlags[mainCount] = buttonTmp[mainCount];
        if (buttonFlags[mainCount]) {
          Keyboard_press(littetList[mainCount]);
          delay(20);
        } else {
          Keyboard_release(littetList[mainCount]);
        }
      }
      mainCount += 1;
    }
    digitalWrite(buttonPinList[i], HIGH);
  }

  mainCount = 0;
}