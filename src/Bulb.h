#ifndef _POWER_MONITOR_H_
#define _POWER_MONITOR_H_

#define HTTP_PORT 80
#define HOSTNAME "smart-bulb"

#define LOG_SIZE 8192

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "Settings.h"
#include "WiFi.h"
#include "Logger.h"
#include "WebServer.h"

struct SettingsData {
    NetworkSettings network;
    // struct LED {
        // uint8_t red;
        // uint8_t green;
        // uint8_t blue;
        // uint8_t white;
    // } led;
    // TODO smart bulb settings
};

#define NO_NAME
// #define SONOFF_B1


#ifdef NO_NAME
    // Chineese no-name bulb with SLM211A for the white LEDs and transistors driving the RGB 5050 LEDs.
    #define MODEL_NAME "NoName"
    #define GREEN_PIN  12  // GPIO12
    #define BLUE_PIN   13  // GPIO13
    #define RED_PIN    14  // GPIO14
    #define WHITE_PIN  4   // GPIO04
#endif

#ifdef SONOFF_B1
    // TODO
#endif


extern Logger logger;
extern Settings settings;
extern SettingsData settingsData;
extern WiFiManager wifi;

#endif
