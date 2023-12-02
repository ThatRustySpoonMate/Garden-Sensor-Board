#include "main.hpp"


void setup() {
  
  setCpuFrequencyMhz(80);

  Serial.begin(115200);

  pinMode(SOIL_MOISUTRE_SENS_GND, OUTPUT);

  setup_mqtt(MQTT_BROKER_IP, MQTT_BROKER_PORT, DEVICE_ID, MQTT_MANAGEMENT_TOPIC);

}

void loop() {

}

void upon_wake() {
  // Connect to WIFI
  setup_wifi(WIFI_SSID, WIFI_PASSWORD);
  

  
  

  // Connect to MQTT

  // Power up Soil sensor

  // Take Reading

  // Power down soil sensor

  // Disconnect WIFI & MQTT

  // Go to sleep
}




