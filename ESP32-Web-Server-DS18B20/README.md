# ESP32 Web Server with DS18B20 Temperature Sensor

A simple project turning an ESP32 into its own mini web server, displaying a live temperature reading from a DS18B20 sensor, viewable from any browser on the same WiFi network.

Watch the video here: YouTube 

## What you need
- ESP32 dev board
- DS18B20 temperature sensor
- Cable for connections
- Jumper Wires (3) 
- Arduino IDE with ESP32 board support installed

## Libraries required
Install these via Arduino IDE → Sketch → Include Library → Manage Libraries:
- `OneWire`
- `DallasTemperature`

## Wiring
- DS18B20 data pin → GPIO4 on the ESP32
- DS18B20 VCC → 3.3V
- DS18B20 GND → GND

## Setup
1. Open the `.ino` file in Arduino IDE
2. Replace `ssid` and `password` with your own WiFi network name and password
3. Upload to your ESP32
4. Open the Serial Monitor (115200 baud) and wait for it to print "Connected!" along with an IP address
5. Type that IP address into any browser on the same network to see the live temperature reading

## Troubleshooting
- If Serial Monitor doesn't show an IP address, try unplugging and reconnecting the ESP32, then re-open Serial Monitor
- Make sure your device (phone/PC/iPad) is on the same WiFi network as the ESP32

---
Part of my **Simple Projects Series** a quick, small DIY tech and embedded builds.

