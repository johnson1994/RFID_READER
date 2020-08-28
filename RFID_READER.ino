#include <SPI.h>
#include "rc522.h"


// rc522模块
RC522 *rc522;

void setup() {
  Serial.begin(115200);
  Serial.println("=========== starting ===========");

  // 内置LED设置输出
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  SPI.begin();
  // 初始化SPI 16M 大端 MODE0(下降沿设置数据, 上升沿取值)
//  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
  
  // 初始化rc522模块
  rc522=new RC522();
  rc522->readVersion();
  rc522->wakeUp();
  rc522->readError();
  Serial.println("init finished");
}


void loop() {
//  Serial.println("idle");
  delay(1000);
//  rc522->test();
//  rc522->readError();
}
