#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

#include <Arduino.h>
#include <ESP8266WebServer.h>

#define NUM_LEDS 890 //Make sure that its equal to L_ROWS * L_COLS
#define L_ROWS 11
#define L_COLS 81

const char* ssid = "dimensionless art studio";
const char* password = "Dimen@123";

ESP8266WebServer server ( 5045 );

boolean dataAvailable = false;
String data;
byte theme;
byte themeBrt;
byte themeBrtFade;
uint16_t themeSpd;
unsigned long themeClr;
boolean isRepeat;
boolean isApplyColor, isApplyBrt;
int hueInt;
unsigned long counter;
boolean showBlack;

//Temp variables
byte tThm, tBrt, tApply = 0;
boolean tApplyClr, tApplyBrt, fillLed;
uint16_t tSpd, tLed;
unsigned long tClr;
byte r, g, b;

CRGB leds[NUM_LEDS];
uint8_t hue[NUM_LEDS];
long ledsProc [L_ROWS][L_COLS];