#include "src/userUsbHidKeyboard/USBHIDKeyboard.h"
#define gameMode false

#if (gameMode)
signed char littetList[20] = {'h', 'b', 'm', 0xB1, 'q', 'w', 'e',
                              'f', 'a', 's', 'd', 0x20, '1', '2',
                              '3', 0x20, 0x82, 0x20, '4'};
#else
signed char littetList[20] = {' ', '/', '*', '-', '7', '8', '9',
                              '+', '4', '5', '6', 0x20, '1', '2',
                              '3', 0x0A, '0', 0x20, '.'};
#endif

unsigned char buttonPinList[9] = {32, 14, 15, 16, 17, 31, 30, 11, 33};

bool buttonFlags[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool buttonTmp[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char mainCount = 0;

void setup()
{
  USBInit();
  pinMode(34, OUTPUT);
  digitalWrite(34, 0);
}

void loop()
{
  defScanButton();
}

void defScanButton()
{
  delay(100);
  //按键扫描
  for (unsigned char i = 0; i < 5; i++)
  {
    //依次把 A1 - A5 拉低
    pinMode(buttonPinList[i], OUTPUT);
    digitalWrite(buttonPinList[i], LOW);

    for (unsigned char j = 5; j < 9; j++)
    {
      //将 A6 - A9 依次设为输入上拉
      pinMode(buttonPinList[j], INPUT_PULLUP);
      //将电平写入list
      buttonTmp[mainCount] = !digitalRead(buttonPinList[j]);
      if (buttonFlags[mainCount] != buttonTmp[mainCount])
      {
        //多加一层判断，可以模拟出真实的键盘按键
        buttonFlags[mainCount] = buttonTmp[mainCount];
        if (buttonFlags[mainCount])
        {
          //按下
          Keyboard_press(littetList[mainCount]);
          delay(20);
        }
        else
        {
          //放开
          Keyboard_release(littetList[mainCount]);
        }
      }
      mainCount += 1;
    }
    //最后把 A1 - A5 重新设为高电平
    digitalWrite(buttonPinList[i], HIGH);
  }

  mainCount = 0;
}
