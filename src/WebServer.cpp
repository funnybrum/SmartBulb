#include "Bulb.h"

char buffer[4096];

WebServer::WebServer(NetworkSettings* networkSettings, Logger* logger)
    :WebServerBase(networkSettings, logger) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));
    server->on("/on", std::bind(&WebServer::handle_on, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/reset", std::bind(&WebServer::handle_reset, this));
    server->on("/brightness", std::bind(&WebServer::handle_brightness, this));
    server->on("/temperature", std::bind(&WebServer::handle_temperature, this));
    server->on("/rgbw", std::bind(&WebServer::handle_rgbw, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_get() {
    char resp[strlen_P(GET_JSON) + 32];
    sprintf_P(resp,
              GET_JSON,
              0,
              0,
              0,
              0);
    server->send(200, "application/json", resp);
}

void WebServer::handle_settings() {
    bool save = false;

    wifi.parse_config_params(this, save);
    // process_setting("some_settings", settingsData.bulb.some_settings, save);

    if (save) {
        settings.save();
    }

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        MODEL_NAME,
        network_settings,
        0.0f);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_reset() {
    logger->log("/hard_reset");
    settings.erase();
    server->send(200, "text/plain", "Settings erased.");
}

void WebServer::handle_on() {
    logger->log("/on");
    server->send(200);
    // TODO
}

void WebServer::handle_off() {
    logger->log("/off");
    server->send(200);
    // TODO
}

void WebServer::handle_brightness() {
    uint16_t val = server->arg("val").toInt();
    ledController.setBrightness(val);
    server->send(200);
}

void WebServer::handle_temperature() {
    uint16_t val = server->arg("val").toInt();
    ledController.setTemperature(val);
    server->send(200);
}

void WebServer::handle_rgbw() {
    if (server->args() == 1 && server->argName(0).length() == 8) {
        uint32_t rgbw = strtoul(server->argName(0).c_str(), NULL, 16);
        uint8_t r = rgbw >> 24;
        uint8_t g = rgbw >> 16 & 0xFF;
        uint8_t b = rgbw >> 8 & 0xFF;
        uint8_t w = rgbw & 0xFF;
        ledController.rgbw(r, g, b, w);
        server->send(200);
        return;
    }

    server->send(200, "text/html", "Missing RGBW value. Try with /rgbw?FF000000 .");
}