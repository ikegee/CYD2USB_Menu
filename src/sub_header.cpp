#include "sub_header.h"

SubHeader::SubHeader(TFT_eSPI* display) : tft(display) {}

void SubHeader::draw(const String& title) {
  const int16_t yPosition = START_Y + HEADER_GAP;
  
  tft->fillRect(0, yPosition, 240, SUB_HEIGHT, TFT_NAVY);
  tft->setTextColor(TFT_GREEN);
  tft->setTextSize(2);
  
  int16_t textWidth = title.length() * 12;
  int16_t xPos = (240 - textWidth) / 2;
  int16_t yPos = yPosition + (SUB_HEIGHT - 16) / 2;
  
  tft->setCursor(xPos, yPos);
  tft->println(title);
}

void SubHeader::drawWithAlignment(const String& title, bool centerHorizontal, bool centerVertical) {
  const int16_t yPosition = START_Y + HEADER_GAP;
  
  tft->fillRect(0, yPosition, 240, SUB_HEIGHT, TFT_NAVY);
  tft->setTextColor(TFT_GREEN);
  tft->setTextSize(2);
  
  int16_t xPos = 5;
  int16_t yPos = yPosition + 2;
  
  if (centerHorizontal) {
    int16_t textWidth = title.length() * 12;
    xPos = (240 - textWidth) / 2;
  }
  
  if (centerVertical) {
    yPos = yPosition + (SUB_HEIGHT - 16) / 2;
  }
  
  tft->setCursor(xPos, yPos);
  tft->println(title);
}
