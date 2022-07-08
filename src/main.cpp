#include <Arduino.h>
#include <M5Core2.h>
#undef min
AXP192 Axp;

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float pitch, roll, yaw;
float my_pitch;
float temp;

void setup() {
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);

}

void loop() {
  M5.update();
  // data acquisition
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);
  M5.IMU.getTempData(&temp);
  my_pitch = atan(-accX / sqrtf(accY * accY + accZ * accZ)) * RAD_TO_DEG;

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Pitch : %.2f deg\n", my_pitch);
  M5.Lcd.printf("Temp. : %.2f deg.C", temp);
  delay(1000);
}