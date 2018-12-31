#include "main.h"

#define THEME_OFF         1 
#define THEME_ON          2 
#define THEME_RAINBOW     3 
#define THEME_STROBE      4 
#define THEME_ALLWHITE    5 
#define THEME_COLORFUL    6 
#define THEME_FADE        7 
#define THEME_NIGHTSKY    10
#define Theme_RGBLoop                 11
#define Theme_FadeInFadeOut           12
#define Theme_Strobe2                 13
#define Theme_CylonBounce             14
#define Theme_NewKITT                 15
#define THEME_NIGHTSKY2               16
#define Theme_Sparkle                 17
#define Theme_SnowSparkle             18
#define Theme_RunningLights           19
#define Theme_colorWipe               20
#define Theme_theaterChaseRainbow     21
#define Theme_Fire                    22
#define Theme_meteorRain              23
#define Theme_HueEffect               24

#define THEME_CUSTOM      100

//If returns True, break the current task
boolean setDelay(uint16_t d){
  unsigned long mili = d * 1000;
  for(unsigned long i = 0; i < mili; i += DELAY_MICRO){
    server.handleClient();
    if(dataAvailable){
      //Some data received from user
      //Break the timing
      //processData();
      if(dataAvailable)
        return true;
    } else {
      delayMicroseconds(DELAY_MICRO);
    }
  }
  return false;
}

void displayPage(String page){
  //Send the page to client
  server.send ( 200, "text/html", page );
}

void handleRoot() {
  displayPage(DEV_NAME);
}

void handleLeds(){
  byte led = 100;
  byte state = 100;
  if (server.arg("led")!= ""){
    led = server.arg("led").toInt();
  }
  if (server.arg("state")!= ""){
    state = server.arg("state").toInt();
  }

  displayPage("Handle LEDs");

  //if(led > 0 && led < H_LED_COUNT){
    if(state == 0) //Off
      digitalWrite(led, HIGH);
    else if(state == 1) //On
      digitalWrite(led, LOW);
  //}
}

void handleThemes() {
  dataAvailable = true;
  
  if (server.arg("apply")!= "" && server.arg("apply") == "True"){
    tApply = 1;
  }
  if (server.arg("brt")!= ""){
    tBrt = server.arg("brt").toInt();
    tApplyBrt = true;
  }
  if (server.arg("clr")!= ""){
    tClr = server.arg("clr").toInt();
    tApplyClr = true;
  }
  if (server.arg("led")!= ""){
    tLed = server.arg("led").toInt();
    fillLed = true;
  }
  if (server.arg("spd")!= ""){
    tSpd = server.arg("spd").toInt();
  }
  if (server.arg("thm")!= ""){
    tThm = server.arg("thm").toInt();
  }

  Serial.println(String(tThm) + " " + String(tBrt));
  displayPage("Hndle Themes");
}

void applyLed(){
  tApply = 0;
  themeBrt = tBrt;
  themeSpd = tSpd;
  themeClr = tClr;
  theme = tThm;
  isRepeat = true;
  isApplyColor = tApplyClr;
  isApplyBrt = tApplyBrt;
  
  counter = 0;
  hueInt = 0;
  themeBrtFade = themeBrt;

  //Convert to RGB
  b = tClr & 255;
  g = (tClr >> 8) & 255;
  r = (tClr >> 16) & 255;

  //Switch off all the 2812b leds
  applyBlack();
}

void processData(){
  tApply = 11;
  if(tApplyBrt){
    FastLED.setBrightness(themeBrt);
  }
  dataAvailable = false;
}

void fillLedData(){
  fillLed = false;
  leds[tLed] = tClr;
}

void executeLED(){
  if(isApplyBrt){
    isApplyBrt = false;
    FastLED.setBrightness(themeBrt);
  }

  switch(theme){
    case THEME_OFF:
      applyBlack();
      isRepeat = false;
    break;
        
    case THEME_RAINBOW:
      fill_rainbow(leds, NUM_LEDS, hueInt, 5);
      FastLED.show();
      hueInt = hueInt + themeSpd;
    break;
        
    case THEME_STROBE:
        if(counter >= 1000 * themeSpd){
          counter = 0;
          if(showBlack){
            applyBlack();
            showBlack = false;
          } else {
            fill_solid(leds, NUM_LEDS, themeClr);
            delay(DELAY_APPLY_COLOR_ALL);
            FastLED.show();
            showBlack = true;
          }
        }
        counter++;
        break;
        
    case THEME_ALLWHITE:
        applyColor(CRGB::White);
        isRepeat = false;
        break;
        
    case THEME_COLORFUL:
        applyColor(themeClr);
        isRepeat = false;
        break;
        
    case THEME_FADE:
      fade_sha();
    break;

    case Theme_RGBLoop:
      RGBLoop(themeSpd);
    break;

    case Theme_FadeInFadeOut:
      FadeInOut(r, g, b, themeSpd);
    break;
    
    case Theme_Strobe2:
       Strobe(r, g, b, 10, themeSpd, themeSpd + 1000);
    break;
    
    case Theme_CylonBounce:
      //CylonBounce(r, g, b, 4, themeSpd, 2);
      CylonBounce2(themeClr, 5, themeSpd);
    break;
    
    case Theme_NewKITT:
      NewKITT(r, g, b, 20, themeSpd, 2);
    break;
    
    case THEME_NIGHTSKY:
      Twinkle(0xff, 0xff, 0xff, 100, themeSpd, false);
      Twinkle(0, 0, 0, NUM_LEDS, 1, false);
    break;
    
    case THEME_NIGHTSKY2:
      TwinkleRandom(200, themeSpd, false);
    break;
    
    case Theme_Sparkle:
      Sparkle(r, g, b, themeSpd);
    break;
    
    case Theme_SnowSparkle:
      SnowSparkle(r, g, b, themeSpd, random(100, 1000));
    break;
    
    case Theme_RunningLights:
      RunningLights(r, g, b, themeSpd);
    break;
    
    case Theme_colorWipe:
      colorWipe(r, g, b, themeSpd);
    break;
    
    case Theme_theaterChaseRainbow:
      theaterChaseRainbow(themeSpd);
    break;
    
    case Theme_Fire:
      Fire(35, 180, themeSpd);
    break;
    
    case Theme_meteorRain:
      meteorRain(r, g, b, 10, 8, true, themeSpd);
    break;
    
    case Theme_HueEffect:
      HueEffect();
    break;
        
    case THEME_CUSTOM:
      FastLED.show();
    break;
  }
}