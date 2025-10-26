#include "ble_handler.h"

BLEHandler::BLEHandler() {
    pServer = nullptr;
    pCharacteristic = nullptr;
    deviceConnected = false;
    oldDeviceConnected = false;
}

void BLEHandler::begin(const char* deviceName, const char* serviceUUID, const char* charUUID) {
    BLEDevice::init(deviceName);
    pServer = BLEDevice::createServer();
    
    ServerCallbacks* callbacks = new ServerCallbacks();
    callbacks->handler = this;
    pServer->setCallbacks(callbacks);
    
    BLEService *pService = pServer->createService(serviceUUID);
    pCharacteristic = pService->createCharacteristic(
                        charUUID,
                        BLECharacteristic::PROPERTY_READ |
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
    pService->start();
    
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(serviceUUID);
    pAdvertising->start();
}

void BLEHandler::sendMessage(String message) {
    if (deviceConnected && pCharacteristic != nullptr) {
        pCharacteristic->setValue(message.c_str());
        pCharacteristic->notify();
    }
}

bool BLEHandler::isConnected() {
    return deviceConnected;
}

void BLEHandler::setConnected(bool status) {
    deviceConnected = status;
}
