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
  static float tempReadingRaw, humidityReadingRaw, pressureReadingRaw, altitudeReadingRaw;
  static String moistureReadingStr, tempReadingStr, humidityReadingStr, pressureReadingStr, altitudeReadingStr;
  
  // Connect to WIFI
  setup_wifi(WIFI_SSID, WIFI_PASSWORD);

  // Connect to MQTT
  mqtt_reconnect();

  // Read soil moisture and BME280 sensors
  readSensors(&moistureReadingRaw, &tempReadingRaw, &humidityReadingRaw, &pressureReadingRaw, &altitudeReadingRaw);

  /* Convert readings to string objects */
  moistureReadingStr = String(moistureReadingRaw);
  tempReadingStr = String(tempReadingRaw);
  humidityReadingStr = String(humidityReadingRaw);
  pressureReadingStr = String(pressureReadingRaw);
  altitudeReadingStr = String(altitudeReadingRaw);

  /* Transmit Soil moisture reading to MQTT Broker */
  mqtt_transmit(MQTT_TOPIC_MOISTURE, moistureReadingStr.c_str());

  /* Transmit BME280 Readings to MQTT Broker */
  mqtt_transmit(MQTT_TOPIC_TEMPERATURE, tempReadingStr.c_str()); 
  mqtt_transmit(MQTT_TOPIC_HUMIDITY, humidityReadingStr.c_str()); 
  mqtt_transmit(MQTT_TOPIC_PRESSURE, pressureReadingStr.c_str()); 
  mqtt_transmit(MQTT_TOPIC_ALTITUDE, altitudeReadingStr.c_str()); 

  // Disconnect WIFI & MQTT
  delay(500); // Allow time to transmit message before disconnecting
  mqtt_disconnect();
  //wifi_disconnect();
}




