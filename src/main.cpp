#include <Arduino.h>
#include "CanDriver/CanDriver.h"


void setup() {
    Serial.begin(115200);
    CanInit(GPIO_NUM_4, GPIO_NUM_5, 500);
}

void loop() {
    CanHandlerLoop();
    Serial.println("Hallo");
}