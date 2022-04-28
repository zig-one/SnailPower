

#include <Wire.h>
#include <DFRobot_ADS1115.h>




DFRobot_ADS1115 ads(&Wire);
int16_t data[700];


const int n = 690;
const int tps=30*1000;//time per sample
const int rest_time=3;



int k;
void setup(void)
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);


  Serial.begin(115200);
  ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS0);   // 0x48
  ads.setGain(eGAIN_TWOTHIRDS);   // 2/3x gain
  ads.setMode(eMODE_SINGLE);       // single-shot mode
  ads.setRate(eRATE_8);          // 128SPS (default)
  ads.setOSMode(eOSMODE_SINGLE);   // Set to start a single-conversion
  ads.init();

  





  if (ads.checkADS1115()) {
    digitalWrite(8, LOW);
    
    delay(10000);


    int t = 4000;
    for (k = 0; k < n; k++) {
      for(int t=0;t<rest_time;t++)
      {
         digitalWrite(8, LOW);
        delay(tps/rest_time);
        

      
      data[k] = (ads.readVoltage(0) + ads.readVoltage(0) + ads.readVoltage(0)) / 3.0 ;
        digitalWrite(8, HIGH);
        delay(tps/rest_time);
      }





      t = t * 0.97 + 0.03 * data[k];
//      if (i>2&&data[k]<2700&&(data[k]-data[k-1]<300)&&(data[k-1]-data[k]<300))  break;

      if (k % 40 == 0) {
        Serial.println();
        Serial.print(k / 40 + 1); Serial.println(":");
        delay(200);
      }
      Serial.print(data[k] ); Serial.print(",");
    }

  }
  digitalWrite(8, HIGH);

}

void loop(void)
{
  int i = 0;
  for (i = 0; i < k; i++) {
    if (i % 40 == 0) {
      Serial.println();
      Serial.print(i / 40 + 1); Serial.println(":");
      delay(200);
    }
    Serial.print(data[i] ); Serial.print(",");

  }
  Serial.println();
  Serial.println("\n---------------------------------");
  Serial.println();



}
