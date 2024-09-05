//
// Created by FabianKlaffenboeck on 05/09/2024.
//

#include "UpdateHandler.h"

void UpdateHandler::init() {

}

void UpdateHandler::setExpectedBytes() {

}

bool UpdateHandler::addByte(uint8_t data) {
    return false;
}

bool UpdateHandler::finish(bool restart) {

    if (_expectedBytes != _actualBytes) {
        return false;
    }

    return true;
}
