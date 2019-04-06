#include "Dusk2Dawn.h"
#include "NTPClock.h"

const char LIGHTMANAGER_CONFIG_PAGE[] PROGMEM = R"=====(
<fieldset style='display: inline-block; width: 300px'>
<legend>Light settings</legend>
Latitude:<br>
<input type="text" name="lm_lat" value="%s"><br>
<small><em>Bulb location latitude</em></small><br><br>
Longitude:<br>
<input type="text" name="lm_lon" value="%s"><br>
<small><em>Bulb location longitude</em></small><br><br>
</fieldset>
)=====";

struct LightManagerSettings {
    float lon;
    float lat;
};

class LightManager {
    public:
        LightManager(NTPClock* ntpClock) {
            // this->settings = settings;
            // this->dusk2down = new Dusk2Dawn(this->settings->lat, this->settings->lon, 0);
            this->dusk2down = new Dusk2Dawn(42.6450327, 23.3445709, 0);
            this->ntpClock = ntpClock;
        }

        void begin() {
        }

        void loop() {
            // if (this->ntpClock->getYear() > 1900) {
            //     char buf[128];
            //     sprintf(buf,
            //             "sunrise:%d; sunset:%d",
            //             dusk2down->sunrise(ntpClock->getYear(), ntpClock->getMonth(), ntpClock->getDay(), false),
            //             dusk2down->sunset(ntpClock->getYear(), ntpClock->getMonth(), ntpClock->getDay(), false));

            //     Serial.println(buf);
            // }
        }

    private:
        LightManagerSettings* settings = NULL;
        Dusk2Dawn* dusk2down = NULL;
        NTPClock* ntpClock = NULL;
};