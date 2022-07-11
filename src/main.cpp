#include <Arduino.h>
#include <M5Core2.h>
#undef min
AXP192 Axp;

float accX, accY, accZ;
float myPitch, myRoll;
float avePitch, aveRoll;
int numAve = 10;
float listPitch[30], listRoll[30];
/* float* listPitch = new float(numAve);
float* listRoll = new float(numAve); */
float temp;

void vibrate(int msec = 100) {
  Axp.SetLDOEnable(3, true);
  delay(msec);
  Axp.SetLDOEnable(3, false);
}

void setup() {
  M5.begin();
  M5.IMU.Init();  // To use Port A, change the source file; "MPU6886.cpp" to use wire(32, 33) instead of wire1(21, 22) for I2C communication.
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  M5.update();
  // data acquisition
  M5.IMU.getAccelData(&accX, &accY, &accZ);

  // calcurate pitch
  myPitch = atan2(-accZ, sqrtf(accY * accY + accX * accX)) * RAD_TO_DEG;
  myRoll = atan2(accY, accX) * RAD_TO_DEG;

  // calcurate average
  float sumPitch = 0;
  float sumRoll = 0;
  for (int i = numAve - 1; i > 0; i--) {
    listPitch[i] = listPitch[i - 1];
    listRoll[i] = listRoll[i - 1];
    sumPitch += listPitch[i - 1];
    sumRoll += listRoll[i - 1];
  }
  listPitch[0] = myPitch;
  listRoll[0] = myRoll;
  avePitch = (sumPitch + listPitch[0]) / float(numAve);
  aveRoll = (sumRoll + listRoll[0]) / float(numAve);

  // feedback via LCD
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("%3.4f V %3.1f %%\n\n", Axp.GetBatVoltage(), Axp.GetBatteryLevel());

  M5.Lcd.setTextSize(3);
  M5.Lcd.print("ADC via. 10 fps\n");
  M5.Lcd.printf("Pitch: %3.1f deg.\n", myPitch);
  M5.Lcd.printf("Roll: %3.1f deg.\n\n", myRoll);
  M5.Lcd.print("Average at 10 sps\n");
  M5.Lcd.printf("Pitch: %3.1f deg.\n", avePitch);
  M5.Lcd.printf("Roll: %3.1f deg.\n", aveRoll);
  //vibrate(abs(aveRoll));
  delay(1000 / numAve);
}