#include <Arduino.h>
#include "CanDriver/CanDriver.h"


void setup() {
    CanInit(GPIO_NUM_4, GPIO_NUM_5, 500);
}

void loop() {
    CanHandlerLoop();
}