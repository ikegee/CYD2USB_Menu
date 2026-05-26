#ifndef SCREEN_STATES_H
#define SCREEN_STATES_H

// All Screen state constants
#define SCREEN_MAIN_MENU 0
#define SCREEN_WIFI 1
#define SCREEN_BLUETOOTH 2
#define SCREEN_DEVICE_INFO 3
#define SCREEN_REBOOT 4
#define SCREEN_WIFI_SETTINGS 5
#define SCREEN_WIFI_SCANNER 6
#define SCREEN_WIFI_CONNECT 7
#define SCREEN_BLUETOOTH_SETTINGS 8
#define SCREEN_BLUETOOTH_SCANNER 9
#define SCREEN_BLUETOOTH_CONNECT 10

// Menu item constants
#define TITLE_PROJECT_NAME "CYD2USB Menu"
#define TITLE_MAIN_MENU "Main Menu"
#define TITLE_BLUETOOTH "Bluetooth"
#define ITEM_WIFI "Wi-Fi"
#define ITEM_BLUETOOTH "Bluetooth"
#define ITEM_DEVICE_INFO "Device Info"
#define ITEM_REBOOT "Reboot"

// Sub header constants
#define SUB_TITLE_WIFI_SETTINGS "WiFi Settings"
#define SUB_TITLE_WIFI_SCANNER "WiFi Scanner"
#define SUB_TITLE_WIFI_CONNECT "Connect to WiFi"
#define SUB_TITLE_BLUETOOTH_SETTINGS "Bluetooth Settings"
#define SUB_TITLE_BLUETOOTH_SCANNER "Bluetooth Scanner"
#define SUB_TITLE_BLUETOOTH_CONNECT "Connect Bluetooth"

// Screen state enum
enum ScreenState {
  MAIN_MENU_STATE,
  WIFI_SCREEN_STATE,
  BLUETOOTH_SCREEN_STATE,
  DEVICE_INFO_SCREEN_STATE,
  REBOOT_SCREEN_STATE
};
extern ScreenState currentScreen;

#endif  // SCREEN_STATES_H
