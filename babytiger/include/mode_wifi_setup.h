#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <ESP8266WiFi.h>
#include "modes.h"
#include "scroll_text.h"

namespace modes {

  enum class WiFiSetupHTTPStage {
    REQUEST_START,
    REQUEST_PATH,
    REQUEST_QUERY,
    REQUEST_HTTP_VERSION,
    REQUEST_HEADER_NAME,
    REQUEST_HEADER_CONTENT_LENGTH,
    REQUEST_HEADER_UNIMPORTANT,
    REQUEST_BODY,

    RESPONSE_START,
    BAD_REQUEST,
    RESPONSE_SEND,
  };

  enum class WiFiSetupHTTPMethod {
    UNDEFINED,
    HEAD,
    GET,
    POST,
  };

  class WiFiSetup: public Mode {

      char error[41] = {'\0'};
      ScrollingText error_scroll;

      bool sta_disconnect_started = false;
      bool ap_initialized = false;
      uint8_t info_display = 0;
      uint8_t mac_addr[6];
      char wifi_ssid[11]; // "ESP_XXXXXX"
      char wifi_password[9]; // 8-digit password
      uint8_t wifi_channel;

      WiFiServer server;
      WiFiClient client;
      unsigned long client_connect_time = 0;

      WiFiSetupHTTPStage http_stage = WiFiSetupHTTPStage::REQUEST_START;
      char http_request_buffer[65] = {'\0'}; // should be at least the size max possible request body
      // however, SSID is max 32 bytes, password is max 63, adds "ssid=&password=" (15) overhead, its too much memory for my liking
      // so we just don't allow long values
      uint8_t http_request_buffer_occupancy = 0;
      char last_read_char = '\0';

      WiFiSetupHTTPMethod http_request_method = WiFiSetupHTTPMethod::UNDEFINED;
      char http_request_path[13] = {'\0'}; // must fit "/wifi-setup " (12)
      uint8_t http_request_content_length_remaining = 0;
      const char* http_response_ptr = nullptr; // pointer to progmem
      char http_response_extra[22] = {'\0'}; // must fit "XX:XX:XX:XX:XX:XX</p>" (21)
      char* http_response_extra_ptr = nullptr;

      // These points to locations in http_request_buffer
      char* entered_ssid = nullptr;
      char* entered_password = nullptr;

    public:
      WiFiSetup();
      void tick();

    private:
      void switchDisplay();
      void clearRequestBuffer();
      void progressHTTPStage(WiFiSetupHTTPStage new_stage);
      bool parseForm();
      bool decodeURIComponent(char* str);
  };

}