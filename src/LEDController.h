#pragma once

#define PWM_PERIOD 256

#include "Arduino.h"
#include "pwm.h"

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

            uint32 io_info[4][3] = {
                // MUX, FUNC, PIN
                //	{PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5,   5}, // D1
                    {PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4,   4}, // D2 white
                //	{PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0,   0}, // D3
                //	{PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2,   2}, // D4
                    {PERIPHS_IO_MUX_MTMS_U,  FUNC_GPIO14, 14}, // D5 red
                    {PERIPHS_IO_MUX_MTDI_U,  FUNC_GPIO12, 12}, // D6 green
                    {PERIPHS_IO_MUX_MTCK_U,  FUNC_GPIO13, 13}, // D7 blue
                //	{PERIPHS_IO_MUX_MTDO_U,  FUNC_GPIO15 ,15}, // D8
            };
            uint32 pwm_duty_init[4] = {0, 0, 0, 0};
            pwm_init(PWM_PERIOD, pwm_duty_init, 4, io_info);
            pwm_start();

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

        void rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
            _red = map(red, 0, 255, 0, PWM_PERIOD);
            _green = map(green, 0, 255, 0, PWM_PERIOD);
            _blue = map(blue, 0, 255, 0, PWM_PERIOD);
            _white = map(white, 0, 255, 0, PWM_PERIOD);

            set();
        }

    private:
        uint8_t _whitePin, _redPin, _greenPin, _bluePin;
        uint16_t _temperature;
        uint16_t _brightness;
        uint16_t _white, _red, _green, _blue;

        void mapParams() {
            // Some magic...
            uint16_t colorMapper[6][4] {
                {500,  255,   0,   0},
                {2600, 255, 197, 143},
                {3200, 255, 241, 224},
                {5400, 255, 255, 251},
                {7000, 201, 226, 255},
                {10000,  0,  64, 255}
            };

            uint8_t mappingIndex = 0;
            for (int i = 1; i < 5; i++) {
                if (_temperature > colorMapper[i][0]) {
                    mappingIndex++;
                }
            }

            if (mappingIndex > 4) mappingIndex = 4;

            _red = map(_temperature, colorMapper[mappingIndex][0], colorMapper[mappingIndex+1][0], colorMapper[mappingIndex][1], colorMapper[mappingIndex+1][1]);
            _green = map(_temperature, colorMapper[mappingIndex][0], colorMapper[mappingIndex+1][0], colorMapper[mappingIndex][2], colorMapper[mappingIndex+1][2]);
            _blue = map(_temperature, colorMapper[mappingIndex][0], colorMapper[mappingIndex+1][0], colorMapper[mappingIndex][3], colorMapper[mappingIndex+1][3]);

            logger.log("1) map(%d, %d, %d, %d, %d) = %d", _temperature, colorMapper[mappingIndex][0], colorMapper[mappingIndex+1][0], colorMapper[mappingIndex][3], colorMapper[mappingIndex+1][3], _blue);


            if (_brightness >= 20) {
                _white = map(_brightness, 20, 100, 0, 255);
            } else {
                _white = 0;
                _red = map(_brightness, 0, 20, 0, _red);
                _green = map(_brightness, 0, 20, 0, _green);
                _blue = map(_brightness, 0, 20, 0, _blue);
                logger.log("2) map(%d, %d, %d, %d, %d) = %d", _brightness, 0, 20, 0, _blue, _blue);
            }

            _red = map(_red, 0, 255, 0, PWM_PERIOD);
            _green = map(_green, 0, 255, 0, PWM_PERIOD);
            _blue = map(_blue, 0, 255, 0, PWM_PERIOD);
            _white = map(_white, 0, 255, 0, PWM_PERIOD);

            set();
        }

        void set() {
            pwm_set_duty(_white, 0);
            pwm_set_duty(_red, 1);
            pwm_set_duty(_green, 2);
            pwm_set_duty(_blue, 3);

            pwm_start();

            logger.log("%d %d %d %d", _red, _green, _blue, _white);
        }
};