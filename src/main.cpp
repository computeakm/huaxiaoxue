#include <Arduino.h>
#include <hot.h>
#include <r.h>
#include <ADC.h>
#include <BluetoothSerial.h>
#include <HardwareSerial.h>    
#include <ESP32_l298n.h>
float hot_temp;
float cold_temp;
double voltage;
uint8_t MAX6675_hot_CLK=18;
uint8_t MAX6675_hot_CS=19;
uint8_t MAX6675_hot_DO=22;

uint8_t MAX6675_cold_CLK=18;
uint8_t MAX6675_cold_CS=19;
uint8_t MAX6675_cold_DO=21;
BluetoothSerial SerialBT;
ESP32_L298N cold_make(15,2);
ESP32_L298N wind_make(15,2);
HardwareSerial MySerial(0);  
MAX6675 hot_thermocouple(MAX6675_hot_CLK, MAX6675_hot_CS, MAX6675_hot_DO);
MAX6675 cold_thermocouple(MAX6675_cold_CLK, MAX6675_cold_CS, MAX6675_cold_DO);
float speed=200;
void setup()
{
    Serial.begin(115200);
    SerialBT.begin("hua"); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
    SerialBT.setPin("1234");   // 蓝牙连接的配对码
    Serial.printf("BT initial ok and ready to pair. \r\n");
    MySerial.begin(115200, SERIAL_8N1, 1, 3);
    MySerial.printf("Serial initial ok and ready to pair. \r\n");
    cold_make.drive(speed);
    wind_make.drive(speed);
}

void loop()
{
    voltage=ReadVoltage(4);
    hot_temp=hot_thermocouple.readCelsius();
    cold_temp=cold_thermocouple.readCelsius();
    SerialBT.printf("SPEAD:%f\r\n",speed);
    SerialBT.printf("voltage:%f\r\n",voltage);
    SerialBT.printf("hot_temp:%f\r\n",hot_temp);
    SerialBT.printf("cold_temp:%f\r\n",cold_temp);
    MySerial.printf("hot_temp:%f\r\n",hot_temp);
    MySerial.printf("cold_temp:%f\r\n",cold_temp);

}