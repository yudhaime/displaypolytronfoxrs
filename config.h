#ifndef CONFIG_H
#define CONFIG_H

#include "driver/twai.h"
#include "driver/gpio.h"

// =============================================
// USER CONFIGURATION - EDIT THESE VALUES ONLY
// =============================================

// === DISPLAY SETTINGS ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SDA_PIN GPIO_NUM_16
#define SCL_PIN GPIO_NUM_17
#define OLED_ADDRESS 0x3C

// === BUTTON SETTINGS ===
#define BUTTON_PIN GPIO_NUM_25
#define DEBOUNCE_DELAY 50

// === CAN BUS SETTINGS ===
#define CAN_TX_PIN GPIO_NUM_21
#define CAN_RX_PIN GPIO_NUM_22
#define CAN_BAUDRATE 250000  // 250kbps
#define CAN_MODE TWAI_MODE_LISTEN_ONLY

// === CAN MESSAGE IDs ===
#define ID_CTRL_MOTOR   0x0A010810UL  // Controller & Motor temperature
#define ID_BATT_5S      0x0E6C0D09UL  // Battery 5-sensor temperature  
#define ID_BATT_SINGLE  0x0A010A10UL  // Battery single temperature

// === TEMPERATURE SETTINGS ===
#define DEFAULT_TEMP 25    // Default temperature when no data
#define DATA_TIMEOUT 10000 // 10 seconds timeout for stale data

// === TEMPERATURE THRESHOLDS ===
// ECU Thresholds
#define ECU_NORMAL_MAX 45
#define ECU_WARM_MAX   55
#define ECU_HIGH_MAX   65

// Motor Thresholds  
#define MOTOR_NORMAL_MAX 50
#define MOTOR_WARM_MAX   60
#define MOTOR_HIGH_MAX   70

// Battery Thresholds
#define BATT_NORMAL_MAX 35
#define BATT_WARM_MAX   40
#define BATT_HIGH_MAX   45

// =============================================
// END USER CONFIGURATION
// =============================================

#endif