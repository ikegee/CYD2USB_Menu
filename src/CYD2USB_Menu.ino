/* (c) 2026 G.E. Eidsness */

/** 
 * IMPORTANT: Use the calibration values from attached TFT_eSPI_User_Setup.txt for the 2.8" TFT display configuration. 
 * These values are critical for accurate touch input mapping for the ESP32-2432S028R XPT2046 touchscreen. 
 * Incorrect calibration can lead to touch coordinates being misaligned with the display, causing touch interactions to be inaccurate or unresponsive.
 * The calibration values are typically found in the User_Setup.h file of the TFT_eSPI library.
*/

// build and monitor script: run_build_monitor.sh

#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <XPT2046_Touchscreen.h>

#include "bluetooth_screen.h"
#include "device_info_screen.h"
#include "header.h"
#include "main_menu_screen.h"
#include "screen_manager.h"
#include "screen_states.h"
#include "utils.h"
#include "wifi_screen.h"

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);
Header header(&tft);
ScreenManager* screenManager;

// Touch debounce variables
unsigned long lastTouchTime = 0;
const unsigned long touchDebounce = 300;  // 300ms debounce

// Touch state tracking
bool wasTouching = false;

// Define the global screen state
ScreenState currentScreen = MAIN_MENU_STATE;

void setup() {
  Serial.begin(115200);
  delay(1000);

  tft.init();
  tft.setRotation(0);  // Portrait
  tft.fillScreen(TFT_NAVY);

  // Initialize SPI for touch screen
  SPI.begin(TOUCH_SCLK, TOUCH_MISO, TOUCH_MOSI, TOUCH_CS);

  // Initialize touchscreen
  bool touch_status = ts.begin();
  ts.setRotation(0);
  SPI.endTransaction();

  // Initialize screen manager
  screenManager = new ScreenManager(&tft, &header);
  screenManager->registerScreen(MAIN_MENU_STATE, new MainMenuScreen(&tft, &header));
  screenManager->registerScreen(WIFI_SCREEN_STATE, new WiFiScreen(&tft, &header));
  screenManager->registerScreen(BLUETOOTH_SCREEN_STATE, new BluetoothScreen(&tft, &header));
  screenManager->registerScreen(DEVICE_INFO_SCREEN_STATE, new DeviceInfoScreen(&tft, &header));
  // Now try to show the main menu
  screenManager->showScreen(MAIN_MENU_STATE);
}

void loop() {
  static unsigned long lastTouchTime = 0;
  unsigned long currentTime = millis();
  
  if (ts.touched()) {
    if (!wasTouching) {
      // Touch just started
      wasTouching = true;
      TS_Point p = ts.getPoint();
      
      if (isValidTouch(p.x, p.y)) {
        uint16_t touchX = p.x;
        uint16_t touchY = p.y;
        mapTouchToScreen(&touchX, &touchY);
        
        Serial.println("Mapped touch: x=" + String(touchX) + ", y=" + String(touchY));
        // Handle touch with screen manager
        screenManager->handleTouch(touchX, touchY);
      }
    }
  } else if (wasTouching) {
    // Touch has been released
    wasTouching = false;
    Serial.println("Touch released, processing selection");
    // Process selections for current screen
    screenManager->processSelection();
  }
  
  delay(10);
}

