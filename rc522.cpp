
#include <Arduino.h>
#include <SPI.h>
#include "rc522.h"

// 构造函数
RC522::RC522(){
  // 设置片选输出
  pinMode(RC522_SS, OUTPUT);
}

// 唤醒MFRC522
void RC522::wakeUp(){
  Serial.println("doing wakeUp");
  // 7-6:RFU 5:RcvOff 4:PowerDown 3-0:Command
  unsigned char CommandReg_value=0x00;
  writeCommand(CommandReg, CommandReg_value);
  Serial.println("wakeUp finished");
}

void RC522::test(){
  unsigned char *address_list = new unsigned char[1];
  address_list[0] = CommandReg;
  unsigned char *tmp = readCommand(address_list, 1);
  delete[] tmp;
}

// 读寄存器
unsigned char* RC522::readCommand(unsigned char *address_list, int len){
  Serial.println("============= reading regiester (SPI) ===============");
  unsigned char* res_list = new unsigned char[len];

  digitalWrite(RC522_SS, LOW);
  delay(100);

  unsigned char tmp = address_wrap(address_list[0], ACTION::r);
  SPI.transfer(tmp);
  for(int i=1; i<len; i++){
    tmp = address_wrap(address_list[i], ACTION::r);
    res_list[i-1] = SPI.transfer(tmp);
    Serial.println(res_list[i-1], HEX);
  }
  res_list[len-1] = SPI.transfer(0x00);
  Serial.println(res_list[len-1], HEX);
  delete[] address_list;

  delay(100);
  digitalWrite(RC522_SS, HIGH);
  Serial.println("============= regiester read finsihed ===============");
  return res_list;
}

// 写寄存器
void RC522::writeCommand(unsigned char address, unsigned char data){
  Serial.println("============= setting regiester (SPI) ===============");
  address = address_wrap(address, ACTION::w);
  digitalWrite(RC522_SS, LOW);
  delay(100);
  SPI.transfer(address);
  SPI.transfer(data);  
  delay(100);
  digitalWrite(RC522_SS, HIGH);
  Serial.println("============= regiester set finsihed ===============");
}


// 地址封装
unsigned char RC522::address_wrap(unsigned char address, ACTION act){
  address = address << 1;
  
  if(act == ACTION::w){
    address = 0x80 | address;
  }
  address = 0xfe & address;
  Serial.print("address=");
  Serial.println(address, HEX);
  return address;
}
