#include "Bulb.h"


void initSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);
}

Logger logger = Logger();
SettingsData settingsData = SettingsData();
Settings settings = Settings(&logger, (void*)(&settingsData), sizeof(SettingsData), initSettings);
WiFiManager wifi = WiFiManager(&logger, &settingsData.network);

WebServer webServer = WebServer(&settingsData.network, &logger);

NTPClock ntpClock = NTPClock();
LightManager lm = LightManager(&ntpClock);
LEDController ledController = LEDController(WHITE_PIN, RED_PIN, GREEN_PIN, BLUE_PIN);

void setup()
{
    Serial.begin(115200);
    logger.begin();
    settings.begin();
    wifi.begin();
    webServer.begin();
    ntpClock.begin();
    lm.begin();
    ledController.begin();

    wifi.connect();
}

unsigned long lastPrint = millis();

void loop() {
    logger.loop();
    settings.loop();
    wifi.loop();
    webServer.loop();
    ntpClock.loop();
    lm.loop();
    ledController.loop();

    delay(100);
}
