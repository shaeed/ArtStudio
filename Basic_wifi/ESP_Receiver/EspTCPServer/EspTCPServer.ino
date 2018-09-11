#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>

//LED 
#define NUM_LEDS 300
#define LED_PIN 4
#define STRIP_TYPE WS2812B
#define COLOR_MODE GRB
CRGB leds[NUM_LEDS];

//Wifi
const char* ssid = "WhiteRose";
const char* password = "shaeed1199";

// Start a TCP Server on port 5045
WiFiServer server(5045);
WiFiClient client;

//Setup constants
#define THEME_OFF         1 
#define THEME_ON          2 
#define THEME_RAINBOW     3 
#define THEME_STROBE      4 
#define THEME_ALLWHITE    5 
#define THEME_COLORFUL    6 
#define THEME_FADE        7 
#define THEME_SPIRAL      8 
#define THEME_BLINK       9 
#define THEME_NIGHTSKY    10
#define THEME_CUSTOM      100

#define DELAY_APPLY_COLOR_ALL 100

//Globals
boolean dataAvailable = false;
String data;

byte theme;
byte themeBrt;
byte themeBrtFade;
uint16_t themeSpd;
unsigned long themeClr;
boolean isRepeat;
boolean isApplyColor, isApplyBrt;
int hue;
unsigned long counter;
boolean showBlack;

byte tThm, tBrt;
boolean tApply = false, tApplyClr, tApplyBrt, fillLed;
uint16_t tSpd, tLed;
unsigned long tClr;

void processData(){
  dataAvailable = false;
  //Sample formt
  //T 1;B 123;S 12;C 123456;A 1;
  int start = 0, endd = 0;
  String t;
  byte ld = data.length();
  Serial.println(ld);
  
  while(endd < ld){
    Serial.println(String(endd) + " " + String(start));
    endd = data.indexOf(';', start);
    if(endd == -1)
      break;
    t = data.substring(start, endd);
    Serial.println(t);
    switch(t.charAt(0)){
      case 'A':
        tApply = true;
        break;
        
      case 'B':
        t = t.substring(2);
        tBrt = t.toInt();
        tApplyBrt = true;
        break;
        
      case 'C':
        t = t.substring(2);
        tClr = t.toInt();
        tApplyClr = true;
        break;
        
      case 'L':
        t = t.substring(2);
        tLed = t.toInt();
        fillLed = true;
        break;
        
      case 'S':
        t = t.substring(2);
        tSpd = t.toInt();
        break;
        
      case 'T':
        t = t.substring(2);
        tThm = t.toInt();
        break;
    }//End switch
    start = endd + 1;
  }//End while

  Serial.println("T " + String(tThm) + ", B " + String(tBrt) + ", C " + String(tClr) + ", S " + String(tSpd) + ", App " + String(tApply));
}

void applyLed(){
  tApply = false;
  themeBrt = tBrt;
  themeSpd = tSpd;
  themeClr = tClr;
  theme = tThm;
  isRepeat = true;
  isApplyColor = tApplyClr;
  isApplyBrt = tApplyBrt;
  
  counter = 0;
  hue = 0;
  themeBrtFade = themeBrt;
}

void executeLED(){
  if(isApplyBrt)
    FastLED.setBrightness(themeBrt);
  switch(theme){
    case THEME_OFF:
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        isRepeat = false;
        delay(DELAY_APPLY_COLOR_ALL);
        FastLED.show();
        break;
        
    case THEME_RAINBOW:
         fill_rainbow(leds, NUM_LEDS, hue, 5);
         FastLED.show();
         hue = hue + themeSpd;
        break;
        
    case THEME_STROBE:
        if(counter >= 1000 * themeSpd){
          counter = 0;
          if(showBlack){
            fill_solid(leds, NUM_LEDS, CRGB::Black);
            delay(DELAY_APPLY_COLOR_ALL);
            FastLED.show();
            //delay(600);
            showBlack = false;
          } else {
            /*for(int i=0; i< NUM_LEDS; i++) {
              leds[i] = CRGB(255, 0, 0);
            }*/
            fill_solid(leds, NUM_LEDS, themeClr);
            delay(DELAY_APPLY_COLOR_ALL);
            FastLED.show();
            showBlack = true;
          }
        }
        counter++;
        break;
        
    case THEME_ALLWHITE:
        fill_solid(leds, NUM_LEDS, CRGB::White);
        delay(DELAY_APPLY_COLOR_ALL);
        FastLED.show();
        isRepeat = false;
        break;
        
    case THEME_COLORFUL:
        fill_solid(leds, NUM_LEDS, themeClr);
        /*for(int i=0; i< NUM_LEDS; i++)
        {  
          leds[i] = themeClr;
        }*/
        delay(DELAY_APPLY_COLOR_ALL);
        FastLED.show();
        isRepeat = false;
        break;
        
    case THEME_FADE:
        if(isApplyColor){
          fill_solid(leds, NUM_LEDS, themeClr);
          delay(DELAY_APPLY_COLOR_ALL);
          isApplyColor = false;
        }
        if(counter >= 1000 * themeSpd){
          counter = 0;
          if(showBlack){
            //Fade in
            FastLED.setBrightness(themeBrtFade);
            themeBrtFade++;
            delay(2);
            FastLED.show();
            if(themeBrtFade > themeBrtFade)
              showBlack = false;
          } else {
            //Fade out
            FastLED.setBrightness(themeBrtFade);
            themeBrtFade--;
            delay(2);
            FastLED.show();
            if(themeBrtFade < 1)
              showBlack = true;
          }
        }
        counter++;
        break;
        
    case THEME_SPIRAL:
        
        break;
        
    case THEME_BLINK:
        
        break;
        
    case THEME_NIGHTSKY:
        
        break;
        
    case THEME_CUSTOM:
        FastLED.show();
        break;
  }
}

void fillLedData(){
  fillLed = false;
  leds[tLed] = tClr;
  
}

void TCPServer () {
    if (!client.connected()) {  
      Serial.print('.');
      client = server.available(); 
      delay(1000);
      return; 
    }

    if (client.available() > 0) {
      // Read incoming message
      data = client.readStringUntil('\r');
      Serial.println(data);
      client.flush();
      // Send back something to the clinet
      client.print(">>");
      dataAvailable = true;
    }
}

void setup() {
  //Init Hardware
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<STRIP_TYPE, LED_PIN, COLOR_MODE>(leds, NUM_LEDS);
  
  Serial.begin(115200);
  //Serial.begin(1843200);
  delay(100);

  //Wifi connect
  //WiFiManager wifiManager;
  //wifiManager.autoConnect("InfinityRoom");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  // Start the server
  server.begin();
  Serial.println("Server started"); 
  //client = server.available(); 
}

void loop() {
  TCPServer();
  if(dataAvailable)
    processData();
    
  if(tApply)
    applyLed();

  if(fillLed)
    fillLedData();
    
  if(isRepeat)
    executeLED();
}
    
