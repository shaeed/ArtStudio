#include <Arduino.h>

void setPixel(int Pixel, byte red, byte green, byte blue);
void setAll(byte red, byte green, byte blue);
void HueEffect();
void RGBLoop(uint16_t SpeedDelay);
void FadeInOut(byte red, byte green, byte blue, uint16_t SpeedDelay);
void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause);
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void CylonBounce2(uint16_t clr, int EyeSize, int SpeedDelay);
void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne);
void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne);
void Sparkle(byte red, byte green, byte blue, int SpeedDelay);
void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay);
void RunningLights(byte red, byte green, byte blue, int WaveDelay);
void colorWipe(byte red, byte green, byte blue, int SpeedDelay);
void rainbowCycle(int SpeedDelay);
void theaterChase(byte red, byte green, byte blue, int SpeedDelay);
void theaterChaseRainbow(int SpeedDelay);
void Fire(int Cooling, int Sparking, int SpeedDelay);
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay); 
void fadeToBlack(int ledNo, byte fadeValue);

void applyBlack();
void applyColor(unsigned long clr);
void fade_sha();
void showLedsProc();
void clearLedsProc();
void populateMatrixCylon(int start, byte row, uint16_t color, int EyeSize);
void setPixelHeatColor (int Pixel, byte temperature);
byte * Wheel(byte WheelPos);
