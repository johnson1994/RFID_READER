
#ifndef RC522_DEF
#define RC522_DEF

// RC522模块片选
#define RC522_SS 10

enum ACTION{ r, w };

class RC522{
public:
  // 寄存器地址 
  // 启动和停止命令的执行
  unsigned char CommandReg =  0x01;
  // 中断请求传递的使能和禁能控制位
  unsigned char CommIEnReg = 0x02;
  // 错误标志寄存器,显示执行的上个命令的错误状态
  unsigned char ErrorReg = 0x06;
  // 显示版本
  unsigned char VersionReg = 0x37;

  // 构造函数
  RC522();
  // 唤醒MFRC522
  void wakeUp();
  void test();

  // 读取错误标志寄存器
  unsigned char readError();
  // 读取版本
  unsigned char readVersion();

  // 读寄存器
  unsigned char* readCommand(unsigned char *address_list, int len);
  // 写寄存器
  void writeCommand(unsigned char address, unsigned char data);
  
private:
  
  // 地址封装
  unsigned char address_wrap(unsigned char address,ACTION act);
};

#endif
