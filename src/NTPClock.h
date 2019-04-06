#pragma once

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

#define HOURS_TO_MILLIS(h) ((h) * 60 * 60 * 1000)  

class NTPClock {
    public:
        NTPClock(uint32_t updateInterval=HOURS_TO_MILLIS(4), const char* ntpServer="bg.pool.ntp.org") {        
            this->ntpClient = new NTPClient(ntpUDP, ntpServer, 0, updateInterval);
        }

        void begin() {
            this->ntpClient->begin();
        }

        void loop() {
            this->ntpClient->update();
        }

        int getYear() {
            time_t rawtime = ntpClient->getEpochTime();
            struct tm * ti;
            ti = localtime (&rawtime);
            //tm_year starts from 1900. I.e. 105 stands for year 2005.
            return ti->tm_year + 1900;
        }

        int getMonth() {
            time_t rawtime = ntpClient->getEpochTime();
            struct tm * ti;
            ti = localtime (&rawtime);
            //tm_mon starts with zero, i.e. 0 stands for January.
            return ti->tm_mon + 1;
        }

        int getDay() {
            time_t rawtime = ntpClient->getEpochTime();
            struct tm * ti;
            ti = localtime (&rawtime);
            return ti->tm_mday;
        }

        int getHour() {
            time_t rawtime = ntpClient->getEpochTime();
            struct tm * ti;
            ti = localtime (&rawtime);
            return ti->tm_hour;
        }

        uint8_t getMinute() {
            time_t rawtime = ntpClient->getEpochTime();
            struct tm * ti;
            ti = localtime (&rawtime);
            return ti->tm_min;
        }

        uint8_t getSeconds() {
            time_t rawtime = ntpClient->getEpochTime();
            struct tm * ti;
            ti = localtime (&rawtime);
            return ti->tm_sec;
        }

    private:
        NTPClient* ntpClient = NULL;
        WiFiUDP ntpUDP = WiFiUDP();
};