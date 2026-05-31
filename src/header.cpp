#include "header.h"
#include "screen_states.h"

Header::Header(TFT_eSPI* display) : tft(display) {}

void Header::draw() {

  // TODO: add SD card status indicator
  tft->fillRect(0, 0, 240, 20, TFT_BLUE);
  tft->setTextColor(TFT_GREEN);
  tft->setTextSize(1);
  tft->setCursor(5, 6);
  tft->println(TITLE_PROJECT_NAME);
  
  // TODO: Replace with actual battery level indicator
  tft->drawRect(205, 4, 20, 12, TFT_WHITE);
  tft->drawRect(225, 6, 2, 8, TFT_WHITE);
  tft->fillRect(207, 6, 16, 8, TFT_GREEN);
}
