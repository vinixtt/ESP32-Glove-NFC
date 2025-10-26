#include <Wire.h>
#include "config.h"
#include "ble_handler.h"
#include "nfc_handler.h"
#include "motor_handler.h"

// Global objects
BLEHandler ble;
NFCHandler nfc(SDA_PIN, SCL_PIN);
MotorHandler motor(MOTOR_PIN);

void setup() {
    delay(INITIAL_DELAY);
    
    // Initialize BLE
    ble.begin(DEVICE_NAME, SERVICE_UUID, CHARACTERISTIC_UUID);
    
    // Initialize motor
    motor.initialize();
    
    // Initialize I2C
    Wire.begin(SDA_PIN, SCL_PIN);
    Wire.setClock(I2C_CLOCK_SPEED);
    
    // Initialize NFC
    if (!nfc.initialize()) {
        // NFC initialization failed - can add LED or other indication
    }
}

void loop() {
    // BLE connection debug (optional)
    static bool previousStatus = false;
    if (ble.isConnected() != previousStatus) {
        delay(100);
        previousStatus = ble.isConnected();
    }
    
    // Read UID and content
    String uid = nfc.readUID();
    String content = nfc.readContent();
    
    if (content != "" && uid != "") {
        delay(TAG_READ_DELAY);
        motor.vibrate(MOTOR_VIBRATION_MS);
        ble.sendMessage("Content: " + content);
    }
    
    delay(LOOP_DELAY_MS);
}