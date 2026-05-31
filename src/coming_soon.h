#ifndef COMING_SOON_H
#define COMING_SOON_H

#include <TFT_eSPI.h>

class ComingSoon {
 private:
  TFT_eSPI* tft;

 public:
  ComingSoon(TFT_eSPI* display) : tft(display) {}

  void draw(int16_t x = 20, int16_t y = 100) {
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->setCursor(x, y);
    tft->println("Coming soon...");
  }
};

#endif  // COMING_SOON_H