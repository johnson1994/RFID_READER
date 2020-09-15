
#include <Arduino.h>
#include "rc522.h"

// 构造函数
RC522::RC522(int ss):RC522Base(ss){
}

// 唤醒MFRC522
void RC522::wakeUp(){
  Serial.println("wakeUp");
  // 7-6:RFU 5:RcvOff 4:PowerDown 3-0:Command
  unsigned char CommandReg_value=0x20;
  writeRegister(RC_Register::CommandReg, CommandReg_value);
}


// 读取错误标志寄存器
unsigned char RC522::readError(){
  unsigned char tmp = readRegister(RC_Register::ErrorReg); 
  serialOut("ErrorReg=", tmp);
  return tmp;
}

// 读取版本
unsigned char RC522::readVersion(){
  unsigned char tmp = readRegister(RC_Register::VersionReg);
  serialOut("VersionReg=", tmp); 
  return tmp;
}
