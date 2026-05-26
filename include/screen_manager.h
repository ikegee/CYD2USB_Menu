#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <TFT_eSPI.h>
#include <vector> 
#include "header.h"
#include "screen_states.h"

// Forward declarations
class Screen;
class MainMenuScreen;
class WiFiScreen;
class BluetoothScreen;
class DeviceInfoScreen;

// Forward declarations
class Screen;

class ScreenManager {
    private:
        TFT_eSPI* tft;
        Header* header;
        // Replace fixed array with dynamic vector
        std::vector<Screen*> screens;
        ScreenState currentScreenState;

    public:
        ScreenManager(TFT_eSPI* tft, Header* header);
        ~ScreenManager();
        
        void registerScreen(ScreenState state, Screen* screen);
        void showScreen(ScreenState state);
        bool handleTouch(uint16_t touchX, uint16_t touchY);
        void processSelection();
    };

// Base Screen class
class Screen {
    protected:
        TFT_eSPI* tft;
        Header* header;
        ScreenManager* screenManager; // Add this
        
    public:
        Screen(TFT_eSPI* display, Header* headerObj, ScreenManager* manager = nullptr) 
            : tft(display), header(headerObj), screenManager(manager) {}
        
        void setScreenManager(ScreenManager* manager) {
            screenManager = manager;
        }
        virtual ~Screen() {}
        
        virtual void draw() = 0;
        virtual bool handleTouch(uint16_t touchX, uint16_t touchY) = 0;
        virtual void processSelection() = 0;
        virtual void cleanup() = 0;
    };
    
#endif // SCREEN_MANAGER_H
