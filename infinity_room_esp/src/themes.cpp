#include "main.h"

void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}

void applyBlack(){
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  delay(DELAY_APPLY_COLOR_ALL);
  FastLED.show();
}

void applyColor(unsigned long clr){
  fill_solid(leds, NUM_LEDS, clr);
  delay(DELAY_APPLY_COLOR_ALL);
  FastLED.show();
}

void HueEffect() {
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(hue[i]++, 255, 255);
  }

  FastLED.show();
  //delay(15);
  if(setDelay(15))
    return;
}

void RGBLoop(uint16_t SpeedDelay) {
  for (byte j = 0; j < 3; j++ ) {
    // Fade IN
    for (byte k = 0; k < 255; k++) {
      switch (j) {
        case 0: setAll(k, 0, 0); break;
        case 1: setAll(0, k, 0); break;
        case 2: setAll(0, 0, k); break;
      }
      FastLED.show();
      if(setDelay(SpeedDelay/10)) return;
    }
    // Fade OUT
    for (byte k = 255; k >= 0; k--) {
      switch (j) {
        case 0: setAll(k, 0, 0); break;
        case 1: setAll(0, k, 0); break;
        case 2: setAll(0, 0, k); break;
      }
      FastLED.show();
      if(setDelay(SpeedDelay/10)) return;
    }
  }
}

void FadeInOut(byte red, byte green, byte blue, uint16_t SpeedDelay) {
  float r, g, b;

  for (int k = 0; k < 256; k = k + 1) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    FastLED.show();
    if(setDelay(SpeedDelay/10)) return;
  }

  for (int k = 255; k >= 0; k = k - 2) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    FastLED.show();
    if(setDelay(SpeedDelay/10)) return;
  }
}

void fade_sha(){
    if(isApplyColor){
      applyColor(themeClr);
      isApplyColor = false;
    }
    if(counter >= 1000 * themeSpd){
      counter = 0;
      if(showBlack){
        //Fade in
        FastLED.setBrightness(themeBrtFade);
        themeBrtFade++;
        if(setDelay(2)) return;
        FastLED.show();
        if(themeBrtFade > 250)
          showBlack = false;
      } else {
        //Fade out
        FastLED.setBrightness(themeBrtFade);
        themeBrtFade--;
        if(setDelay(2)) return;
        FastLED.show();
        if(themeBrtFade < 1)
          showBlack = true;
      }
    }
    counter++;
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
  for (int j = 0; j < StrobeCount; j++) {
    setAll(red, green, blue);
    FastLED.show();
    if(setDelay(FlashDelay)) return;
    setAll(0, 0, 0);
    FastLED.show();
    if(setDelay(FlashDelay)) return;
  }

  if(setDelay(EndPause)) return;
}

void HalloweenEyes(byte red, byte green, byte blue,
                   int EyeWidth, int EyeSpace,
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause) {
  randomSeed(analogRead(0));

  int i;
  int StartPoint  = random( 0, NUM_LEDS - (2 * EyeWidth) - EyeSpace );
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;

  for (i = 0; i < EyeWidth; i++) {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
  }

  FastLED.show();

  if (Fade == true) {
    float r, g, b;

    for (int j = Steps; j >= 0; j--) {
      r = j * (red / Steps);
      g = j * (green / Steps);
      b = j * (blue / Steps);

      for (i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }

      FastLED.show();
      if(setDelay(FadeDelay)) return;
    }
  }

  setAll(0, 0, 0); // Set all black

  if(setDelay(EndPause)) return;
}

/*void CylonBounce(byte red, byte green, byte blue, int EyeSize,
    int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }

  if(setDelay(ReturnDelay)) return;

  for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }

  if(setDelay(ReturnDelay)) return;
}*/

void CylonBounce2(uint16_t clr, int EyeSize, int SpeedDelay) {
  static uint16_t randStrt[L_ROWS];
  static bool randStartDir[L_ROWS]; //True- Forward direction
  static bool randStrtInit = true;
  //Init start with random numbers
  if(randStrtInit) {
    for(byte i = 0; i < L_ROWS; i++) {
      randStrt[i] = random(0, L_COLS - EyeSize);
      randStartDir[i] = true;
    }
    randStrtInit = false;
  }

  //Erase old matrix
  clearLedsProc();

  for(byte i = 0; i < L_ROWS; i++) {
    //forward
    if(randStartDir[i]) {
      for(; randStrt[i] < L_COLS-EyeSize-2; randStrt[i]++) {
        populateMatrixCylon(randStrt[i], i, clr, EyeSize);
      }
      if(randStrt[i] >= L_COLS-EyeSize-2) {
        randStartDir[i] = false;
        randStrt[i] = L_COLS-EyeSize-2;
      }
    } else {
      //Backward
      for(; randStrt[i] > 0; randStrt[i]--) {
        populateMatrixCylon(randStrt[i], i, clr, EyeSize);
      }
      if(randStrt[i] <= 0){
        randStrt[i] = 0;
        randStartDir[i] = true;
      }
    }
  }

  //Show the effect and wait
  showLedsProc();
  if(setDelay(SpeedDelay)) return;
}

