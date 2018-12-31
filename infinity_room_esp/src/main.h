#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include <EEPROM.h>
#include <FastLED.h>
#include "functions.h"
#include "hardware.h"
#include "themes.h"


//Wifi
extern const char* ssid;
extern const char* password;

extern ESP8266WebServer server;

extern boolean dataAvailable;
extern String data;
extern byte theme;
extern byte themeBrt;
extern byte themeBrtFade;
extern uint16_t themeSpd;
extern unsigned long themeClr;
extern boolean isRepeat;
extern boolean isApplyColor, isApplyBrt;
extern int hueInt;
extern unsigned long counter;
extern boolean showBlack;

//Temp variables
extern byte tThm, tBrt, tApply;
extern boolean tApplyClr, tApplyBrt, fillLed;
extern uint16_t tSpd, tLed;
extern unsigned long tClr;
extern byte r, g, b;

extern CRGB leds[NUM_LEDS];
extern uint8_t hue[NUM_LEDS];
extern long ledsProc [L_ROWS][L_COLS];