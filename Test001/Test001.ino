#include "Encoder2.h"
//#include "Current_sensor.h"
#include <string>
#include <Wire.h>
#include <INA226_WE.h>
#define I2C_ADDRESS 0x40

String command;

struct DataPacket {
  float voltb = 0;  //4 ไบต์
  float velob = 0;  //4 ไบต์
  float currb = 0;  //4 ไบต์
  float voltl = 0;  //4 ไบต์
  float templ = 0;  //4 ไบต์
  float currl = 0;  //4 ไบต์
  float volta = 0;  //4 ไบต์
  float curra = 0;  //4 ไบต์
  int xl = 0;
  int yl = 0;
};
int i = 0;
Encoder myEncoder(0, 1, 2340.0, 100);
//CurrentSensor sensor(A0, 960, 66, 10);
INA226_WE ina226 = INA226_WE(I2C_ADDRESS);

void setup() {
  Serial.begin(9600);
  Encoder::setInstance(&myEncoder);  // Set the instance pointer
  myEncoder.begin();
  //sensor.begin();
  Wire.begin();
  ina226.init();
  ina226.setResistorRange(0.1, 1.3);
  ina226.setCorrectionFactor(0.93);
  ina226.waitUntilConversionCompleted();
}

void loop() {
  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0;
  if (i = 0)
  {
    delay(100);
    i = 1;
  }
  ina226.readAndClearFlags();
  shuntVoltage_mV = ina226.getShuntVoltage_mV();
  busVoltage_V = ina226.getBusVoltage_V();
  current_mA = ina226.getCurrent_mA();
  power_mW = ina226.getBusPower();
  loadVoltage_V = busVoltage_V + (shuntVoltage_mV / 1000.0);

  myEncoder.update();
  //sensor.update();
  DataPacket data;
  //data.voltb = 1;
  data.velob = (round(myEncoder.get_velocity() * 1000.0) / 1000.0)*0.006;
  //Serial.println(to_string(round(myEncoder.get_velocity()*1000)/1000));
  //Serial.println(myEncoder.get_velocity());
  //Serial.println(data.velob);
  data.currb = current_mA / 1000.0;
  //data.currb = round(sensor.get_current() * 1000) / 1000;
  //Serial.println(data.currb);

  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');  // อ่านคำสั่งที่ส่งมาจาก serial

    if (command == "Shutdown") {
      Serial.println(command);
      analogWrite(2, 0);
      analogWrite(3, 0);
      digitalWrite(25, 1);
      // while (1)
      // {

      // }
    }
  }
  if (command != "Shutdown") {
    analogWrite(2, 255);
    analogWrite(3, 0);                                                                                                                                 
    Serial.print("<");
    Serial.print(loadVoltage_V);
    Serial.print(",");
    Serial.print(data.velob, 3);
    Serial.print(",");
    Serial.print(data.currb, 3);
    Serial.print(",");
    Serial.print(data.voltl, 3);
    Serial.print(",");
    Serial.print(data.templ);
    Serial.print(",");
    Serial.print(data.currl, 3);
    Serial.print(",");
    Serial.print(data.xl);
    Serial.print(",");
    Serial.print(data.yl);
    Serial.print(",");
    Serial.print(data.volta, 3);
    Serial.print(",");
    Serial.print(data.curra, 3);
    Serial.println(">");
    //Serial.write('<');  // เริ่ม
    //Serial.write((byte*)&data, sizeof(data));  // ข้อมูล 12 ไบต์
    //Serial.write('>');  // หยุด
    delay(100);
  }
}