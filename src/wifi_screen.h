#ifndef WIFI_SCREEN_H
#define WIFI_SCREEN_H

#include "back_link.h"
#include "coming_soon.h"
#include "screen_manager.h"
#include "screen_states.h"
#include "sub_header.h"
#include "text_link.h"

enum WiFiScreenState { WIFI_MAIN, WIFI_SETTINGS, WIFI_SCANNER, WIFI_CONNECT };

class WiFiScreen : public Screen {
 private:
  SubHeader subHeader;
  BackLink* backLink;
  LinkGroup* wifiLinks;
  WiFiScreenState wifiState;
  ComingSoon comingSoon;  // Add ComingSoon instance

 public:
  WiFiScreen(TFT_eSPI* tft, Header* header)
      : Screen(tft, header),
        subHeader(tft),
        backLink(nullptr),
        wifiLinks(nullptr),
        wifiState(WIFI_MAIN),
        comingSoon(tft) {}

  ~WiFiScreen() { cleanup(); }

  void draw() override {
    // Clear screen
    tft->fillScreen(TFT_NAVY);
    header->draw();

    // Create back link if it doesn't exist
    if (backLink == nullptr) {
      backLink = new BackLink(tft, 20, 60);
    }
    backLink->draw();

    switch (wifiState) {
      case WIFI_MAIN:
        // Draw main WiFi screen
        subHeader.draw(ITEM_WIFI);

        // Create WiFi links if they don't exist
        if (wifiLinks == nullptr) {
          wifiLinks = new LinkGroup(tft, 20, 100, 4);
          wifiLinks->addLink("WiFi Settings", SCREEN_WIFI_SETTINGS);
          wifiLinks->addLink("WiFi Scanner", SCREEN_WIFI_SCANNER);
          wifiLinks->addLink("Connect to WiFi", SCREEN_WIFI_CONNECT);
        }
        wifiLinks->draw();
        break;

      case WIFI_SETTINGS:
        subHeader.draw(SUB_TITLE_WIFI_SETTINGS);
        comingSoon.draw();  
        break;

      case WIFI_SCANNER:
        subHeader.draw(SUB_TITLE_WIFI_SCANNER);
        comingSoon.draw(); 
        break;

      case WIFI_CONNECT:
        subHeader.draw(SUB_TITLE_WIFI_CONNECT);
        comingSoon.draw();  
        break;

      default:
        // Handle unexpected state (optional, for robustness)
        Serial.println("WiFiScreen::draw: Unexpected wifiState=" + String(wifiState));
        break;
    }

    // Update screen state
    currentScreen = WIFI_SCREEN_STATE;
  }

  bool handleTouch(uint16_t touchX, uint16_t touchY) override {
    // Check if back button was touched
    if (backLink != nullptr && backLink->checkTouch(touchX, touchY)) {
      Serial.println("Back link touched");

      if (wifiState != WIFI_MAIN) {
        // If in any sub-screen, go back to main WiFi screen
        wifiState = WIFI_MAIN;
        draw();
        return false;  // Don't go back to main menu yet
      } else {
        // If in main WiFi screen, return to main menu
        return true;
      }
    }

    // Handle link touches in main WiFi screen
    if (wifiState == WIFI_MAIN && wifiLinks != nullptr) {
      if (wifiLinks->handleTouch(touchX, touchY)) {
        return false;  // We handled the touch
      }
    }

    return false;
  }

  void processSelection() override {
    if (wifiState == WIFI_MAIN && wifiLinks != nullptr && wifiLinks->hasSelection()) {
      ScreenDestination destination = wifiLinks->getSelectedDestination();

      if (destination == SCREEN_WIFI_SETTINGS) {
        Serial.println("Transitioning to WiFi Settings screen");
        wifiState = WIFI_SETTINGS;
        wifiLinks->clearSelection();
        draw();  // Redraw with new state
      } else if (destination == SCREEN_WIFI_SCANNER) {
        Serial.println("Transitioning to WiFi Scanner screen");
        wifiState = WIFI_SCANNER;
        wifiLinks->clearSelection();
        draw();  // Redraw with new state
      } else if (destination == SCREEN_WIFI_CONNECT) {
        Serial.println("Transitioning to Connect to WiFi screen");
        wifiState = WIFI_CONNECT;
        wifiLinks->clearSelection();
        draw();  // Redraw with new state
      }
    }
  }

  void cleanup() override {
    if (backLink != nullptr) {
      delete backLink;
      backLink = nullptr;
    }

    if (wifiLinks != nullptr) {
      delete wifiLinks;
      wifiLinks = nullptr;
    }
  }
};

#endif  // WIFI_SCREEN_H
