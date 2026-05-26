#ifndef HEADER_H
#define HEADER_H

#include <TFT_eSPI.h>

class Header {
private:
  TFT_eSPI* tft;
  
public:
  Header(TFT_eSPI* display);
  void draw();
};

#endif // HEADER_H
