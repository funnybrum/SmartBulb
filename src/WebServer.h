#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "Bulb.h"
#include "WebServerBase.h"
#include "WebPages.h"

class WebServer: public WebServerBase {
    public:
        WebServer(NetworkSettings* networkSettings, Logger* logger);
        void registerHandlers();
        void handle_root();
        void handle_get();
        void handle_on();
        void handle_off();
        void handle_settings();
        void handle_reset();
        void handle_brightness();
        void handle_temperature();
};

#endif
