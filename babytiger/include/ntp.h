#pragma once

#define NTP_SERVER "pool.ntp.org"
#define NTP_REQUEST_INTERVAL 600000UL
#define NTP_NO_RESPONSE_THRESHOLD 3600000UL

enum class NTPState {
  UNAVAILABLE, // not connect to internet
  NOT_STARTED, // have not synchronized since startup
  NO_RESPONSE, // have not received a response in NTP_NO_RESPONSE_THRESHOLD ms
  GOOD,        // everything is fine
};

extern NTPState ntp_state;
extern unsigned long ntp_previous_request_millis;
extern unsigned long ntp_previous_response_millis;

void ntp_init();
void ntp_destroy();
void ntp_update();