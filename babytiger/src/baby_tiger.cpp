#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include <Wire.h>
#include <RtcDS1307.h>
#include <SparkFunBME280.h>
#include "pins.h"
#include "buttons.h"
#include "rtc.h"
#include "ntp.h"
#include "alarms.h"
#include "modes.h"
#include "mode_clock.h"
#include "baby_tiger.h"

BME280 Bme;
WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(PIN_BTN_L, INPUT_PULLUP);
  pinMode(PIN_BTN_X, INPUT_PULLUP);
  pinMode(PIN_BTN_O, INPUT_PULLUP);
  pinMode(PIN_BTN_R, INPUT_PULLUP);
  // Interrupts seems always to trigger on change, even if set to falling
  attachInterrupt(digitalPinToInterrupt(PIN_BTN_L), handle_button_l, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_BTN_X), handle_button_x, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_BTN_O), handle_button_o, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_BTN_R), handle_button_r, CHANGE);

  pinMode(PIN_BUZZER, OUTPUT);

  LittleFS.begin();

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

  time_init();
  alarms_init();

  Bme.settings.commInterface = I2C_MODE;
  Bme.settings.I2CAddress = 0x76;
  Bme.settings.runMode = 3; // Normal mode
  Bme.settings.tStandby = 5; // 1000ms
  Bme.settings.filter = 4; // coefficient = 16
  Bme.settings.tempOverSample = 1;
  Bme.settings.pressOverSample = 1;
  Bme.settings.humidOverSample = 1;
  Bme.begin();

  WiFi.persistent(false);
  gotIpEventHandler = WiFi.onStationModeGotIP([&] (const WiFiEventStationModeGotIP &event) {
    ntp_init();
  });
  disconnectedEventHandler = WiFi.onStationModeDisconnected([&] (const WiFiEventStationModeDisconnected &event) {
    ntp_destroy();
  });
  WiFi.begin();

  // alarms_init();

  current_mode = new modes::Clock;
}

void loop() {
  ntp_update();

  if (next_mode) {
    delete current_mode;
    current_mode = next_mode;
    next_mode = nullptr;
  }
  current_mode->tick();
}