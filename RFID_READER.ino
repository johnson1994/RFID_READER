#include <SPI.h>
#include "rc522.h"

// RC522模块片选引脚
#define RC522_SS 10

// rc522模块
RC522 *rc522;

void setup() {
  Serial.begin(115200);
  Serial.println("=========== starting ===========");

  // 内置LED设置输出
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  SPI.begin();
  
  // 初始化rc522模块
  rc522 = new RC522(RC522_SS);
  rc522->readVersion();
  rc522->wakeUp();
  rc522->serialOut("CommandReg=", rc522->readRegister(rc522->RC_Register::CommandReg));
  rc522->readError();
  Serial.println("========== init finished ============");
}


void loop() {
//  Serial.println("idle");
  delay(1000);
//  rc522->test();
//  rc522->readError();
}
