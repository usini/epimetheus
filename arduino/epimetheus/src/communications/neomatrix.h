#include <Adafruit_GFX.h>
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>
#include <communications/Fonts/TomThumb.h>

#define NEOMATRIX_PIN 27
#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 5
#define NUMMATRIX (MATRIX_WIDTH * MATRIX_HEIGHT)

CRGB matrixleds[NUMMATRIX];
FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_WIDTH, MATRIX_HEIGHT,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE );

String neomatrix_text = "";
int neomatrix_x    = MATRIX_HEIGHT;
int neomatrix_text_length = 0;
int neomatrix_speed = 100;

void neomatrix_print( String text) {
  neomatrix_text_length = -(text.length() * 3.5);
  neomatrix_text = text;
  neomatrix_x = matrix->width();
}

void loop_neomatrix( void * parameter ) {
  while (true) {
  matrix->fillScreen(0);
  matrix->setCursor(neomatrix_x, MATRIX_HEIGHT);
  matrix->print(neomatrix_text);
  Serial.println(String(neomatrix_x) + " / " + String(neomatrix_text_length));
  neomatrix_x = neomatrix_x - 1;
  if(neomatrix_x < neomatrix_text_length) {
    neomatrix_x = matrix->width();
  }
  matrix->show();
  delay(neomatrix_speed);
  }
}

void setup_neomatrix() {
  FastLED.addLeds<NEOPIXEL, NEOMATRIX_PIN>(matrixleds, NUMMATRIX);
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setFont(&TomThumb);
  matrix->setBrightness(25);
  matrix->setTextColor((0,0,255));
  matrix->setRotation(3);
  neomatrix_print("Another test to check if my magic number is cool");
  xTaskCreate(
    loop_neomatrix,
    "neomatrix",
    10000,
    NULL,
    1,
    NULL);
}

