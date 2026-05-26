#ifndef UTILS_H
#define UTILS_H

#include "header.h"
#include "sub_header.h"

// Function declarations only (implementations in utils.cpp)
bool isValidTouch(uint16_t x, uint16_t y);
void mapTouchToScreen(uint16_t *x, uint16_t *y);
void drawBaseLayout(TFT_eSPI* tft, Header* header, SubHeader* subHeader, const String& title);
void showRebootMessage(TFT_eSPI* tft);

#endif // UTILS_H
