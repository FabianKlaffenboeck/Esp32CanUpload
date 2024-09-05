//
// Created by FabianKlaffenboeck on 05/09/2024.
//

#ifndef ESP32CANUPLOAD_TMP_H
#define ESP32CANUPLOAD_TMP_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>

const char *ssid = "khushal";
const char *password = "123456789";
const char *serverAddress = "192.168.29.81";
const int serverPort = 3000; // Change to your server's port
const String firmwareFileName = "sketch.bin"; // The name of the firmware file to be downloaded and flashed


void tmp(){
    Serial.begin(115200);
    delay(100);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Specify the URL for the firmware file you want to download
    String url = "http://" + String(serverAddress) + ":" + String(serverPort) + "/download";

    HTTPClient http;
    http.begin(url);

    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        Serial.println("Downloading firmware...");

        if (Update.begin(UPDATE_SIZE_UNKNOWN)) {

            int len = http.getSize();
            uint8_t buff[4096] = {0};

            // get tcp stream
            WiFiClient *stream = http.getStreamPtr();

            // read all data from server

            // read data as long http is connected -1 is for then no length header is set > 0 is for when header is set
            while (http.connected() && (len > 0 || len == -1)) {
                // get available data size

                // how much is actually available
                size_t size = stream->available();
                if (size) {

                    // if enough bytes are available for one full buffer, user the whole buffer, else user only as much as available
                    int act_size;
                    if (size > sizeof(buff)) {
                        act_size = sizeof(buff);
                    } else {
                        act_size = size;
                    }

                    // read available bytes into buffer
                    int c = stream->readBytes(buff, act_size);

                    // write it to Serial
                    int writtenCount = Update.write(buff, c);
                    Serial.println((String) "written:" + writtenCount + " act_size:" + act_size);

                    if (writtenCount != act_size) {
                        Serial.println("Error updating firmware here");
                        break;
                    }
                    if (len > 0) {
                        len -= c;
                    }
                }
                delay(1);
            }

            if (Update.end()) {
                Serial.println("Firmware update successful!");
                delay(10000);
                ESP.restart();
            } else {
                Serial.println("Error updating firmware");
            }
        } else {
            Serial.println("Error starting update");
        }
    } else {
        Serial.println("Firmware download failed");
    }

    http.end();}

#endif //ESP32CANUPLOAD_TMP_H
