
#include <Arduino.h>
#include <SPI.h>
#include "rc522base.h"


/////////// 构造函数 /////////////
RC522Base::RC522Base(int ss){
  this->ss = ss;
  pinMode(ss, OUTPUT);    // 设置片选->数字输出模式
}

////////// 读寄存器 ////////////
unsigned char* RC522Base::readRegister(unsigned char *address_list, int len){
  unsigned char* res_list = new unsigned char[len];

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0));   // SPI开始传输 设置（速率10M 大端 SPI_MODE0：上升沿赋值 下降沿读值）
  digitalWrite(ss, LOW);

  unsigned char tmp = address_wrap(address_list[0], ACTION::r);     // 封装地址
  SPI.transfer(tmp);                                  // 传地址取值 （第一个返回值值无意义，不获取）
  for(int i=1; i<len; i++){
    tmp = address_wrap(address_list[i], ACTION::r);   // 封装地址
    res_list[i-1] = SPI.transfer(tmp);                // 传地址取值 (取到的值为前一个地址的值)
  }
  res_list[len-1] = SPI.transfer(0x00);               // 传0x00 取最后一个地址的值
  delete[] address_list;

  digitalWrite(ss, HIGH); 
  SPI.endTransaction();                               // SPI传输结束  
  return res_list;
}

///////////// 读取单个寄存器 ////////////////
unsigned char RC522Base::readRegister(unsigned char address){
  unsigned char *address_list = new unsigned char[1];
  address_list[0] = address;
  unsigned char *tmp = readRegister(address_list, 1);
  unsigned char res = tmp[0];
  delete[] tmp;
  return res; 
}

////////////// 写寄存器 ////////////////////
void RC522Base::writeRegister(unsigned char address, unsigned char data){
  address = address_wrap(address, ACTION::w);

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0));   // SPI开始传输 设置（速率10M 大端 SPI_MODE0：上升沿赋值 下降沿读值）
  digitalWrite(ss, LOW);
  SPI.transfer(address);
  SPI.transfer(data);  
  digitalWrite(ss, HIGH);
  SPI.endTransaction();                                                      // SPI传输结束
}


//////////////// 串口输出 ////////////////////
void RC522Base::serialOut(String mesg, unsigned char hexData){
  Serial.print(mesg);
  Serial.print("0x");
  Serial.println(hexData, HEX);
}

/////////////// 地址封装 /////////////////////
unsigned char RC522Base::address_wrap(unsigned char address, ACTION act){
  address = address << 1;         // 左移1位 将最低位空出来
  if(act == ACTION::r){           
    address = 0x80 | address;     // 如果是读取， 高位置1
  }
  address = 0xfe & address;       // 最低位统一置0
  return address;
}
