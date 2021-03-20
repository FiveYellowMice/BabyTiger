#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266TrueRandom.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "buttons.h"
#include "modes.h"
#include "mode_settings.h"
#include "mode_wifi_setup.h"

#define PREPARE_ERROR_SCREEN(message) { \
  strncpy_P(error, PSTR(message), sizeof(error) - 1); \
  scroll_text_set_text(&error_scroll, error); \
  scroll_text_reset(&error_scroll); \
  button_press_clear(); \
} while(0);

const PROGMEM char* HTTP_RESPONSE_REDIRECT =
  "HTTP/1.1 302 Found\n"
  "Connection: close\n"
  "Location: http://192.168.4.1/wifi-setup\n"
  "\n";

const PROGMEM char* HTTP_RESPONSE_SETUP_PAGE = 
  "HTTP/1.1 200 OK\n"
  "Connection: close\n"
  "\n"
  "<!DOCTYPE html>"
  "<meta charset=\"utf-8\">"
  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
  "<form method=\"post\">"
  "<label>SSID: <input name=\"ssid\" type=\"text\"></label><br>"
  "<label>Password: <input name=\"password\" type=\"password\"></label><br>"
  "<button type=\"submit\">Enter</button>"
  "</form>"
  "<p style=\"color: gray\">MAC address of this device: ";

const PROGMEM char* HTTP_RESPONSE_FORM_SUBMITTED =
  "HTTP/1.1 200 OK\n"
  "Connection: close\n"
  "\n"
  "<!DOCTYPE html>"
  "<meta charset=\"utf-8\">"
  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
  "<p>Attemping to connect to WiFi. Please close this page. You may also want to remove this WiFi from the list of saved networks on your device.</p>";

const PROGMEM char* HTTP_RESPONSE_NOT_FOUND =
  "HTTP/1.1 404 Not Found\n"
  "Connection: close\n"
  "\n"
  "Not found.";

const PROGMEM char* HTTP_RESPONSE_BAD_REQUEST =
  "HTTP/1.1 400 Bad Request\n"
  "Connection: close\n"
  "\n"
  "Bad request.";

namespace modes {

  WiFiSetup::WiFiSetup() : server(80) {
    scroll_text_init(
      &error_scroll,
      "", fonts::ascii7, COLOR_WHITE,
      0, 5, SCROLL_TEXT_MODE_ADAPTIVE,
      800, 60
    );

    WiFi.softAPmacAddress(mac_addr);
    snprintf_P(wifi_ssid, sizeof(wifi_ssid), PSTR("ESP_%02X%02X%02X"), mac_addr[3], mac_addr[4], mac_addr[5]);
    snprintf_P(wifi_password, sizeof(wifi_password), PSTR("%06ld"), ESP8266TrueRandom.random(100000000));
    wifi_channel = (uint8_t) ESP8266TrueRandom.random(1, 11);
  }

