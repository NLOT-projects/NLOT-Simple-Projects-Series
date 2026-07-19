#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

#define ONE_WIRE_BUS 4  // DS18B20 data pin connected to GPIO4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  sensors.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // <-- use this address in your browser

  server.begin();
}

void loop() {
  // Reconnect WiFi automatically if it drops
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost, reconnecting...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Reconnected!");
    Serial.println(WiFi.localIP());
  }

  WiFiClient client = server.available();
  if (client) {
    // Wait briefly for the client's request data to arrive
    unsigned long timeout = millis();
    while (!client.available() && millis() - timeout < 5000) {
      delay(1);
    }

    // Read and discard the incoming request (we don't need to parse it)
    while (client.available()) {
      client.read();
    }

    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);

    String html = "<html><body style='font-family:sans-serif;text-align:center;margin-top:100px;'>";
    html += "<h1>Test Dashboard</h1>";
    html += "<h2>Temperature: " + String(tempC) + " &deg;C</h2>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "</body></html>";

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.print(html);
    delay(1);
    client.stop();
  }
}
