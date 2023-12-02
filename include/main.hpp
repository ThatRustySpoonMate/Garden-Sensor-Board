#include <Arduino.h>

#include "credentials.h"
#include "MQTTTasks.hpp"


#define SOIL_MOISUTRE_SENS_GND 15
#define SOIL_MOISTURE_SENS_DIN 5 // ADC1_CH4

const char *MQTT_TOPIC_MOISTURE = "home/outside/garden/moisture";
const char *MQTT_MANAGEMENT_TOPIC = "manage/garden";

void upon_wake();