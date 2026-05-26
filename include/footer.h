#ifndef FOOTER_H
#define FOOTER_H

#include <TFT_eSPI.h>
#include "screen_states.h"

class Footer {
private:
  TFT_eSPI* tft;
  int footerY;
  bool showEndIndicator;

public:
  Footer(TFT_eSPI* _tft, int _footerY = 310) : tft(_tft), footerY(_footerY), showEndIndicator(false) {}

  void draw() {
    // Draw footer background
    tft->fillRect(0, footerY, 240, 10, TFT_DARKGREY);    
    // Draw basic footer content
    tft->setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft->setTextSize(1);
    tft->setTextDatum(TC_DATUM); // Center text
    tft->drawString(TITLE_PROJECT_NAME, 120, footerY + 2);
    tft->setTextDatum(TL_DATUM); // Reset to default
  }
  
  // Show/hide the "END OF CONTENT" indicator
  void showEnd(bool show) {
    showEndIndicator = show;
    if (showEndIndicator) {
      // Clear the area where the end indicator will be shown
      tft->fillRect(0, footerY - 10, 240, 20, TFT_NAVY);      
      // Draw end indicator above where the footer would be (adjusted Y position)
      tft->setTextColor(TFT_YELLOW, TFT_NAVY);
      tft->setTextSize(1);
      tft->setTextDatum(TC_DATUM); // Center text
      tft->drawString("= = = END OF CONTENT = = =", 120, footerY - 5);
      tft->setTextDatum(TL_DATUM); // Reset to default
    }
  }
};

#endif // FOOTER_H
