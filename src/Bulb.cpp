#include "Bulb.h"


void initSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);
}

Logger logger = Logger();
SettingsData settingsData = SettingsData();
Settings settings = Settings(&logger, (void*)(&settingsData), sizeof(SettingsData), initSettings);
WiFiManager wifi = WiFiManager(&logger, &settingsData.network);

WebServer webServer = WebServer(&settingsData.network, &logger);

void setup()
{
    Serial.begin(115200);
    logger.begin();
    settings.begin();
    wifi.begin();
    webServer.begin();

    // TODO begin

    wifi.connect();
}

void loop() {
    logger.loop();
    settings.loop();
    wifi.loop();
    webServer.loop();

    // TODO loop

    delay(100);
}
