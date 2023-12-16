#include "Arduino.h"

#define SOIL_MOISUTRE_SENS_GND 15
#define SOIL_MOISTURE_SENS_DIN 33 // 5 - ADC1_CH4 for ESP32 Dev Board

void initSensors();

void readSensors(uint16_t *moistureReading);