  void WiFiSetup::tick() {
    if (error[0]) {
      draw_text("ERR:", fonts::digits5, COLOR_RED, 0, 0);
      scroll_text_update(&error_scroll);
      draw_glyph(&fonts::cross, COLOR_RED, 4, 13);
      display();
      clear_pixels();
      button_event_handle(BTN_X, [&] {
        transition_mode(new modes::WiFiSetup);
      });
      button_press_clear();
      return;
    }

    // User has completed entering SSID and password, and disconnected
    if (!client && entered_ssid && entered_password) {
      if (ap_initialized) {
        // Close server and AP
        server.close();
        if (!WiFi.softAPdisconnect(true)) {
          PREPARE_ERROR_SCREEN("Cannot stop soft AP.");
        }
        ap_initialized = false;
        // Start station mode
        WiFi.persistent(true);
        WiFi.begin(entered_ssid, entered_password);
        WiFi.setAutoConnect(true);
        WiFi.setAutoReconnect(true);
        WiFi.persistent(false);
        return;
      }

      // Connect to the AP user has entered
      switch (WiFi.status()) {
        case WL_DISCONNECTED:
        case WL_IDLE_STATUS:
          // Play animation in the center 4 pixels of the screen
          switch ((millis() / 128) % 4) {
            case 0:
              set_pixel(7, 7, COLOR_BLUE);
              break;
            case 1:
              set_pixel(8, 7, COLOR_BLUE);
              break;
            case 2:
              set_pixel(8, 8, COLOR_BLUE);
              break;
            case 3:
              set_pixel(7, 8, COLOR_BLUE);
              break;
          }
          display();
          clear_pixels();
          button_press_clear();
          break;
        case WL_CONNECTED:
          draw_glyph(&fonts::tick, COLOR_GREEN, 6, 6);
          draw_glyph(&fonts::circle, COLOR_GRAY, 9, 13);
          display();
          clear_pixels();
          button_event_handle(BTN_O, [&] {
            transition_mode(new modes::Settings(SettingsMenuSelection::WIFI));
          });
          button_press_clear();
          break;

        case WL_NO_SSID_AVAIL:
          PREPARE_ERROR_SCREEN("SSID unreachable.");
          break;
        case WL_CONNECT_FAILED:
        default:
          PREPARE_ERROR_SCREEN("Connection failed.");
      }

      return;
    }

    // When we have just entered the mode
    if (!sta_disconnect_started) {
      WiFi.disconnect(true);
      sta_disconnect_started = true;
      return;
    }

    if (!ap_initialized) {
      // Wait until WiFi is disconnected
      if (WiFi.status() != WL_DISCONNECTED) {
        switch ((millis() / 128) % 4) {
          case 0:
            set_pixel(7, 7, COLOR_ORANGE);
            break;
          case 1:
            set_pixel(8, 7, COLOR_ORANGE);
            break;
          case 2:
            set_pixel(8, 8, COLOR_ORANGE);
            break;
          case 3:
            set_pixel(7, 8, COLOR_ORANGE);
            break;
        }
        display();
        clear_pixels();
        button_press_clear();
      // Start soft AP after station mode has ended
      } else {
        if (WiFi.softAP(wifi_ssid, wifi_password, wifi_channel)) {
          ap_initialized = true;
          server.begin();
          switchDisplay();
        } else {
          PREPARE_ERROR_SCREEN("Cannot start soft AP.");
        }
      }
      return;
    }

    button_event_handle(BTN_R, [&] {
      switchDisplay();
    });
    button_press_clear();

    // Wait for clients
    if (!client.connected()) {
      client = server.available();
      if (client) {
        // If we have a client, reset state variables
        client_connect_time = millis();
        progressHTTPStage(WiFiSetupHTTPStage::REQUEST_START); // implicitly clears request buffer
        http_request_method = WiFiSetupHTTPMethod::UNDEFINED;
        memset(http_request_path, 0, sizeof(http_request_path));
        http_request_content_length_remaining = 0;
        http_response_ptr = nullptr;
        memset(http_response_extra, 0, sizeof(http_response_extra));
        http_response_extra_ptr = nullptr;
      }

    // Ongoing connection
    } else {
      // Close clients connected for over 30 seconds
      if (millis() - client_connect_time > 30000) {
        client.stop();
      }

      // Read request into buffer for stages prior to REQUEST_BODY
      if (http_stage < WiFiSetupHTTPStage::REQUEST_BODY) {
        last_read_char = '\0';
        if (!client.available()) {
          goto after_client_read;
        }
        if (http_request_buffer_occupancy + 1 == sizeof(http_request_buffer)) { // if buffer will overflow
          progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
          return;
        }
        last_read_char = client.read();
        if (last_read_char == '\0') {
          progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
          return;
        }
        if (last_read_char == '\r') {
          // Ignore '\r'
          last_read_char = '\0';
          goto after_client_read;
        }
        http_request_buffer[http_request_buffer_occupancy++] = last_read_char;
      }
      after_client_read:

      switch (http_stage) {

        case WiFiSetupHTTPStage::REQUEST_START:
          if (last_read_char && (last_read_char < 'A' || last_read_char > 'Z')) {
            if (last_read_char == ' ') {
              if (strcmp_P(http_request_buffer, PSTR("HEAD ")) == 0) {
                http_request_method = WiFiSetupHTTPMethod::HEAD;
              } else if (strcmp_P(http_request_buffer, PSTR("GET ")) == 0) {
                http_request_method = WiFiSetupHTTPMethod::GET;
              } else if (strcmp_P(http_request_buffer, PSTR("POST ")) == 0) {
                http_request_method = WiFiSetupHTTPMethod::POST;
              } else {
                progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
                return;
              }
              progressHTTPStage(WiFiSetupHTTPStage::REQUEST_PATH);
            } else {
              progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
            }
          }
          break;

        case WiFiSetupHTTPStage::REQUEST_PATH:
          if (last_read_char == ' ' || last_read_char == '?') {
            if (http_request_buffer_occupancy > sizeof(http_request_path) - 1) { // path too long
              progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
              return;
            }
            strcpy(http_request_path, http_request_buffer); // omit size check because of the above if
            http_request_path[http_request_buffer_occupancy - 1] = '\0'; // remove last char (' ' or '?') from path
            progressHTTPStage(last_read_char == '?' ? WiFiSetupHTTPStage::REQUEST_QUERY : WiFiSetupHTTPStage::REQUEST_HTTP_VERSION);
          }
          break;

        case WiFiSetupHTTPStage::REQUEST_QUERY:
          if (last_read_char == ' ') {
            progressHTTPStage(WiFiSetupHTTPStage::REQUEST_HTTP_VERSION);
          }
          break;

        case WiFiSetupHTTPStage::REQUEST_HTTP_VERSION:
          if (last_read_char == '\n') {
            if (strcmp_P(http_request_buffer, PSTR("HTTP/1.1\n")) == 0) {
              progressHTTPStage(WiFiSetupHTTPStage::REQUEST_HEADER_NAME);
            } else {
              progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
            }
          }
          break;

        case WiFiSetupHTTPStage::REQUEST_HEADER_NAME:
          if (!last_read_char) {
            // Do nothing
          } else if (last_read_char == '\n') {
            progressHTTPStage(WiFiSetupHTTPStage::REQUEST_BODY);
          } else if ((last_read_char >= 'A' && last_read_char <= 'Z') || (last_read_char >= 'a' && last_read_char <= 'z') || last_read_char == '-') {
            // Clear buffer if it's almost full, therefore ignore super long header names
            if (http_request_buffer_occupancy >= sizeof(http_request_buffer) - 1) {
              clearRequestBuffer();
            }
          } else if (last_read_char == ':') {
            // Header name ends, do nothing
          } else if (last_read_char == ' ') {
            if (!(http_request_buffer_occupancy >= 2 && http_request_buffer[http_request_buffer_occupancy - 2] == ':')) { // if previous char is not ':'
              progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
            } else if (strcmp_P(http_request_buffer, PSTR("Content-Length: ")) == 0) {
              progressHTTPStage(WiFiSetupHTTPStage::REQUEST_HEADER_CONTENT_LENGTH);
            } else {
              progressHTTPStage(WiFiSetupHTTPStage::REQUEST_HEADER_UNIMPORTANT);
            }
          } else {
            progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
          }
          break;

        case WiFiSetupHTTPStage::REQUEST_HEADER_CONTENT_LENGTH:
          if (last_read_char == '\n') {
            http_request_content_length_remaining = atoi(http_request_buffer);
            progressHTTPStage(WiFiSetupHTTPStage::REQUEST_HEADER_NAME);
          } else if (last_read_char && (last_read_char < '0' || last_read_char > '9')) {
            progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
          }
          break;

        case WiFiSetupHTTPStage::REQUEST_HEADER_UNIMPORTANT:
          if (last_read_char == '\n') {
            progressHTTPStage(WiFiSetupHTTPStage::REQUEST_HEADER_NAME);
          } else {
            clearRequestBuffer();
          }
          break;

        case WiFiSetupHTTPStage::REQUEST_BODY:
          if (http_request_method == WiFiSetupHTTPMethod::POST) {
            // Read a request body for POST requests
            if (http_request_content_length_remaining) {
              last_read_char = '\0';
              if (!client.available()) {
                return;
              }
              if (http_request_buffer_occupancy + 1 == sizeof(http_request_buffer)) { // if buffer will overflow
                progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
                return;
              }
              last_read_char = client.read();
              http_request_buffer[http_request_buffer_occupancy++] = last_read_char;
              http_request_content_length_remaining--;
            } else {
              progressHTTPStage(WiFiSetupHTTPStage::RESPONSE_START);
            }
          } else {
            // Ignore request body for others
            progressHTTPStage(WiFiSetupHTTPStage::RESPONSE_START);
          }
          break;

        // Buffer is not cleared when progressing to RESPONSE_START or higher

        case WiFiSetupHTTPStage::RESPONSE_START:
          // Start sending a normal response
          if (strcmp(http_request_path, "/") == 0) {
            if (http_request_method == WiFiSetupHTTPMethod::GET || http_request_method == WiFiSetupHTTPMethod::HEAD) {
              http_response_ptr = HTTP_RESPONSE_REDIRECT;
              progressHTTPStage(WiFiSetupHTTPStage::RESPONSE_SEND);
            } else {
              progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
            }
          } else if (strcmp_P(http_request_path, PSTR("/wifi-setup")) == 0) {
            if (http_request_method == WiFiSetupHTTPMethod::GET || http_request_method == WiFiSetupHTTPMethod::HEAD) {
              http_response_ptr = HTTP_RESPONSE_SETUP_PAGE;
              snprintf_P(http_response_extra, sizeof(http_response_extra), PSTR("%02X:%02X:%02X:%02X:%02X:%02X</p>"),
                mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
              http_response_extra_ptr = http_response_extra;
              progressHTTPStage(WiFiSetupHTTPStage::RESPONSE_SEND);
            } else if (http_request_method == WiFiSetupHTTPMethod::POST) {
              if (parseForm()) {
                http_response_ptr = HTTP_RESPONSE_FORM_SUBMITTED;
                progressHTTPStage(WiFiSetupHTTPStage::RESPONSE_SEND);
              } else {
                progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
              }
            } else {
              progressHTTPStage(WiFiSetupHTTPStage::BAD_REQUEST);
            }
          } else {
            http_response_ptr = HTTP_RESPONSE_NOT_FOUND;
            progressHTTPStage(WiFiSetupHTTPStage::RESPONSE_SEND);
          }
          break;

        case WiFiSetupHTTPStage::BAD_REQUEST:
          http_response_ptr = HTTP_RESPONSE_BAD_REQUEST;
          progressHTTPStage(WiFiSetupHTTPStage::RESPONSE_SEND);
          break;

        case WiFiSetupHTTPStage::RESPONSE_SEND:
          char sending_char;
          // Send hardcoded response first
          if (http_response_ptr && (sending_char = pgm_read_byte(http_response_ptr))) {
            http_response_ptr++;
            client.write(sending_char);
          // Send dynamically generated response second
          } else if (http_response_extra_ptr && (sending_char = *http_response_extra_ptr)) {
            http_response_extra_ptr++;
            client.write(sending_char);
          // Close connection last
          } else {
            client.stop();
          }
          break;
      }
    }
  }

  void WiFiSetup::switchDisplay() {
    switch (info_display) {
      case 0: // Show SSID
        draw_text(wifi_ssid, fonts::digits5, COLOR_GREEN, 0, 0); // draw "ESP_"
        draw_text(wifi_ssid + 4, fonts::digits5, COLOR_TENDER_GREEN, 0, 5); // draw "28FC"
        draw_text(wifi_ssid + 8, fonts::digits5, COLOR_TENDER_GREEN, 0, 11); // draw "B9"
        draw_glyph(&fonts::triangle_right, COLOR_ORANGE, 14, 13);
        break;
      case 1: // Show password
        draw_text(wifi_password, fonts::digits5, COLOR_ORANGE, 0, 0);
        draw_text(wifi_password + 4, fonts::digits5, COLOR_ORANGE, 0, 6);
        draw_glyph(&fonts::triangle_right, COLOR_BLUE, 14, 13);
        break;
      case 2: // Show IP address
        draw_text("192.", fonts::digits5, COLOR_BLUE, 0, 0);
        draw_text("168.", fonts::digits5, COLOR_BLUE, 0, 6);
        draw_text("4.1", fonts::digits5, COLOR_LAKE_BLUE, 0, 11);
        draw_glyph(&fonts::triangle_right, COLOR_TENDER_GREEN, 14, 13);
        break;
    }

    info_display = (info_display + 1) % 3;

    display();
    clear_pixels();
  }

  void WiFiSetup::clearRequestBuffer() {
    last_read_char = '\0';
    memset(http_request_buffer, 0, sizeof(http_request_buffer));
    http_request_buffer_occupancy = 0;
  }

  void WiFiSetup::progressHTTPStage(WiFiSetupHTTPStage new_stage) {
    http_stage = new_stage;
    if (http_stage < WiFiSetupHTTPStage::RESPONSE_START) {
      clearRequestBuffer();
    }
  }

  bool WiFiSetup::parseForm() {
    // Parse http_request_buffer, which may contain "ssid=xxxx&password=xxxxx"
    // Parsed values's pointers are stored in object members,
    // which, since are used as indicator of successful submittion, are set to null on failure
    entered_ssid = http_request_buffer;

    if (strncmp_P(entered_ssid, PSTR("ssid="), 5) != 0) goto failure;
    entered_ssid += 5;

    entered_password = strchr(entered_ssid, '&');
    if (!entered_password) goto failure;
    entered_password[0] = '\0'; // create null byte at the end of entered_ssid (overwrites '&')
    entered_password++;

    if (strncmp_P(entered_password, PSTR("password="), 9) != 0) goto failure;
    entered_password += 9;

    if (strchr(entered_password, '&')) goto failure;

    if (!decodeURIComponent(entered_ssid)) {
      goto failure;
    }
    if (!decodeURIComponent(entered_password)) {
      goto failure;
    }

    if (
      strlen(entered_ssid) == 0 ||
      strlen(entered_ssid) > 32 ||
      strlen(entered_password) < 8 ||
      strlen(entered_password) > 63
    ) {
      goto failure;
    }

    return true;

    failure:
    entered_ssid = nullptr;
    entered_password = nullptr;
    return false;
  }

  bool WiFiSetup::decodeURIComponent(char* str) {
    // Decode URI encoded string, overwrite original memory location,
    // this is fine because the decoded string is always going to be shorter or equal in length
    if (!str) return false;
    char *out = str;
    char *in = str;
    char decoded_char;
    while (in[0]) {
      if (in[0] == '%') {
        decoded_char = 0;
        for (uint8_t j = 1; j < 3; j++) { // read 2 characters ahead
          if (in[j] >= '0' && in[j] <= '9') {
            decoded_char |= in[j] - '0';
          } else if (in[j] >= 'a' && in[j] <= 'f') {
            decoded_char |= in[j] - 'a' + 0xA;
          } else if (in[j] >= 'A' && in[j] <= 'F') {
            decoded_char |= in[j] - 'A' + 0xA;
          } else { // unexpected char or null
            return false;
          }
          if (j == 1) {
            decoded_char = decoded_char << 4;
          }
        }
        // NOTE: if there is "%00", it will result in an early-terminated string, but this should be fine
        out[0] = decoded_char;
        in += 2;
      } else if (in[0] == '+') {
        out[0] = ' ';
      } else {
        out[0] = in[0];
      }
      in++;
      out++;
    }
    out[0] = '\0'; // null terminate the output
    return true;
  }

}