void populateMatrixCylon(int start, byte row, uint16_t color, int EyeSize){
    //Start pixel
    ledsProc[row][start] = color / 10;
    for(byte i = 1; i <= EyeSize; i++){
        ledsProc[row][start + i] = color;
    }
    //Last pixel
    ledsProc[row][start + EyeSize + 1] = color / 10;
}

void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = ((NUM_LEDS - EyeSize) / 2); i >= 0; i--) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(NUM_LEDS - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS - i - j, red, green, blue);
    }
    setPixel(NUM_LEDS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }
  if(setDelay(ReturnDelay)) return;
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i <= ((NUM_LEDS - EyeSize) / 2); i++) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(NUM_LEDS - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS - i - j, red, green, blue);
    }
    setPixel(NUM_LEDS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }
  if(setDelay(ReturnDelay)) return;
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }
  if(setDelay(ReturnDelay)) return;
}

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }
  if(setDelay(ReturnDelay)) return;
}

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  //setAll(0, 0, 0);

  for (int i = 0; i < Count; i++) {
    setPixel(random(NUM_LEDS), red, green, blue);
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
    if (OnlyOne) {
      setAll(0, 0, 0);
    }
  }

  //if(setDelay(SpeedDelay)) return;
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0, 0, 0);

  for (int i = 0; i < Count; i++) {
    setPixel(random(NUM_LEDS), random(0, 255), random(0, 255), random(0, 255));
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
    if (OnlyOne) {
      setAll(0, 0, 0);
    }
  }

  if(setDelay(SpeedDelay)) return;
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel;
  for(byte i = 0; i < 5; i++) {
    Pixel = random(NUM_LEDS);
    setPixel(Pixel, red, green, blue);
  }
  FastLED.show();
  if(setDelay(SpeedDelay)) return;
  //setPixel(Pixel, 0, 0, 0);
  applyBlack();
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red, green, blue);

  int Pixel = random(NUM_LEDS);
  setPixel(Pixel, 0xff, 0xff, 0xff);
  FastLED.show();
  if(setDelay(SparkleDelay)) return;
  setPixel(Pixel, red, green, blue);
  FastLED.show();
  if(setDelay(SpeedDelay)) return;
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position = 0;

  for (int i = 0; i < NUM_LEDS * 2; i++)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < NUM_LEDS; i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255)*red,
               ((sin(i + Position) * 127 + 128) / 255)*green,
               ((sin(i + Position) * 127 + 128) / 255)*blue);
    }

    FastLED.show();
    if(setDelay(WaveDelay)) return;
  }
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    setPixel(i, red, green, blue);
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < NUM_LEDS; i++) {
      c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, red, green, blue);  //turn every third pixel on
      }
      FastLED.show();

      if(setDelay(SpeedDelay)) return;

      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}

void theaterChaseRainbow(int SpeedDelay) {
  byte *c;

  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        c = Wheel( (i + j) % 255);
        setPixel(i + q, *c, *(c + 1), *(c + 2)); //turn every third pixel on
      }
      FastLED.show();

      if(setDelay(SpeedDelay)) return;

      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  FastLED.show();
  if(setDelay(SpeedDelay)) return;
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if ( t192 > 0x80) {                    // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {            // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}


void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    FastLED.show();
    if(setDelay(SpeedDelay)) return;
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue ); 
}

void clearLedsProc(){
  for(int i = 0; i < L_ROWS; i++) {
    for(int j = 0; j < L_COLS; j++){
      ledsProc[i][j] = -1;
    }
  }
}

void showLedsProc(){
  //Clear all leds
  applyBlack();

  for(int i = 0; i < L_ROWS; i++){
    for(int j = 0; j < L_COLS; j++){
      int ledNo = i * j + j;
      if(ledNo == N_L_1)
        continue;

      leds[ledNo] = ledsProc[i][j];
    }
  }
  FastLED.show();
}