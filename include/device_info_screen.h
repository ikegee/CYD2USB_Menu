#ifndef DEVICE_INFO_SCREEN_H
#define DEVICE_INFO_SCREEN_H

#include <SPI.h>
#include "screen_manager.h"
#include "sub_header.h"
#include "back_link.h"
#include "screen_states.h"


class DeviceInfoScreen : public Screen {
private:
    SubHeader subHeader;
    BackLink* backLink;
    
public:
    DeviceInfoScreen(TFT_eSPI* tft, Header* header) 
        : Screen(tft, header), subHeader(tft), backLink(nullptr) {}
    
    ~DeviceInfoScreen() {
        cleanup();
    }

   
    void draw() override {
        // Clear screen
        tft->fillScreen(TFT_NAVY);
        header->draw();
        subHeader.draw(ITEM_DEVICE_INFO);
        
        // Create back link if it doesn't exist
        if (backLink == nullptr) {
            backLink = new BackLink(tft, 20, 60);
        }
        backLink->draw();
        
        // Draw device info content
        tft->setTextColor(TFT_WHITE);
        tft->setTextSize(1);
        
        tft->setCursor(20, 100);
        tft->println("ESP32 Chip Model: " + String(ESP.getChipModel()));
        
        tft->setCursor(20, 120);
        tft->println("Chip Revision: " + String(ESP.getChipRevision()));
        
        tft->setCursor(20, 140);
        tft->println("CPU Freq: " + String(ESP.getCpuFreqMHz()) + " MHz");
        
        tft->setCursor(20, 160);
        tft->println("Flash Size: " + String(ESP.getFlashChipSize() / 1024 / 1024) + " MB");
        
        tft->setCursor(20, 180);
        tft->println("Free Heap: " + String(ESP.getFreeHeap() / 1024) + " KB");
        
        tft->setCursor(20, 200);
        tft->println("SDK Version: " + String(ESP.getSdkVersion()));
       
        // Update screen state
        currentScreen = DEVICE_INFO_SCREEN_STATE;
    }
    
    bool handleTouch(uint16_t touchX, uint16_t touchY) override {
        if (backLink != nullptr) {
            return backLink->checkTouch(touchX, touchY);
        }
        return false;
    }
    
    void processSelection() override {
        // No selections to process in this simple screen
    }
    
    void cleanup() override {
        if (backLink != nullptr) {
            delete backLink;
            backLink = nullptr;
        }
    }
};

#endif // DEVICE_INFO_SCREEN_H

