#include <Arduino.h>

#include <JustWifi.h>
//#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
//#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <FastLED.h>
#include <EEPROM.h>

#include "functions.h"
//#include "wifi_utils.cpp"

#define DEV_NAME  "InfinityRoom"

#define NUM_LEDS 890
#define PIN 4
#define LED_PIN 4
#define STRIP_TYPE WS2812B
#define COLOR_MODE GRB
CRGB leds[NUM_LEDS];
uint8_t hue[NUM_LEDS];

//Wifi
#define SSID1 "dimensionless art studio"
#define PASS1 "Dimen@123"
#define SSID2 "PurpleTulip"
#define PASS2 "Shaeed@&786"

ESP8266WebServer server ( 5045 );
DNSServer dnsServer;

boolean dataAvailable = false;

//Function prototypes
void mdnsCallback(justwifi_messages_t code, char * parameter);
void captivePortalCallback(justwifi_messages_t code, char * parameter);

extern void infoWifi(); //In wifi_utils.cpp
extern void infoCallback(justwifi_messages_t code, char * parameter); //In wifi_utils.cpp
