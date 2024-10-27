//
// Created by FabianKlaffenboeck on 05/09/2024.
//

#ifndef ESP32CANUPLOAD_UPDATEHANDLER_H
#define ESP32CANUPLOAD_UPDATEHANDLER_H

#include <cstdint>

#define BUFFER_SIZE 1024


class UpdateHandler {
public:
    void init();

    bool start(uint16_t expectedBytes);

    bool addByte(uint8_t data, bool lastByte);

    bool finish();

private:
    uint16_t _expectedBytes = 0;
    uint16_t _writtenBytes = 0;
    uint8_t _update_buffer[BUFFER_SIZE] = {};
    uint16_t _bufferIndex = 0;
};


#endif //ESP32CANUPLOAD_UPDATEHANDLER_H
