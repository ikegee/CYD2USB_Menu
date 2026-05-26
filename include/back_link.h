#ifndef BACK_LINK_H
#define BACK_LINK_H

#include <TFT_eSPI.h>

class BackLink {
 private:
  TFT_eSPI* tft;
  int x;
  int y;
  int textWidth;
  int textHeight;
  static const uint8_t BACK_PADDING = 10; // Padding below back link

 public:
  BackLink(TFT_eSPI* display, int posX, int posY);
  void draw();
  bool checkTouch(int touchX, int touchY);
  
  int getX() const { return x; }
  int getY() const { return y; }
  int getWidth() const { return textWidth; }
  int getHeight() const { return textHeight + BACK_PADDING; }
};

// Helper function with adjusted vertical position
inline BackLink* createStandardBackLink(TFT_eSPI* tft) {
  return new BackLink(tft, 20, 65); // Increased Y position
}

inline BackLink* createBackLink(TFT_eSPI* tft, int posX, int posY) {
  return new BackLink(tft, posX, posY);
}

#endif
