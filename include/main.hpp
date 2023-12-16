#include <Arduino.h>

#include "credentials.h"
#include "MQTTTasks.hpp"
#include "SensorTasks.hpp"


const char *MQTT_TOPIC_MOISTURE = "home/outside/garden/moisture";
const char *MQTT_MANAGEMENT_TOPIC = "manage/garden";

void upon_wake();