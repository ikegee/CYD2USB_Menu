#ifndef TEXT_LINK_H
#define TEXT_LINK_H

#include <TFT_eSPI.h>
#include <functional>
#include <vector>

// Instead of using ScreenState enum directly, use an integer to represent destinations
typedef int ScreenDestination;

class TextLink {
 private:
  TFT_eSPI* tft;
  int x;
  int y;
  int textWidth;
  int textHeight;
  String label;
  ScreenDestination destination;
  std::function<void()> action;
  uint16_t textColor;
  uint16_t bgColor;
  uint16_t activeBgColor;
  uint8_t textSize;
  bool isActive;

 public:
  TextLink(TFT_eSPI* display, String linkText, int posX, int posY, 
           ScreenDestination dest, std::function<void()> callback = nullptr)
      : tft(display),
        x(posX),
        y(posY),
        label(linkText),
        destination(dest),
        action(callback),
        textColor(TFT_WHITE),
        bgColor(TFT_NAVY),
        activeBgColor(TFT_DARKGREEN),
        textSize(2),
        isActive(false)
  {
    // Calculate dimensions based on text length    
    textWidth = tft->width();
    textHeight = 20;
  }

  // In the TextLink class
  void draw() {
    // Draw background - extend from left edge (x=0) to right edge of screen
    uint16_t bgColor = isActive ? activeBgColor : this->bgColor;
    
    // Instead of using x as the starting point, use 0 to start from left edge
    // Keep the same y position and height
    // For width, use the full screen width (tft->width())
    tft->fillRect(0, y, tft->width(), textHeight, bgColor);
    
    // Draw the text at the original x position
    tft->setTextColor(textColor);
    tft->setTextSize(textSize);
    tft->setCursor(x, y);
    tft->println(label);
    
    Serial.println("Drawing link '" + label + "', active: " + String(isActive ? "true" : "false"));
  }

  // Set active state (for highlighting)
  void setActive(bool active) {
    isActive = active;
  }

  // Check if the link was touched
  bool checkTouch(int touchX, int touchY) {
    if (touchX >= x && touchX <= (x + textWidth) && 
        touchY >= y && touchY <= (y + textHeight)) {
      Serial.println("Link '" + label + "' touched!");
      return true;
    }
    return false;
  }

  // Execute the action
  void execute() {
    if (action) {
      action();
    }
  }

  // Get destination screen
  ScreenDestination getDestination() const {
    return destination;
  }

  // Get the position and dimensions
  int getX() const { return x; }
  int getY() const { return y; }
  int getWidth() const { return textWidth; }
  int getHeight() const { return textHeight; }
  String getLabel() const { return label; }
  
  // Customize appearance
  void setColors(uint16_t text, uint16_t bg, uint16_t activeBg) {
    textColor = text;
    bgColor = bg;
    activeBgColor = activeBg;
  }
  
  void setTextSize(uint8_t size) {
    textSize = size;
    textWidth = label.length() * (6 * size); // Recalculate width
    textHeight = 10 * size;                  // Recalculate height
  }
};

// Class to manage a group of text links
class LinkGroup {
private:
  TFT_eSPI* tft;
  std::vector<TextLink> links;  // Fixed: Properly declared as a member variable
  int startX;
  int startY;
  int linkSpacing;
  int selectedLink;
  bool vertical;

public:
  LinkGroup(TFT_eSPI* display, int x, int y, int spacing = 0, bool isVertical = true)
    : tft(display), 
      startX(x), 
      startY(y), 
      linkSpacing(spacing), 
      selectedLink(-1),
      vertical(isVertical) {}

  // Add a link to the group
  void addLink(String label, ScreenDestination destination, std::function<void()> action = nullptr) {
    int posX = startX;
    int posY = startY;
    
    if (!links.empty()) {
      if (vertical) {
        // Calculate Y position based on previous links
        posY = links.back().getY() + links.back().getHeight() + linkSpacing;
      } else {
        // Calculate X position based on previous links
        posX = links.back().getX() + links.back().getWidth() + linkSpacing;
      }
    }
    
    links.emplace_back(tft, label, posX, posY, destination, action);
  }

  // Draw all links
  void draw() {
    for (auto& link : links) {
      link.draw();
    }
  }

  // Handle touch event for all links
  bool handleTouch(int touchX, int touchY) {
    for (size_t i = 0; i < links.size(); i++) {
        if (links[i].checkTouch(touchX, touchY)) {
            Serial.println("Link " + String(i) + " selected: " + links[i].getLabel());
            // Highlight the link
            if (selectedLink >= 0 && selectedLink < static_cast<int>(links.size())) {
                links[selectedLink].setActive(false);
            }
            selectedLink = i;
            links[i].setActive(true);
            draw(); // Redraw to show the highlight
            
            return true;
        }
    }
    return false;
  }


  // Process the selected link
  bool processSelection() {
    if (selectedLink >= 0 && selectedLink < static_cast<int>(links.size())) {
      links[selectedLink].execute();
      return true;
    }
    return false;
  }

  // Get the destination of the selected link
  ScreenDestination getSelectedDestination() const {
    if (hasSelection()) {
        ScreenDestination dest = links[selectedLink].getDestination();
        Serial.println("LinkGroup::getSelectedDestination returning: " + String(dest));
        return dest;
    }
    Serial.println("LinkGroup::getSelectedDestination: No selection, returning 0");
    return 0;
}

  // Clear selection
  void clearSelection() {
    if (selectedLink >= 0 && selectedLink < static_cast<int>(links.size())) {
      links[selectedLink].setActive(false);
      selectedLink = -1;
    }
  }

  // Check if there's a selection
  bool hasSelection() const {
    bool result = (selectedLink >= 0 && selectedLink < static_cast<int>(links.size()));
    Serial.println("LinkGroup::hasSelection returning: " + String(result ? "true" : "false") + 
                   " (selectedLink=" + String(selectedLink) + ")");
    return result;
  } 
};

#endif // TEXT_LINK_H
