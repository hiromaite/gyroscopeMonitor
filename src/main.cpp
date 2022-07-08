#include <Arduino.h>
#include <M5Core2.h>
#undef min
AXP192 Axp;

float accX = 0;
float accY = 0;
float accZ = 0;
float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;
float temp = 0;

void setup() {
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 0);

}

void loop() {
  delay(1000);
}