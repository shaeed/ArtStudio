#include "main.h"

void setup(){
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<STRIP_TYPE, LED_PIN, COLOR_MODE>(leds, NUM_LEDS);


  /*******************************Wifi Setup**********************************/
  // Set WIFI hostname (otherwise it would be ESP-XXXXXX)
  //jw.setHostname("justwifi");

  // Callbacks
  jw.subscribe(infoCallback);
  jw.subscribe(mdnsCallback);
  jw.subscribe(captivePortalCallback);

  // AP mode only as fallback
  jw.enableAP(false);
  jw.enableAPFallback(true);

  // Enable STA mode (connecting to a router)
  jw.enableSTA(true);

  // Configure it to scan available networks and connect in order of dBm
  jw.enableScan(true);

  // Clean existing network configuration
  jw.cleanNetworks();

  // Add a network with password
  jw.addNetwork(SSID1, PASS1);
  jw.addNetwork(SSID2, PASS2);

  Serial.println("[WIFI] Connecting Wifi...");
  
/******************************Create server*********************************/
  //Page handrels
  server.on ( "/", handleRoot );
  //server.on ("/ir", handleApply); //Infinity room
  server.on ("/irl", handleLeds);
  //Start the server
  server.begin();
  Serial.println("Server started"); 
}

void loop(){
  //-------Wifi--------
  jw.loop();

  delay(1000);
  setDelay(10);
}


void mdnsCallback(justwifi_messages_t code, char * parameter) {
  if (code == MESSAGE_CONNECTED) {
  String hostname = WiFi.hostname();
    // Configure mDNS
    if (MDNS.begin((char *) hostname.c_str())) {
      Serial.printf("[MDNS] OK\n");
      // Publish as if there is an TELNET service available
      MDNS.addService("telnet", "tcp", 22);
    } else {
      Serial.printf("[MDNS] FAIL\n");
    }
   }
}


// -----------------------------------------------------------------------------
// Captive portal
// -----------------------------------------------------------------------------
//#include <DNSServer.h>

//DNSServer dnsServer;

void captivePortalCallback(justwifi_messages_t code, char * parameter) {

    if (code == MESSAGE_ACCESSPOINT_CREATED) {
        if (!WiFi.isConnected()) dnsServer.start(53, "*", WiFi.softAPIP());
    }

    if (code == MESSAGE_CONNECTED) {
        dnsServer.stop();
    }

}