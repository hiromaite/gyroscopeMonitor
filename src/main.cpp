#include <Arduino.h>
#include <M5Core2.h>
#undef min
AXP192 Axp;

void setup() {
  // Initialize M5Core2, Don't use M5.begin() cuz it conflicts with BLE initialization.
  Axp.begin();
  M5.Lcd.begin();
  M5.Lcd.setTextSize(3);
  M5.Rtc.begin();
  Serial.begin(115200);

}

void loop() {
  delay(1000);
}