
#ifndef RC522_DEF
#define RC522_DEF

#include "rc522base.h"

class RC522:public RC522Base{
public:

  // RC522寄存器地址
  enum RC_Register : byte {
    // Page 0: Command and status
    CommandReg      = 0x01,  // starts and stops command execution
    ComIEnReg       = 0x02,  // enable and disable interrupt request control bits
    DivIEnReg       = 0x03,  // enable and disable interrupt request control bits
    ComIrqReg       = 0x04,  // interrupt request bits
    DivIrqReg       = 0x05,  // interrupt request bits
    ErrorReg        = 0x06,  // error bits showing the error status of the last command executed 
    Status1Reg      = 0x07,  // communication status bits
    Status2Reg      = 0x08,  // receiver and transmitter status bits
    FIFODataReg     = 0x09,  // input and output of 64 byte FIFO buffer
    FIFOLevelReg    = 0x0A,  // number of bytes stored in the FIFO buffer
    WaterLevelReg   = 0x0B,  // level for FIFO underflow and overflow warning
    ControlReg      = 0x0C,  // miscellaneous control registers
    BitFramingReg   = 0x0D,  // adjustments for bit-oriented frames
    CollReg         = 0x0E,  // bit position of the first bit-collision detected on the RF interface
    
    // Page 1: Command
    ModeReg         = 0x11,  // defines general modes for transmitting and receiving 
    TxModeReg       = 0x12,  // defines transmission data rate and framing
    RxModeReg       = 0x13,  // defines reception data rate and framing
    TxControlReg    = 0x14,  // controls the logical behavior of the antenna driver pins TX1 and TX2
    TxASKReg        = 0x15,  // controls the setting of the transmission modulation
    TxSelReg        = 0x16,  // selects the internal sources for the antenna driver
    RxSelReg        = 0x17,  // selects internal receiver settings
    RxThresholdReg  = 0x18,  // selects thresholds for the bit decoder
    DemodReg        = 0x19,  // defines demodulator settings
    MfTxReg         = 0x1C,  // controls some MIFARE communication transmit parameters
    MfRxReg         = 0x1D,  // controls some MIFARE communication receive parameters
    SerialSpeedReg  = 0x1F,  // selects the speed of the serial UART interface
    
    // Page 2: Configuration
    CRCResultRegH     = 0x21,  // shows the MSB and LSB values of the CRC calculation
    CRCResultRegL     = 0x22,
    ModWidthReg       = 0x24,  // controls the ModWidth setting?
    RFCfgReg          = 0x26,  // configures the receiver gain
    GsNReg            = 0x27,  // selects the conductance of the antenna driver pins TX1 and TX2 for modulation 
    CWGsPReg          = 0x28,  // defines the conductance of the p-driver output during periods of no modulation
    ModGsPReg         = 0x29,  // defines the conductance of the p-driver output during periods of modulation
    TModeReg          = 0x2A,  // defines settings for the internal timer
    TPrescalerReg     = 0x2B,  // the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
    TReloadRegH       = 0x2C,  // defines the 16-bit timer reload value
    TReloadRegL       = 0x2D,
    TCounterValueRegH   = 0x2E,  // shows the 16-bit timer value
    TCounterValueRegL   = 0x2F,
    
    // Page 3: Test Registers
    TestSel1Reg       = 0x31,  // general test signal configuration
    TestSel2Reg       = 0x32,  // general test signal configuration
    TestPinEnReg      = 0x33,  // enables pin output driver on pins D1 to D7
    TestPinValueReg   = 0x34,  // defines the values for D1 to D7 when it is used as an I/O bus
    TestBusReg        = 0x35,  // shows the status of the internal test bus
    AutoTestReg       = 0x36,  // controls the digital self-test
    VersionReg        = 0x37,  // shows the software version 
    AnalogTestReg     = 0x38,  // controls the pins AUX1 and AUX2
    TestDAC1Reg       = 0x39,  // defines the test value for TestDAC1
    TestDAC2Reg       = 0x3A,  // defines the test value for TestDAC2
    TestADCReg        = 0x3B   // shows the value of ADC I and Q channels
  };

  // RC522 命令集
  enum RC_Command : byte {
    Idle        = 0x00,         // no action, cancels current command execution
    Mem         = 0x01,         // stores 25 bytes into the internal buffer
    GenerateRandomID  = 0x02,   // generates a 10-byte random ID number
    CalcCRC       = 0x03,       // activates the CRC coprocessor or performs a self-test
    Transmit      = 0x04,       // transmits data from the FIFO buffer
    NoCmdChange   = 0x07,       // no command change, can be used to modify the CommandReg register bits without affecting the command, for example, the PowerDown bit
    Receive       = 0x08,       // activates the receiver circuits
    Transceive    = 0x0C,       // transmits data from FIFO buffer to antenna and automatically activates the receiver after transmission
    MFAuthent     = 0x0E,       // performs the MIFARE standard authentication as a reader
    SoftReset     = 0x0F        // resets the MFRC522
  };

  // 接收器增益
  enum RC_RxGain : byte {
    RxGain_18dB       = 0x00,  // 000b - 18 dB, minimum
    RxGain_23dB       = 0x01,  // 001b - 23 dB
    RxGain_18dB_2     = 0x02,  // 010b - 18 dB, it seems 010b is a duplicate for 000b
    RxGain_23dB_2     = 0x03,  // 011b - 23 dB, it seems 011b is a duplicate for 001b
    RxGain_33dB       = 0x04,  // 100b - 33 dB, average, and typical default
    RxGain_38dB       = 0x05,  // 101b - 38 dB
    RxGain_43dB       = 0x06,  // 110b - 43 dB
    RxGain_48dB       = 0x07,  // 111b - 48 dB, maximum
    RxGain_min        = 0x00,  // 000b - 18 dB, minimum, convenience for RxGain_18dB
    RxGain_avg        = 0x04,  // 100b - 33 dB, average, convenience for RxGain_33dB
    RxGain_max        = 0x07   // 111b - 48 dB, maximum, convenience for RxGain_48dB
  };
  

  // 构造函数
  RC522(int ss);
  // 唤醒MFRC522
  void wakeUp();
  void test();

  // 读取错误标志寄存器
  unsigned char readError();
  // 读取版本
  unsigned char readVersion();

private:
};

#endif
