// ==================== config.h ====================
#ifndef CONFIG_H
#define CONFIG_H

// BLE service UUIDs
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// BLE device name
#define DEVICE_NAME "NFC-Reader"

// Pin definitions
#define MOTOR_PIN 14
#define SDA_PIN 26
#define SCL_PIN 27

// Timing configurations
#define INITIAL_DELAY 2000
#define I2C_CLOCK_SPEED 100000  // 100kHz
#define NFC_TIMEOUT 500
#define NFC_QUICK_CHECK 50
#define MOTOR_VIBRATION_MS 500
#define LOOP_DELAY_MS 300
#define TAG_READ_DELAY 1000

// NFC reading configuration
#define FIRST_BLOCK 4
#define LAST_BLOCK 8

// Default MIFARE key
const uint8_t KEY_A[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

#endif