
#ifndef RC522_BASE_DEF
#define RC522_BASE_DEF

// 寄存器操作类型，读/写
enum ACTION{ r, w };

class RC522Base{
public:
  // 片选
  int ss;
  // 构造函数
  RC522Base(int ss);

  ///////////////////// 寄存器操作 ////////////////////////////
  unsigned char* readRegister(unsigned char *address_list, int len);
  unsigned char readRegister(unsigned char address);
  void writeRegister(unsigned char address, unsigned char data);
  
  ///////////////////// 串口输出 //////////////////////
  void serialOut(String mesg, unsigned char hexData);
  
private:
  ////////////////////  地址封装 //////////////////////
  unsigned char address_wrap(unsigned char address,ACTION act);
};


#endif
