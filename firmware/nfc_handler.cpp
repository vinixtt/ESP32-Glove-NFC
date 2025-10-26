#include "nfc_handler.h"
#include "config.h"

NFCHandler::NFCHandler(uint8_t sda, uint8_t scl) : nfc(sda, scl) {}

bool NFCHandler::initialize() {
    nfc.begin();
    uint32_t version = nfc.getFirmwareVersion();
    
    if (!version) {
        return false;
    }
    
    nfc.SAMConfig();
    return true;
}

String NFCHandler::removeAccents(String text) {
    text.replace("ç", "c"); text.replace("Ç", "C");
    text.replace("ã", "a"); text.replace("á", "a");
    text.replace("à", "a"); text.replace("â", "a");
    text.replace("Ã", "A"); text.replace("Á", "A");
    text.replace("À", "A"); text.replace("Â", "A");
    text.replace("é", "e"); text.replace("ê", "e");
    text.replace("É", "E"); text.replace("Ê", "E");
    text.replace("í", "i"); text.replace("Í", "I");
    text.replace("ó", "o"); text.replace("ô", "o");
    text.replace("õ", "o"); text.replace("Ó", "O");
    text.replace("Ô", "O"); text.replace("Õ", "O");
    text.replace("ú", "u"); text.replace("Ú", "U");
    text.replace("ü", "u"); text.replace("Ü", "U");
    return text;
}

String NFCHandler::processBlock(uint8_t* data) {
    String piece = "";
    for (uint8_t i = 0; i < 16; i++) {
        if (data[i] >= 32 && data[i] <= 126) {
            piece += (char)data[i];
        }
    }
    return piece;
}

bool NFCHandler::isTextExtension(String currentContent, String newPiece) {
    for (int i = 1; i <= min(currentContent.length(), newPiece.length()); i++) {
        String currentEnd = currentContent.substring(currentContent.length() - i);
        String newStart = newPiece.substring(0, i);
        
        if (currentEnd == newStart) {
            return true;
        }
    }
    return false;
}

String NFCHandler::readUID() {
    uint8_t uid[7] = {0};
    uint8_t uidLength;
    
    bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, NFC_QUICK_CHECK);
    
    if (!success) {
        return "";
    }
    
    String uidString = "";
    for (uint8_t i = 0; i < uidLength; i++) {
        if (uid[i] < 0x10) {
            uidString += "0";
        }
        uidString += String(uid[i], HEX);
    }
    uidString.toUpperCase();
    
    return uidString;
}

String NFCHandler::readContent() {
    uint8_t uid[7] = {0};
    uint8_t uidLength;
    
    uint8_t success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, NFC_TIMEOUT);
    if (!success) return "";

    String finalContent = "";

    for(uint8_t block = FIRST_BLOCK; block <= LAST_BLOCK; block++) {
        success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, block, 0, (uint8_t*)KEY_A);
        if (!success) continue;

        uint8_t data[16];
        success = nfc.mifareclassic_ReadDataBlock(block, data);
        if (success) {
            String currentPiece = processBlock(data);
            
            if (currentPiece.length() > 0) {
                if (finalContent.length() == 0) {
                    finalContent = currentPiece;
                } else {
                    bool isExtension = isTextExtension(finalContent, currentPiece);
                    
                    if (isExtension) {
                        for (int i = 1; i <= min(finalContent.length(), currentPiece.length()); i++) {
                            String currentEnd = finalContent.substring(finalContent.length() - i);
                            String newStart = currentPiece.substring(0, i);
                            
                            if (currentEnd == newStart) {
                                finalContent += currentPiece.substring(i);
                                break;
                            }
                        }
                    } else if (!finalContent.endsWith(currentPiece) && !currentPiece.endsWith(finalContent)) {
                        finalContent += currentPiece;
                    }
                }
            }
            
            // Check for null terminator
            for (uint8_t j = 0; j < 16; j++) {
                if (data[j] == 0) {
                    finalContent.trim();
                    if (finalContent.startsWith("Ten")) {
                        finalContent = finalContent.substring(3);
                    }
                    return removeAccents(finalContent);
                }
            }
        }
    }

    if (finalContent.startsWith("Ten")) {
        finalContent = finalContent.substring(3);
    }
    finalContent.trim();
    return removeAccents(finalContent);
}