#include <SoftwareSerial.h>   // 引用库
#include <dht.h>
//定义蓝牙模块引脚
SoftwareSerial BT(8, 9); // 接HC05发送脚与D8接口连接，HC05接收脚与D9接口连接
char val;  // 存储接收的数据
#define dataPin 7 // Defines pin number to which the sensor is connected
dht DHT; // Creats a DHT object


void setup() {
  Serial.begin(9600);
  Serial.println("BT is ready!");
  // 如果是HC-06，改成38400；
  BT.begin(9600);
  pinMode(3, OUTPUT);
}
void loop() {
  // 把串口监视器接收到的数据发送给蓝牙模块
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
  // 把蓝牙模块接收到的数据发送到串口监视器
  if (BT.available()) {
    val = BT.read();
    if (val == '1')digitalWrite(3, HIGH);
    if (val == '0')digitalWrite(3, LOW);
    Serial.print(val);
    
  }


    int readData = DHT.read22(dataPin); // Reads the data from the sensor
  float t = DHT.temperature; // Gets the values of the temperature
  
  float h = DHT.humidity; // Gets the values of the humidity
  
  // Printing the results on the serial monitor
  BT.print("Temperature = ");
  BT.print(t);
  BT.println(" *C ");
  BT.print("    Humidity = ");
  BT.print(h);
  BT.println(" % ");
  delay(2000); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz
}
