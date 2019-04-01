#include "Bulb.h"

char buffer[4096];

WebServer::WebServer(NetworkSettings* networkSettings, Logger* logger)
    :WebServerBase(networkSettings, logger) {
    pinMode(RED_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(WHITE_PIN, OUTPUT);
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));
    server->on("/on", std::bind(&WebServer::handle_on, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/reset", std::bind(&WebServer::handle_reset, this));
    server->on("/red", std::bind(&WebServer::handle_red, this));
    server->on("/green", std::bind(&WebServer::handle_green, this));
    server->on("/blue", std::bind(&WebServer::handle_blue, this));
    server->on("/white", std::bind(&WebServer::handle_white, this));
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

void WebServer::led(uint8_t pin) {
    uint16_t val = server->arg("val").toInt();
    analogWrite(pin, val);
    server->send(200, "text/plain", "Done!");

    // if (server->hasArg("iaq")) {
    //     float iaq = server->arg("iaq").toFloat();
    //     led.blink(iaq);
        // server->send(200, "text/plain", "Just blinked!");
    // } else {
    //     server->send(400, "text/plain", "Missing iaq argument!");
    // }
}

void WebServer::handle_red() {
    led(RED_PIN);
}

void WebServer::handle_green() {
    led(GREEN_PIN);
}

void WebServer::handle_blue() {
    led(BLUE_PIN);
}

void WebServer::handle_white() {
    led(WHITE_PIN);
}
