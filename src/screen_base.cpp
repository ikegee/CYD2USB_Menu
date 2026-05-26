#include "screen_base.h"
#include "back_link.h"

ScreenBase::ScreenBase(TFT_eSPI* tft, Header* header, String title) 
  : tft(tft), header(header), backLink(nullptr), screenTitle(title) {
  subHeader = new SubHeader(tft);
}

ScreenBase::~ScreenBase() {
  cleanup();
}

void ScreenBase::draw() {
  // Clear screen
  tft->fillScreen(TFT_NAVY);
  header->draw();
  tft->fillRect(0, 20, 240, 320 - 20, TFT_NAVY);
  subHeader->draw(screenTitle);
  
  // Create back link if needed
  if (backLink == nullptr) {
    backLink = createStandardBackLink(tft); 
    //backLink = new BackLink(tft, 20, 60);
  }
  backLink->draw();
}

bool ScreenBase::handleTouch(uint16_t touchX, uint16_t touchY) {
  if (backLink != nullptr && backLink->checkTouch(touchX, touchY)) {
    return true; // Back action triggered
  }
  return false; // No action
}

void ScreenBase::cleanup() {
  if (backLink != nullptr) {
    delete backLink;
    backLink = nullptr;
  }
  
  if (subHeader != nullptr) {
    delete subHeader;
    subHeader = nullptr;
  }
}
