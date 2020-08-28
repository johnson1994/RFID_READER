
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

  // 构造函数
  RC522();
  // 唤醒MFRC522
  void wakeUp();
  void test();

  // 读寄存器
  unsigned char* readCommand(unsigned char *address_list, int len);
  // 写寄存器
  void writeCommand(unsigned char address, unsigned char data);
  
private:
  
  // 地址封装
  unsigned char address_wrap(unsigned char address,ACTION act);
};

#endif
