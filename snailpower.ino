#include <ACS712.h>
#include <SoftwareSerial.h> // 引用库

#define DEFAULT_USB_VOLTAGE 5
#define VOLTAGE_TOLERENCE 0.5
// #define DEBUG

#define PIN_BT_RXD 8
#define PIN_BT_TXD 9
#define PIN_POTENTIOMETERS_UD 4
#define PIN_POTENTIOMETERS_CS 5
#define PIN_POTENTIOMETERS_INC 3
// V1
#define PIN_INPUT_VOLTAGE A0
// V2
#define PIN_BATTERY_VOLTAGE A1
// V3
#define PIN_OUTPUT_VOLTAGE A2

#define PIN_BATTERY_CUTTENT A3

// bluetooth module
SoftwareSerial BT(PIN_BT_TXD, PIN_BT_RXD); // 接HC05发送脚与D8接口连接，HC05接收脚与D9接口连接
char Bt_val;                               // 存储接收的数据

// ACS127
ACS712 ACS(ACS712_05B, PIN_BATTERY_CUTTENT);

int step = 0;


void read_BT()
{
  // 把蓝牙模块接收到的数据发送到串口监视器
  if (BT.available())
  {
    Bt_val = BT.read();
#ifdef DEBUG
    Serial.print(Bt_val);
#endif

  }




#ifdef DEBUG
  // 把串口监视器接收到的数据发送给蓝牙模块
  if (Serial.available())
  {
    Bt_val = Serial.read();
    BT.print(Bt_val);
  }
#endif
}

class Snail_Power
{
  public:

    double vi = 0, vb = 0, vo = 0, cu = 0, percent = 0;
    unsigned long time_last = 0, time_left = 0;


    Snail_Power()
    {

    }

    double get_voltage(uint8_t pin)
    {
      double v = 0;
      for (int i = 0; i < 5; i++)
        v += analogRead(pin) * 5.0 / 1024;
      return v / 5.0;
    }

    void get_status()
    {
      get_output_voltage();
      get_input_voltage();
      get_battery_voltage();
//      get_battery_current();
      get_remaining_power();
    }

    bool usb_safe()
    {
      return vo >= 4.7 && vo <= 5.3;
    }

    double get_input_voltage()
    {
      //TODO:design
      vi = get_voltage(PIN_INPUT_VOLTAGE) * 5.67; //分压计算
      String s="输入电压:"+String(vi);
      BT.print(s);
      return vi;
    }

    double get_output_voltage()
    {
      vo = get_voltage(PIN_OUTPUT_VOLTAGE) * 5.67-0.74; //分压计算
      if(vo<0)vo=0;
      String s="输出电压:"+String(vo);
      BT.print(s);

      return vo;
    }

    double get_battery_voltage()
    {
      vb = get_voltage(PIN_BATTERY_VOLTAGE) * 5.67; //分压计算
      String s="电池电压:"+String(vb);
      BT.print(s);

      return vb;
    }

    double get_battery_current()
    {
      cu = ACS.getCurrentDC();
      String s=String("电流:")+cu+"A";
      BT.print(s);

    }

    double get_remaining_power()
    {

      // TODO: fix
      //
      double percent2 = 259.36 * vb * vb - 1716.6 * vb + 2831.2;

      // TODO:be careful
      if (fabs(percent2 - percent) >= 0.5)
      {
        unsigned long time_now = millis();
        if (time_now > time_last) // overflow of time
        {
          time_left = percent2 / (percent2 - percent) * (time_last - time_now) / 1000.0 / 60; // ms->min
          time_last = time_now;
          percent = percent2;
        }
      }
      return percent2;
    }
    double get_time_left()
    {
      return time_left;
    }
} SnailPower;




void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("BT is ready!");
  // 如果是HC-06，改成38400；
#endif
  BT.begin(9600);
  pinMode(PIN_BATTERY_CUTTENT, INPUT);
  pinMode(PIN_BATTERY_VOLTAGE, INPUT);
  pinMode(PIN_INPUT_VOLTAGE, INPUT);
  pinMode(PIN_OUTPUT_VOLTAGE, INPUT);

}

void loop()
{
  delay(1000);
  read_BT();
  SnailPower.get_status();
}
