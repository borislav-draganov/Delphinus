# Delphinus

## Overview
A simple web server running on an ESP8266 displaying the readings from 4 temperature sensors, specifically DS18B20 sensors.
Additionally added a CT Clamp sensor to measure the Amps - YHDC SCT013 20A version.

A D1 mini was used for this project.

## Goals
- Have a ESP8266 with 4 Dallas sensors connected
- Have it serve a web page, displaying the temperature readings of the sensors
- Have the ESP in AP mode so people can connect to it
- Have the ability to set a SSID and password of a network to which the ESP will try to connect. If it can't, it falls back to AP mode
- Have the ability to rename the sensors on the web page

## How to build
0. *(Optional)* Build the frontend - check intructions in `frontend` folder

1. Build and upload the firmware to the ESP8266 via PlatformIO GUI or

```bash
platformio run --target upload
```

2. Upload the contents of `data` folder to the microcontroller's FS

```bash
platformio run --target uploadfs
```

## Useful things
* [Case](https://www.thingiverse.com/thing:4056195)