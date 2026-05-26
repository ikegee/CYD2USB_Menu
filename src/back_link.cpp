#include "back_link.h"

BackLink::BackLink(TFT_eSPI* display, int posX, int posY)
  : tft(display), x(posX), y(posY), textWidth(60), textHeight(20) {}

void BackLink::draw() {
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->setCursor(x, y);
  tft->println("back");
}

bool BackLink::checkTouch(int touchX, int touchY) {
  if (touchX >= x && touchX <= (x + textWidth) && 
      touchY >= y && touchY <= (y + textHeight)) {
    return true;
  }
  return false;
}
