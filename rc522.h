
#ifndef RC522_DEF
#define RC522_DEF



enum ACTION{ r, w };

class RC522{
public:
  // 片选
  int ss;

  // 寄存器地址 
  // 启动和停止命令的执行
  unsigned char CommandReg =  0x01;
  // 中断请求传递的使能和禁能控制位
  unsigned char CommIEnReg = 0x02;
  // 中断请求传递的使能和禁能控制
  unsigned char DivlEnReg = 0x03;
  // 包含中断请求
  unsigned char CommIRqReg = 0x04;
  // 错误标志寄存器,显示执行的上个命令的错误状态
  unsigned char ErrorReg = 0x06;
  // 显示版本
  unsigned char VersionReg = 0x37;

  // 构造函数
  RC522(int ss);
  // 唤醒MFRC522
  void wakeUp();
  void test();

  // 读取错误标志寄存器
  unsigned char readError();
  // 读取版本
  unsigned char readVersion();

  // 读寄存器
  unsigned char* readCommand(unsigned char *address_list, int len);
  // 读取单个寄存器
  unsigned char readOne(unsigned char address);
  // 写寄存器
  void writeCommand(unsigned char address, unsigned char data);

  // 串口输出
  void serialOut(String mesg, unsigned char hexData);
private:
  
  // 地址封装
  unsigned char address_wrap(unsigned char address,ACTION act);
};

#endif
