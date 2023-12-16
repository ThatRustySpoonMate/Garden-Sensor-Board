#include "SensorTasks.hpp"


void initSensors() {
    pinMode(SOIL_MOISUTRE_SENS_GND, PULLUP);

    return;
}

void readSensors(uint16_t *moistureReading) {
  // Power up Soil sensor
  digitalWrite(SOIL_MOISUTRE_SENS_GND, LOW);

  // Take Reading
  delay(500); // Allow time for startup of soil moisture sensor
  *moistureReading = analogRead(SOIL_MOISTURE_SENS_DIN);

  // Power down soil sensor
  digitalWrite(SOIL_MOISUTRE_SENS_GND, HIGH);

  return;
}