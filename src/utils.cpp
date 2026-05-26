#include "utils.h"
#include "header.h"
#include "sub_header.h"

bool isValidTouch(uint16_t x, uint16_t y) {
  // Filter out extreme values that indicate false touches
  if (x == 0 || y == 0 || x == 4095 || y == 4095 || x == -4096 || y == -4096 || y == 8191 ||
      x == 8191) {
    return false;
  }
  // Check if within valid range
  if (x < TS_MINX || x > TS_MAXX || y < TS_MINY || y > TS_MAXY) {
    return false;
  }
  return true;
}

void mapTouchToScreen(uint16_t *x, uint16_t *y) {
  // Use the calibration values from TFT_eSPI's User_Setup.h
  // Map raw touch coordinates to screen coordinates
  *x = map(*x, TS_MINX, TS_MAXX, 0, TFT_WIDTH);
  *y = map(*y, TS_MINY, TS_MAXY, 0, TFT_HEIGHT);
  
  // Add debug output to see the mapped coordinates
  Serial.println("Mapped touch: x=" + String(*x) + ", y=" + String(*y));
}

void drawBaseLayout(TFT_eSPI* tft, Header* header, SubHeader* subHeader, const String& title) {
  tft->fillScreen(TFT_NAVY);
  header->draw();
  
  // Check if subHeader is not null before using it
  if (subHeader != nullptr) {
    subHeader->draw(title);
  } else {
    // Create a temporary SubHeader if none was provided
    SubHeader tempSubHeader(tft);
    tempSubHeader.draw(title);
  }
  // Clear the content area
  tft->fillRect(0, 50, 240, 270, TFT_NAVY);
}

void showRebootMessage(TFT_eSPI* tft) {
  // Calculate position for the message
  int messageY = 200;      
  int messageHeight = 30;    
  
  // Clear just the message area with red background (full width)
  tft->fillRect(0, messageY, 240, messageHeight, TFT_RED);  
  
  // Set text properties to match menu style
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);  
  String rebootText = "REBOOTING...";
  
  // Calculate text position for center alignment
  int textWidth = rebootText.length() * 12;  
  int xPos = (240 - textWidth) / 2;
  int yPos = messageY + (messageHeight - 16) / 2;  
  
  // Flash the text 3 times
  for (int i = 0; i < 3; i++) {
    // Draw text
    tft->setCursor(xPos, yPos);
    tft->println(rebootText);
    delay(300);
    // Clear text area (keep red background)
    tft->fillRect(xPos, yPos, textWidth, 16, TFT_RED);
    delay(200);
  }
  
  // Show text one final time before reboot
  tft->setCursor(xPos, yPos);
  tft->println(rebootText);
  delay(500);

  ESP.restart();
}
