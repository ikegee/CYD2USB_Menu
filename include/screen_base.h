#ifndef SCREEN_BASE_H
#define SCREEN_BASE_H

#include <TFT_eSPI.h>
#include "header.h"
#include "sub_header.h"
#include "back_link.h"

class ScreenBase {
protected:
  TFT_eSPI* tft;
  Header* header;
  SubHeader* subHeader;
  BackLink* backLink;
  String screenTitle;
  
  // Layout constants
  static const uint8_t CONTENT_START_Y = 85; // Adjusted start position for content
  static const uint8_t CONTENT_PADDING = 10; // Padding for content areas
  
public:
  ScreenBase(TFT_eSPI* tft, Header* header, String title);
  virtual ~ScreenBase();
  
  virtual void draw();
  virtual bool handleTouch(uint16_t touchX, uint16_t touchY);
  virtual void cleanup();
  virtual void processSelection() {}
  
  int getContentStartY() const { return CONTENT_START_Y; }
  int getContentPadding() const { return CONTENT_PADDING; }
};

#endif
