#include <SPI.h>
#include <TFT_eSPI.h>

#define AA_FONT_LARGE "NotoSansBold36"

TFT_eSPI tft = TFT_eSPI();
int max_bar = 0;
int bar_size = 0;
void setup_st7789(int bars) {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  max_bar = bars;
  bar_size = 240 / max_bar;
}

void drawBar(int x, int color, int h) {
  tft.fillRect(x * bar_size, 0, bar_size, h, color);
}

void drawValue(int x, String value, String unit) {
  tft.drawString(value, x * bar_size, 120, 2);
  tft.drawString(unit, x * bar_size, 136, 2);
}
