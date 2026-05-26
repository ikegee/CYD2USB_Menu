#ifndef SUB_HEADER_H
#define SUB_HEADER_H

#include <TFT_eSPI.h>

class SubHeader {
private:
  TFT_eSPI* tft;
  static const uint8_t HEADER_GAP = 10;      // Gap between header and sub-header
  static const uint8_t START_Y = 20;        // Where header ends
  static const uint8_t SUB_HEIGHT = 25;     // Height of sub-header
  
public:
  SubHeader(TFT_eSPI* display);
  void draw(const String& title);
  void drawWithAlignment(const String& title, bool centerHorizontal, bool centerVertical);
};

#endif // SUB_HEADER_H

