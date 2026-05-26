#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "screen_manager.h"
#include "sub_header.h"
#include "text_link.h"
#include "screen_states.h"
#include "utils.h"


class MainMenuScreen : public Screen {
private:
    SubHeader subHeader;
    LinkGroup* menuLinks;

public:
    MainMenuScreen(TFT_eSPI* tft, Header* header) 
        : Screen(tft, header), subHeader(tft), menuLinks(nullptr) {}
       
    ~MainMenuScreen() {
        cleanup();
    }
    
    void draw() override {
        // Clear screen
        tft->fillScreen(TFT_NAVY);
        // Draw header
        header->draw();
        // Draw subheader
        subHeader.draw(TITLE_MAIN_MENU);
        // Set up and draw the menu links
        Serial.println("Setting up menu links, current menuLinks: " + String(menuLinks == nullptr ? "nullptr" : "valid"));
        
        if (menuLinks == nullptr) {
            Serial.println("Creating new LinkGroup");
            menuLinks = new LinkGroup(tft, 20, 100, 4);
            if (menuLinks == nullptr) {
                Serial.println("ERROR: Failed to allocate LinkGroup!");
                return;
            }
            Serial.println("Adding links to LinkGroup");
            menuLinks->addLink(ITEM_WIFI, WIFI_SCREEN_STATE);
            menuLinks->addLink(ITEM_BLUETOOTH, BLUETOOTH_SCREEN_STATE);
            menuLinks->addLink(ITEM_DEVICE_INFO, DEVICE_INFO_SCREEN_STATE);
            menuLinks->addLink(ITEM_REBOOT, REBOOT_SCREEN_STATE);
        }
        
        Serial.println("Drawing menu links");
        menuLinks->draw();
        Serial.println("Menu links drawn");
        
        // Update screen state
        currentScreen = MAIN_MENU_STATE;
        Serial.println("MainMenuScreen::draw() completed");
    }
    
    bool handleTouch(uint16_t touchX, uint16_t touchY) override {
        if (menuLinks != nullptr && menuLinks->handleTouch(touchX, touchY)) {
            // The link has been highlighted, now handle navigation
            return true;
        }
        return false;
    }

    void processSelection() override {
        Serial.println("MainMenuScreen::processSelection called");
        
        if (menuLinks != nullptr && menuLinks->hasSelection()) {
            ScreenDestination destination = menuLinks->getSelectedDestination();
            Serial.println("Selected destination: " + String(destination));
            
            // Process the selection based on destination
            switch (destination) {
              case WIFI_SCREEN_STATE:
                Serial.println("Transitioning to WiFi screen");
                screenManager->showScreen(WIFI_SCREEN_STATE);
                break;
              case BLUETOOTH_SCREEN_STATE:
                Serial.println("Transitioning to Bluetooth screen");
                screenManager->showScreen(BLUETOOTH_SCREEN_STATE);
                break;
              case DEVICE_INFO_SCREEN_STATE:
                Serial.println("Transitioning to Device Info screen");
                screenManager->showScreen(DEVICE_INFO_SCREEN_STATE);
                break;
              case REBOOT_SCREEN_STATE:
                Serial.println("Rebooting device");
                // Call the showRebootMessage function to display the reboot animation
                showRebootMessage(tft);
                // Note: ESP.restart() is called inside showRebootMessage, so execution won't reach here
            }
            
            menuLinks->clearSelection();
        } else {
            Serial.println("No menu selection to process");
        }
    }
    
    
    void cleanup() override {
        if (menuLinks != nullptr) {
            delete menuLinks;
            menuLinks = nullptr;
        }
    }
};

#endif // MAIN_MENU_SCREEN_H
