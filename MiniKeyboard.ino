
#ifndef USER_USB_RAM
#error "编译时开启USB以及USB用户代码空间"
#endif

#include "src/userUsbHidKeyboard/USBHIDKeyboard.h"

unsigned char buttonPinList[9] = {32, 14, 15, 16, 17, 31, 30, 11, 33};

signed char littetList[32] = {0x2F, 0x2A, '-', '7', '8', '9', '+', '4',
                              '5', '6', '1', '2', '3', 0xB0, '0', 0x2E,
                              'b', 'm', 0xB1, 'q', 'w', 'e', 'f', 'a',
                              's', 'd', '1', '2', '3',0x20, 0x82, '4'};

bool buttonFlags[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool buttonTmp[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char mainCount = 0;
char offset = 0;
bool gameMode = true;

void setup()
{
  USBInit();
  pinMode(34, OUTPUT);
  digitalWrite(34, gameMode);
}

void loop()
{
  defScanButton();
}

void defScanButton()
{
  delay(50);
  for (int i = 0; i < 5; i++)
  {

    pinMode(buttonPinList[i], OUTPUT);
    digitalWrite(buttonPinList[i], LOW);

    for (int j = 5; j < 9; j++)
    {
      pinMode(buttonPinList[j], INPUT_PULLUP);
      buttonTmp[mainCount] = !digitalRead(buttonPinList[j]);
      if (buttonFlags[mainCount] != buttonTmp[mainCount])
      {
        buttonFlags[mainCount] = buttonTmp[mainCount];
        if (i == 0 && j == 5)
        {
          gameMode = !gameMode;
          if (!gameMode)
          {
            offset = 16;
          }
          else
          {
            offset = 0;
          }
          digitalWrite(34, gameMode);
          delay(200);
        }
        else
        {
          if (buttonFlags[mainCount])
          {
            Keyboard_press(littetList[mainCount + offset]);
            delay(20);
          }
          else
          {
            Keyboard_release(littetList[mainCount + offset]);
          }
        }
      }
      mainCount += 1;
      if (i == 2 && j == 8)
      {
        mainCount -= 1;
      }
      if (i == 4 && j == 6)
      {
        mainCount -= 1;
      }
      if (i == 0 && j == 5)
      {
        mainCount -= 1;
      }
    }
    digitalWrite(buttonPinList[i], HIGH);
  }
  mainCount = 0;
}

