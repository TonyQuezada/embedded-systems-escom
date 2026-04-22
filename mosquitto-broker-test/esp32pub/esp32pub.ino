#include <WiFi.h>
#include <PubSubClient.h>

// ─── Configuración WiFi ───────────────────────────────────────────
const char* WIFI_SSID     = "TU_RED_WIFI";
const char* WIFI_PASSWORD = "TU_CONTRASEÑA";

// ─── Configuración MQTT ───────────────────────────────────────────
const char* MQTT_BROKER_IP = "192.168.1.100"; // IP de tu Raspberry Pi
const int   MQTT_PORT      = 1884;            // Puerto bare-metal (no Docker)
const char* MQTT_CLIENT_ID = "ESP32_Publisher";
const char* MQTT_TOPIC     = "esp32/test";

// ─── Intervalo de publicación (ms) ───────────────────────────────
const long PUBLISH_INTERVAL = 5000; // cada 5 segundos

// ─── Objetos globales ─────────────────────────────────────────────
WiFiClient   espClient;
PubSubClient mqttClient(espClient);
unsigned long lastPublishTime = 0;
int messageCount = 0;

// ─── Conexión WiFi ────────────────────────────────────────────────
void connectWiFi() {
  Serial.print("Conectando a WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi conectado!");
  Serial.print("IP de la ESP32: ");
  Serial.println(WiFi.localIP());
}

// ─── Conexión MQTT ────────────────────────────────────────────────
void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando al broker MQTT...");

    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      Serial.println(" ✅ Conectado!");
    } else {
      Serial.print(" ❌ Error, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" — reintentando en 5 segundos.");
      delay(5000);
    }
  }
}

// ─── Setup ────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(1000);

  connectWiFi();

  mqttClient.setServer(MQTT_BROKER_IP, MQTT_PORT);
}

// ─── Loop ─────────────────────────────────────────────────────────
void loop() {
  // Reconectar si se pierde la conexión
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop();

  // Publicar mensaje cada PUBLISH_INTERVAL milisegundos
  unsigned long now = millis();
  if (now - lastPublishTime >= PUBLISH_INTERVAL) {
    lastPublishTime = now;
    messageCount++;

    // Construir payload
    String payload = "Mensaje #" + String(messageCount) +
                     " desde ESP32 | Uptime: " + String(now / 1000) + "s";

    // Publicar
    if (mqttClient.publish(MQTT_TOPIC, payload.c_str())) {
      Serial.print("📤 Publicado en [");
      Serial.print(MQTT_TOPIC);
      Serial.print("]: ");
      Serial.println(payload);
    } else {
      Serial.println("❌ Error al publicar.");
    }
  }
}
