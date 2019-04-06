# "Smart" bulb
## Summary

!!!WORK IN PROGRESS!!! Nothing is tested and confirmed to be working yet!

Custom firmware for several "smart" bulbs:
 * A common RGBW Chinees LED bulb (check the image below). choifoo, oobest, ...
 * Sonoff B1 (not yet, but will be supported)

 "Smart" is quoted because there is nothing smart in these yet. However there are plans to remove the quotes above by providing a functionality that makes them smart and includes:
  * Automatic color adjustments (cold white light at day, warm white light at night) dependings on the current sun light (estimated based on the sunrise and sunset time).
  * Automatic dimming function depending on the day time. Full brightness during the day, reduced during the evening, minimum during the night.a

## Compiling

The project requires additional libraries that should be retrieved from another github repos. Execute the following commands to get this done (from the project root folder).

```
cd lib/
git clone https://github.com/funnybrum/esp8266-base.git
git clone https://github.com/arduino-libraries/NTPClient  # version 3.1.0
git clone https://github.com/dmkishi/Dusk2Dawn            # version 1.0.1
```

After that choose the proper hardware to be flashed - NO_NAME or SONOFF_B1. Apply changes for the following ... files:
 * Bulb.h - define the hardware.
 * platformio.ini - choose the proper plaform.

Initial flashing should be done with USB to 3.3V serial adapter.
 * [No name Chieese bulb](https://github.com/funnybrum/SmartBulb/docs/)

## Over-the-air programming

The firmware supports OTA update. Below curl command executed from the project root will perform the update:
> curl -F "image=@.pioenvs/.../firmware.bin" http://smart-bulb/update

## Network configuring

After the firmware is successfully flashed and the microcontroler restarted it will enter in access point mode and open a network named smart-bulb. Join that network, set an IP address of 192.168.0.2 and network mask 255.255.255.0 to the computer. Go to http://192.168.0.1/ and you'll see the settings page.

Configure the desired network preferences. If the controller fail to join the specified WiFi network - it will enter AP mode again and can be accessed for reconfiguration as noted above.

## Debugging

There are several log messages produced by the firmware. In order to access them - go to the http://ip_addr/logs and you'll see the last 1024 bytes of log messages.

## HTTP API endpoints
Once flashed the microcontroller will start a web server with the following endpoints 
 * http://{ip_addr}/ -> redirect to http://{ip_addr}/settings
 * http://{ip_addr}/settings -> Configuration page.
 * http://{ip_addr}/get -> A GET request will return JSON document with the current bulb state.
 * http://{ip_addr}/on -> Turn on the power to the connected device.
 * http://{ip_addr}/off -> Turn of the power to the connected device.
 * http://{ip_addr}/reboot -> Reboots the microcontroller.
 * http://{ip_addr}/reset -> Erase the settings and return the microcontroller to the initial state.
 * http://{ip_addr}/logs -> Return the logs from the microcontroller.
 * http://{ip_addr}/update -> ESP8266 OTA firmware update endpoint.  