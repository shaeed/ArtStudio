#include <Arduino.h>
#include <ESP8266WebServer.h>

extern ESP8266WebServer server;
extern boolean dataAvailable;

#define DELAY_MICRO 10

int xsha;
//If returns True, then break the current task
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
  //displayPage(DEV_NAME);
  displayPage("Shaeed - Hellow world from esp8266");
}

void handleLeds(){

  displayPage("Handle LEDs");
}