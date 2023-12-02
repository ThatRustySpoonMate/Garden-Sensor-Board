#include "main.hpp"

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  300      /* Time ESP32 will go to sleep (in seconds) */

void setup() {

  setCpuFrequencyMhz(80);

  Serial.begin(115200);

  pinMode(SOIL_MOISUTRE_SENS_GND, PULLUP);

  setup_mqtt(MQTT_BROKER_IP, MQTT_BROKER_PORT, DEVICE_ID, MQTT_MANAGEMENT_TOPIC);

}

void loop() {
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  upon_wake();
  esp_deep_sleep_start();
}

void upon_wake() {
  static uint16_t moisture_reading_raw;

  
  // Connect to WIFI
  setup_wifi(WIFI_SSID, WIFI_PASSWORD);

  // Connect to MQTT
  mqtt_reconnect();

  // Power up Soil sensor
  digitalWrite(SOIL_MOISUTRE_SENS_GND, LOW);

  // Take Reading
  delay(100); // Allow time for startup of soil moisture sensor
  moisture_reading_raw = analogRead(SOIL_MOISTURE_SENS_DIN);

  // Power down soil sensor
  digitalWrite(SOIL_MOISUTRE_SENS_GND, HIGH);

  // Disconnect WIFI & MQTT
  mqtt_disconnect();
}




