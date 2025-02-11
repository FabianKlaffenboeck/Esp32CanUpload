//
// Created by FabianKlaffenboeck on 05/09/2024.
//

#include "UpdateHandler.h"
#include <Update.h>

void UpdateHandler::init() {
}

bool UpdateHandler::start(uint16_t expectedBytes) {
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
        log_e("Update Begin Error: %s\n", Update.errorString());
        return false;
    }
    return true;
}

bool UpdateHandler::addByte(uint8_t data, bool lastByte = false) {
    if (Update.write(&data, 1) != 1) {
        log_e("Write Error: %s\n", Update.errorString());
        Update.abort();
        return false;
    }

    _recivedBytes++;

    return true;
}

bool UpdateHandler::finish() {
    if (!Update.end(true)) {
        log_e("Update Failed: %s\n", Update.errorString());
        Update.abort();
        return false;
    }

    log_e("Update Success! Rebooting...");
    delay(1000);
    ESP.restart();

    return true;
}
