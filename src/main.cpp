#include <Arduino.h>
#include <hot.h>
#include <r.h>
#include <ADC.h>
#include <pid.h>
#include <BluetoothSerial.h>
#include <HardwareSerial.h>    
#include <ESP32_l298n.h>
float hot_temp;
float cold_temp;
double voltage;
//pid初始化
float cold_p=0.05;
float cold_i=0.001;
float cold_d=0.001;
float cold_integral=0;
float cold_integralmax=100;
float cold_outputmin=0;
float cold_outputmax=100;
float cold_lateerr=0;
//pid初始化
float wind_p=0.05;
float wind_i=0.001;
float wind_d=0.001;
float wind_integral=0;
float wind_integralmax=100;
float wind_outputmin=0;
float wind_outputmax=100;
float wind_lateerr=0;

PID cold_pid={cold_p,cold_i,cold_d,cold_integral,cold_integralmax,cold_outputmin,cold_outputmax,cold_lateerr};
PID wind_pid={wind_p,wind_i,wind_d,wind_integral,wind_integralmax,wind_outputmin,wind_outputmax,wind_lateerr};
uint8_t MAX6675_hot_CLK=18;
uint8_t MAX6675_hot_CS=19;
uint8_t MAX6675_hot_DO=22;

uint8_t MAX6675_cold_CLK=18;
uint8_t MAX6675_cold_CS=19;
uint8_t MAX6675_cold_DO=21;
BluetoothSerial SerialBT;
ESP32_L298N wind_make(4,5,0,1,true);
ESP32_L298N cold_make(32,33,2,3,true);
HardwareSerial MySerial(0);  
MAX6675 hot_thermocouple(MAX6675_hot_CLK, MAX6675_hot_CS, MAX6675_hot_DO);
MAX6675 cold_thermocouple(MAX6675_cold_CLK, MAX6675_cold_CS, MAX6675_cold_DO);
float wind_speed=0;
float cold_speed=0;
int text[2];

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("hua1"); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
    SerialBT.setPin("1234");   // 蓝牙连接的配对码
    Serial.printf("BT initial ok and ready to pair. \r\n");
    MySerial.begin(115200, SERIAL_8N1, 1, 3);
    MySerial.printf("Serial initial ok and ready to pair. \r\n");
    
    
    text[0]=0;
}
int32_t now_temp=0;
int32_t aim_temp=0;
int32_t now_wind=0;
int32_t aim_wind=0;
int32_t wind_pid_output=0;
int32_t cold_pid_output=0;

void loop()
{   
    //cold_pid_output=PID_Cal(&cold_pid,now_temp, aim_temp);
    //wind_pid_output=PID_Cal(&wind_pid,now_wind, aim_wind);
    delay(10);
    hot_temp=hot_thermocouple.readCelsius();
    delay(10);
    cold_temp=cold_thermocouple.readCelsius();
   
    if(SerialBT.available())
   {
      text[1]=SerialBT.read();
      wind_speed=text[1];
    }
    wind_make.drive(wind_speed);
    cold_make.drive(cold_speed);
    SerialBT.printf("TEXT:%d\r\n",text[1]);
    SerialBT.printf("SPEAD:%f\r\n",wind_speed);
    SerialBT.printf("voltage:%f\r\n",voltage);
    SerialBT.printf("hot_temp:%f\r\n",hot_temp);
    SerialBT.printf("cold_temp:%f\r\n",cold_temp);
    MySerial.printf("hot_temp:%f\r\n",hot_temp);
    MySerial.printf("cold_temp:%f\r\n",cold_temp);

}