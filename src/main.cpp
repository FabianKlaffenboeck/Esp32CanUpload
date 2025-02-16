#include <Arduino.h>

#include "../lib/CanDriver/CanDriver.h"
#include "../lib/UpdateHandler/UpdateHandler.h"

UpdateHandler update_handler;

void setup() {
    CanInit(GPIO_NUM_5, GPIO_NUM_4, 500);

    update_handler.init(CanWrite);

    CanRegisterCallback([](CanMsg msg) {
        update_handler.rxHandler(msg);
    });
}

void loop() {
    CanHandlerLoop();
}
