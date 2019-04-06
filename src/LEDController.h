#pragma once

#include "Arduino.h"

class LEDController {
    public:
        LEDController(uint8_t whitePin, uint8_t redPin, uint8_t greenPin, uint8_t bluePin) {
            _whitePin = whitePin;
            _redPin = redPin;
            _greenPin = greenPin;
            _bluePin = bluePin;
        }

        void begin() {
            pinMode(_whitePin, OUTPUT);
            pinMode(_redPin, OUTPUT);
            pinMode(_greenPin, OUTPUT);
            pinMode(_bluePin, OUTPUT);

            digitalWrite(_whitePin, 0);
            digitalWrite(_redPin, 0);
            digitalWrite(_greenPin, 0);
            digitalWrite(_bluePin, 0);

            analogWriteFreq(8192);

            _white = 0;
            _red = 0;
            _green = 0;
            _blue = 0;
            _brightness = 10;
            _temperature = 2700;
            mapParams();
        }

        void loop() {
        }

        void setTemperature(uint16_t temperature) {
            if (_temperature == temperature) {
                return;
            }
            _temperature = temperature;
            mapParams();
        }

        void setBrightness(uint8_t brightness) {
            if (_brightness == brightness) {
                return;
            }
            _brightness = brightness;
            mapParams();
        }

    private:
        uint8_t _whitePin, _redPin, _greenPin, _bluePin;
        uint16_t _temperature;
        uint16_t _brightness;
        uint16_t _white, _red, _green, _blue;

        void mapParams() {
            // Some magic...
            uint16_t colorMapper[4][4] {
                {2600, 255, 197, 143},
                {3200, 255, 241, 224},
                {5400, 255, 255, 251},
                {7000, 201, 226, 255}
            };

            uint8_t mappingIndex = 0;
            for (int i = 0; i < 3; i++) {
                if (colorMapper[i][0] <= _temperature) {
                    mappingIndex++;
                }
            }

            if (mappingIndex > 2) mappingIndex = 2;

            _red = map(_temperature, colorMapper[mappingIndex][0], colorMapper[mappingIndex+1][0], colorMapper[mappingIndex][1], colorMapper[mappingIndex+1][1]);
            _green = map(_temperature, colorMapper[mappingIndex][0], colorMapper[mappingIndex+1][0], colorMapper[mappingIndex][2], colorMapper[mappingIndex+1][2]);
            _blue = map(_temperature, colorMapper[mappingIndex][0], colorMapper[mappingIndex+1][0], colorMapper[mappingIndex][3], colorMapper[mappingIndex+1][3]);

            if (_brightness >= 20) {
                _white = map(_brightness, 20, 100, 0, 255);
            } else {
                _white = 0;
                _red = map(_brightness, 0, 20, 0, _red);
                _green = map(_brightness, 0, 20, 0, _green);
                _blue = map(_brightness, 0, 20, 0, _blue);
            }

            // Remap to the 1023 range
            _red = map(_red, 0, 255, 0, 1023);
            _green = map(_green, 0, 255, 0, 1023);
            _blue = map(_blue, 0, 255, 0, 1023);
            _white = map(_white, 0, 255, 0, 1023);

            // And finally - set the PWM.
            analogWrite(_redPin, _red);
            analogWrite(_greenPin, _green);
            analogWrite(_bluePin, _blue);
            analogWrite(_whitePin, _white);
        }
};