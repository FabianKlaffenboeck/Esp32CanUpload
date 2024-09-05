//
// Created by FabianKlaffenboeck on 05/09/2024.
//

#include <Update.h>
#include "UpdateHandler.h"

void UpdateHandler::init() {
    Update.begin(UPDATE_SIZE_UNKNOWN);
}

void UpdateHandler::setExpectedBytes(uint32_t expectedBytes) {
    _expectedBytes = expectedBytes;

    _fullBuffersCnt = _expectedBytes / BUFFER_SIZE;
    _remainingBits = _expectedBytes - (_fullBuffersCnt * BUFFER_SIZE);
}

bool UpdateHandler::addByte(uint8_t data) {

    _buff[_bufferPointer] = data;

    uint16_t writtenBytes = _bufferPointer;
    _bufferPointer++;

    bool bufferIsFull = ((BUFFER_SIZE >= writtenBytes) && (_fullBuffersCnt > 0));
    bool writeRemainingBytes = ((_bufferPointer == _remainingBits) && (_fullBuffersCnt == 0));

    if (bufferIsFull || writeRemainingBytes) {
        if (_fullBuffersCnt > 0) { _fullBuffersCnt--; }

        uint16_t writtenCount = Update.write(_buff, writtenBytes);

        if (writtenCount != writtenBytes) {
            log_e("Error while writing Bytes");
            return false;
        }

        _bufferPointer = 0;
    }

    return true;
}

bool UpdateHandler::finish(bool restart) {

    if (_expectedBytes != _actualBytes) {
        return false;
    }

    if (!Update.end()) {
        log_e("Error while Updating");
    }

    if (restart) {
        delay(10000);
        ESP.restart();
    }

    return true;
}
