#include "vars.h"
#include "main.h"

void setup(){
  //Init Hardware
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<STRIP_TYPE, LED_PIN, COLOR_MODE>(leds, NUM_LEDS);

  pinMode(H_LED_1, OUTPUT);
  pinMode(H_LED_2, OUTPUT);
  pinMode(H_LED_3, OUTPUT);
  pinMode(H_LED_4, OUTPUT);
  digitalWrite(H_LED_1, HIGH);
  digitalWrite(H_LED_2, HIGH);
  digitalWrite(H_LED_3, HIGH);
  digitalWrite(H_LED_4, HIGH);

  Serial.begin(115200);
  
  //Wifi connect
  //WiFiManager wifiManager;
  //wifiManager.autoConnect("InfinityRoom");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  //Reset automatically
   int isReset;
  EEPROM.begin(1);
  int eeAddress = 1;
  isReset = EEPROM.read(eeAddress);
  delay(10);
  if(isReset == 1){
    EEPROM.write(eeAddress, 0);
    Serial.println("Restarting");
    delay(5);
    EEPROM.commit();
    delay(5);
    ESP.restart();
  } else {
    EEPROM.write(eeAddress, 1);
    delay(10);
    Serial.println("Not Restarting");
    EEPROM.commit();
  } 

  // Start the server
  server.begin();
  Serial.println("Server started");

  //Page handrels
  server.on ( "/", handleRoot );
  server.on ("/ir", handleThemes); //Infinity room themes
  server.on ("/irl", handleLeds); //Infinity room Hanginging LEDs 

  for (int i = 0; i < NUM_LEDS; i++)
    hue[i] = 255 / NUM_LEDS * i;
  FastLED.show();

  //Default theme
}

void loop(){
  server.handleClient();
  
  if(dataAvailable)
    processData();
    
  if(tApply > 10)
    applyLed();

  if(fillLed)
    fillLedData();
    
  if(isRepeat)
    executeLED();
}
