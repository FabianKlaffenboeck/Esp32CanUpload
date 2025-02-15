#include <Arduino.h>
#include <UpdateHandler/UpdateHandler.h>

#include "CanDriver/CanDriver.h"


UpdateHandler update_handler;

void setup() {
    CanInit(GPIO_NUM_5, GPIO_NUM_4, 500);

    update_handler.init();
    update_handler.set_TX_Hook(CanWrite);

    CanRegisterCallback([](CanMsg msg) {
        update_handler.rxHandler(msg);
    });
}

void loop() {
    CanHandlerLoop();
}
