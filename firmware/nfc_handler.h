#ifndef NFC_HANDLER_H
#define NFC_HANDLER_H

#include <Adafruit_PN532.h>
#include <Arduino.h>

class NFCHandler {
private:
    Adafruit_PN532 nfc;
    
    String removeAccents(String text);
    String processBlock(uint8_t* data);
    bool isTextExtension(String currentContent, String newPiece);

public:
    NFCHandler(uint8_t sda, uint8_t scl);
    bool initialize();
    String readUID();
    String readContent();
};

#endif