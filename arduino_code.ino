#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "";
const char* password = "";

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);


void handleData() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("❌ Failed to read from DHT sensor!");
    server.send(500, "application/json", "{\"error\":\"Sensor read failed\"}");
    return;
  }

  String json = "{\"temp\":" + String(t, 1) + ",\"hum\":" + String(h, 1) + "}";
  Serial.println("📤 Sending JSON: " + json);
  server.send(200, "application/json", json);
}

void setup() {
  // Allow time for Serial to open
  Serial.begin(115200);
  delay(1000); // ⏳ Give Serial Monitor time to start
  Serial.println("🔌 Booting ESP32...");

  dht.begin();
  Serial.println("🌡️ DHT sensor initialized.");

  WiFi.begin(ssid, password);
  Serial.print("📡 Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Connected to Wi-Fi");
  Serial.print("🌐 IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/data", handleData);
  server.begin();
  Serial.println("🚀 HTTP server started at /data");
}

void loop() {
  server.handleClient();
}
