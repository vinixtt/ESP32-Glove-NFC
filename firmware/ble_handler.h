#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>

class BLEHandler {
private:
    BLEServer* pServer;
    BLECharacteristic* pCharacteristic;
    bool deviceConnected;
    bool oldDeviceConnected;
    
    class ServerCallbacks: public BLEServerCallbacks {
    public:
        BLEHandler* handler;
        
        void onConnect(BLEServer* pServer) {
            handler->setConnected(true);
        }
        
        void onDisconnect(BLEServer* pServer) {
            handler->setConnected(false);
        }
    };

public:
    BLEHandler();
    void begin(const char* deviceName, const char* serviceUUID, const char* charUUID);
    void sendMessage(String message);
    bool isConnected();
    void setConnected(bool status);
};

#endif