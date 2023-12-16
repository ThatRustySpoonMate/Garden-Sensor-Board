#include "main.hpp"

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  300      /* Time ESP32 will go to sleep (in seconds) */

void setup() {

  setCpuFrequencyMhz(80);

  Serial.begin(115200);

  initSensors();

  setup_mqtt(MQTT_BROKER_IP, MQTT_BROKER_PORT, DEVICE_ID, MQTT_MANAGEMENT_TOPIC);

}

void loop() {
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  upon_wake();
  esp_deep_sleep_start();
}

void upon_wake() {
  static uint16_t moistureReadingRaw;
  static String moistureReadingStr;
  
  // Connect to WIFI
  setup_wifi(WIFI_SSID, WIFI_PASSWORD);

  // Connect to MQTT
  mqtt_reconnect();

  readSensors(&moistureReadingRaw);

  // Transmit reading to MQTT Broker
  moistureReadingStr = String(moistureReadingRaw);
  mqtt_transmit(MQTT_TOPIC_MOISTURE, moistureReadingStr.c_str());


  // Disconnect WIFI & MQTT
  delay(500); // Allow time to transmit message before disconnecting
  mqtt_disconnect();
  //wifi_disconnect();
}




