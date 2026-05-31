#ifndef BLUETOOTH_SCREEN_H
#define BLUETOOTH_SCREEN_H

#include "back_link.h"
#include "screen_manager.h"
#include "screen_states.h"
#include "sub_header.h"
#include "text_link.h"
#include "coming_soon.h"

enum BluetoothScreenState {  BLUETOOTH_MAIN, BLUETOOTH_SETTINGS, BLUETOOTH_SCANNER, BLUETOOTH_CONNECT};

class BluetoothScreen : public Screen {
 private:
  SubHeader subHeader;
  BackLink* backLink;
  LinkGroup* bluetoothLinks;
  BluetoothScreenState btState;
  ComingSoon comingSoon;  // Add ComingSoon instance

 public:
  BluetoothScreen(TFT_eSPI* tft, Header* header)
      : Screen(tft, header),
        subHeader(tft),
        backLink(nullptr),
        bluetoothLinks(nullptr),
        btState(BLUETOOTH_MAIN),
        comingSoon(tft) {}

  ~BluetoothScreen() { cleanup(); }

  void draw() override {
    // Clear screen
    tft->fillScreen(TFT_NAVY);
    header->draw();

    // Create back link if it doesn't exist
    if (backLink == nullptr) {
      backLink = new BackLink(tft, 20, 60);
    }
    backLink->draw();

    switch (btState) {
      case BLUETOOTH_MAIN:
        // Draw main Bluetooth screen
        subHeader.draw(ITEM_BLUETOOTH);

        // Create Bluetooth links if they don't exist
        if (bluetoothLinks == nullptr) {
          bluetoothLinks = new LinkGroup(tft, 20, 100, 4);
          bluetoothLinks->addLink(SUB_TITLE_BLUETOOTH_SETTINGS, SCREEN_BLUETOOTH_SETTINGS);
          bluetoothLinks->addLink(SUB_TITLE_BLUETOOTH_SCANNER, SCREEN_BLUETOOTH_SCANNER);
          bluetoothLinks->addLink(SUB_TITLE_BLUETOOTH_CONNECT, SCREEN_BLUETOOTH_CONNECT);
          }
        bluetoothLinks->draw();
        break;
      
      case BLUETOOTH_SETTINGS:
        subHeader.draw(SUB_TITLE_BLUETOOTH_SETTINGS);
        comingSoon.draw();  
        break;
        
      case BLUETOOTH_SCANNER:
        subHeader.draw(SUB_TITLE_BLUETOOTH_SCANNER);
        comingSoon.draw();  
        break;
        
      case BLUETOOTH_CONNECT:
        subHeader.draw(SUB_TITLE_BLUETOOTH_CONNECT);
        comingSoon.draw();  
        break;
      
      default:
        Serial.println("BluetoothScreen::draw: Unexpected btState=" + String(btState));
        break;
    }

    // Update screen state
    currentScreen = BLUETOOTH_SCREEN_STATE;
  }

  bool handleTouch(uint16_t touchX, uint16_t touchY) override {
    // Check if back button was touched
    if (backLink != nullptr && backLink->checkTouch(touchX, touchY)) {
      Serial.println("Back link touched");

      if (btState != BLUETOOTH_MAIN) {
        // If in any sub-screen, go back to main Bluetooth screen
        btState = BLUETOOTH_MAIN;
        draw();
        return false;  // Don't go back to main menu yet
      } else {
        // If in main Bluetooth screen, return to main menu
        return true;
      }
    }

    // Handle link touches in main Bluetooth screen
    if (btState == BLUETOOTH_MAIN && bluetoothLinks != nullptr) {
      if (bluetoothLinks->handleTouch(touchX, touchY)) {
        return false;  // We handled the touch
      }
    }

    return false;
  }

  void processSelection() override {
    if (btState == BLUETOOTH_MAIN && bluetoothLinks != nullptr && bluetoothLinks->hasSelection()) {
      ScreenDestination destination = bluetoothLinks->getSelectedDestination();

      switch (destination) {
        case SCREEN_BLUETOOTH_SETTINGS:
          Serial.println("Transitioning to Bluetooth Settings screen");
          btState = BLUETOOTH_SETTINGS;
          bluetoothLinks->clearSelection();
          draw();  // Redraw settings state
          break;
        case SCREEN_BLUETOOTH_SCANNER:
          Serial.println("Transitioning to Bluetooth Scanner screen");
          btState = BLUETOOTH_SCANNER;
          bluetoothLinks->clearSelection();
          draw();  // Redraw scanner state
          break;
        case SCREEN_BLUETOOTH_CONNECT:
          Serial.println("Transitioning to Bluetooth Connect screen");
          btState = BLUETOOTH_CONNECT;
          bluetoothLinks->clearSelection();
          draw();  // Redraw connect state 
          break;
      }
    }
  }

  void cleanup() override {
    if (backLink != nullptr) {
      delete backLink;
      backLink = nullptr;
    }

    if (bluetoothLinks != nullptr) {
      delete bluetoothLinks;
      bluetoothLinks = nullptr;
    }
  }
};

#endif  // BLUETOOTH_SCREEN_H
