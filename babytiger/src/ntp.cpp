#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <RtcDS1307.h>
#include "rtc.h"
#include "ntp.h"

#define NTP_PACKET_SIZE 48
#define NTP_RTC_EPOCH_DIFFERENCE 3155673600 // seconds, 2000-1900

NTPState ntp_state = NTPState::UNAVAILABLE;

uint8_t ntp_buffer[NTP_PACKET_SIZE];
WiFiUDP ntp_udp_client;

unsigned long ntp_previous_request_millis = 0;
unsigned long ntp_previous_response_millis = 0;

void ntp_init() {
  ntp_udp_client.begin(123);
  ntp_state = NTPState::NOT_STARTED;
}

void ntp_destroy() {
  ntp_udp_client.stop();
  ntp_state = NTPState::UNAVAILABLE;
}

void ntp_update() {
  if (ntp_state == NTPState::UNAVAILABLE) return;

  unsigned long current_millis = millis();

  // Send request
  if ((ntp_state == NTPState::NOT_STARTED && ntp_previous_request_millis == 0) || current_millis - ntp_previous_request_millis > NTP_REQUEST_INTERVAL) {
    memset(ntp_buffer, 0, NTP_PACKET_SIZE);
    ntp_buffer[0] = 0b11100011;
    ntp_udp_client.beginPacket(NTP_SERVER, 123);
    ntp_udp_client.write(ntp_buffer, NTP_PACKET_SIZE);
    ntp_udp_client.endPacket();
    ntp_previous_request_millis = current_millis;
  }

  // Receive response
  if (ntp_udp_client.parsePacket()) {
    ntp_udp_client.read(ntp_buffer, NTP_PACKET_SIZE);
    uint32_t transmit_timestamp = (ntp_buffer[40] << 24) | (ntp_buffer[41] << 16) | (ntp_buffer[42] << 8) | ntp_buffer[43];
    RtcDateTime new_time(transmit_timestamp - NTP_RTC_EPOCH_DIFFERENCE);
    Rtc.SetDateTime(new_time);
    Serial.printf_P("[NTP] Time synchronized.\n");
    ntp_previous_response_millis = current_millis;
    ntp_state = NTPState::GOOD;
  }

  // Not receiving a response for a long time
  if (current_millis - ntp_previous_response_millis > NTP_NO_RESPONSE_THRESHOLD) {
    ntp_state = NTPState::NO_RESPONSE;
  }
}