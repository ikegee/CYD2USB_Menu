#include "screen_manager.h"

ScreenManager::ScreenManager(TFT_eSPI* tft, Header* header) 
    : tft(tft), header(header), currentScreenState(MAIN_MENU_STATE) {
    // No need to initialize vector elements - it starts empty
}

ScreenManager::~ScreenManager() {
    // Clean up all screens
    for (auto screen : screens) {
        if (screen != nullptr) {
            delete screen;
        }
    }
    screens.clear();
}

void ScreenManager::registerScreen(ScreenState state, Screen* screen) {
    // Ensure the vector is large enough to hold the screen at index 'state'
    if (state >= screens.size()) {
        screens.resize(state + 1, nullptr);
    }
    // Store the screen at the appropriate index
    screens[state] = screen;
    screen->setScreenManager(this); // Set the screen manager reference
}

void ScreenManager::showScreen(ScreenState state) {
    // Start drawing to off-screen buffer
    tft->startWrite();
    // Draw new screen to buffer if it exists and is within bounds
    if (state < screens.size() && screens[state] != nullptr) {
        screens[state]->draw();
    }
    // Update current screen state
    currentScreenState = state;
    // Push buffer to display (single operation)
    tft->endWrite();
}

bool ScreenManager::handleTouch(uint16_t touchX, uint16_t touchY) {
    Serial.println("ScreenManager handling touch at: " + String(touchX) + "," + String(touchY));
    
    if (currentScreenState < screens.size() && screens[currentScreenState] != nullptr) {
        // If the screen's handleTouch returns true, it means we should go back to the main menu
        if (screens[currentScreenState]->handleTouch(touchX, touchY)) {
            // Go back to the main menu
            showScreen(MAIN_MENU_STATE);
            return true;
        }
    }
    
    return false;
}

void ScreenManager::processSelection() {
    Serial.println("ScreenManager::processSelection called");
    
    if (currentScreenState < screens.size() && screens[currentScreenState] != nullptr) {
        Serial.println("Calling processSelection on screen for state: " + String(currentScreenState));
        screens[currentScreenState]->processSelection();
    } else {
        Serial.println("WARNING: No valid screen to process selection");
    }
}

