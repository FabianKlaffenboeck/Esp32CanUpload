//
// Created by FabianKlaffenboeck on 05/09/2024.
//

#ifndef ESP32CANUPLOAD_UPDATEHANDLER_H
#define ESP32CANUPLOAD_UPDATEHANDLER_H

#include <cstdint>

#define BUFFER_SIZE 4096

class UpdateHandler {
public:
    void init();

    void setExpectedBytes(uint32_t expectedBytes);

    bool addByte(uint8_t data);

    bool finish(bool restart);

private:
    uint32_t _expectedBytes = 0;
    uint32_t _fullBuffersCnt = 0;
    uint32_t _remainingBits = 0;


    uint32_t _actualBytes = 0;
    uint16_t _bufferPointer = 0;
    uint8_t _buff[BUFFER_SIZE] = {0};

};


#endif //ESP32CANUPLOAD_UPDATEHANDLER_H
