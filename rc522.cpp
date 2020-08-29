
#include <Arduino.h>
#include <SPI.h>
#include "rc522.h"

// 构造函数
RC522::RC522(int ss){
  // 设置片选
  this->ss = ss;
  pinMode(ss, OUTPUT);
}

// 唤醒MFRC522
void RC522::wakeUp(){
  Serial.println("doing wakeUp");
  // 7-6:RFU 5:RcvOff 4:PowerDown 3-0:Command
  unsigned char CommandReg_value=0x20;
  writeCommand(CommandReg, CommandReg_value);
  Serial.println("wakeUp finished");
}


// 读取错误标志寄存器
unsigned char RC522::readError(){
  unsigned char tmp = readOne(ErrorReg); 
  serialOut("ErrorReg=", tmp);
  return tmp;
}

// 读取版本
unsigned char RC522::readVersion(){
  unsigned char tmp = readOne(VersionReg);
  serialOut("VersionReg=", tmp); 
  return tmp;
}

// 读寄存器
unsigned char* RC522::readCommand(unsigned char *address_list, int len){
  unsigned char* res_list = new unsigned char[len];

  // SPI开始传输 设置（速率10M 大端 SPI_MODE0：上升沿赋值 下降沿读值）
  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0));
  digitalWrite(ss, LOW);

  unsigned char tmp = address_wrap(address_list[0], ACTION::r);
  SPI.transfer(tmp);
  for(int i=1; i<len; i++){
    tmp = address_wrap(address_list[i], ACTION::r);
    res_list[i-1] = SPI.transfer(tmp);
  }
  res_list[len-1] = SPI.transfer(0x00);
  delete[] address_list;

  digitalWrite(ss, HIGH);
  SPI.endTransaction();
  return res_list;
}

// 读取单个寄存器
unsigned char RC522::readOne(unsigned char address){
  unsigned char *address_list = new unsigned char[1];
  address_list[0] = address;
  unsigned char *tmp = readCommand(address_list, 1);
  unsigned char res = tmp[0];
  delete[] tmp;
  return res; 
}

// 写寄存器
void RC522::writeCommand(unsigned char address, unsigned char data){
//  Serial.println("============= setting regiester (SPI) ===============");
  address = address_wrap(address, ACTION::w);
//  Serial.print("data=");
//  Serial.println(data, BIN);

  // SPI开始传输 设置（速率10M 大端 SPI_MODE0：上升沿赋值 下降沿读值）
  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0));
  digitalWrite(ss, LOW);
//  delay(100);
  SPI.transfer(address);
  SPI.transfer(data);  
//  delay(100);
  digitalWrite(ss, HIGH);
  SPI.endTransaction();
//  Serial.println("============= regiester set finsihed ===============");
}


// 串口输出
void RC522::serialOut(String mesg, unsigned char hexData){
  Serial.print(mesg);
  Serial.println(hexData, HEX);
}

// 地址封装
unsigned char RC522::address_wrap(unsigned char address, ACTION act){
  // 左移1位 将最低位空出来
  address = address << 1;
  if(act == ACTION::r){
    // 如果是读取， 高位置1
    address = 0x80 | address;
  }
  // 最低位统一置0
  address = 0xfe & address;
  return address;
}
