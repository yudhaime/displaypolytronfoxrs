#include "canbus.h"
#include "Arduino.h"
#include "driver/twai.h"
#include "config.h"

// Variabel global untuk suhu
int tempCtrl = DEFAULT_TEMP;
int tempMotor = DEFAULT_TEMP;
int tempBatt = DEFAULT_TEMP;

// Variabel untuk smart default system
int lastValidTempCtrl = DEFAULT_TEMP;
int lastValidTempMotor = DEFAULT_TEMP;
int lastValidTempBatt = DEFAULT_TEMP;
unsigned long lastCtrlUpdate = 0;
unsigned long lastMotorUpdate = 0;
unsigned long lastBattUpdate = 0;
int ctrlDataCount = 0;
int motorDataCount = 0;
int battDataCount = 0;

bool initCAN() {
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX_PIN, CAN_RX_PIN, CAN_MODE);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_250KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) return false;
    if (twai_start() != ESP_OK) return false;

    Serial.println("CAN LISTEN ONLY mode siap 250kbps");
    return true;
}

void updateCAN() {
    twai_message_t message;
    
    if(twai_receive(&message, pdMS_TO_TICKS(50)) == ESP_OK){
        uint32_t id = message.identifier;
        uint8_t dlc = message.data_length_code;

        // Controller & Motor Temperature
        if(id == ID_CTRL_MOTOR && dlc >= 6){
            tempCtrl = message.data[4];
            tempMotor = message.data[5];
            
            lastValidTempCtrl = tempCtrl;
            lastValidTempMotor = tempMotor;
            lastCtrlUpdate = millis();
            lastMotorUpdate = millis();
            ctrlDataCount++;
            motorDataCount++;
        }
        // Battery 5-Sensor Temperature
        else if(id == ID_BATT_5S && dlc >= 5){
            int maxTemp = -100;
            
            for(int i = 0; i < 5; ++i){
                if(message.data[i] > maxTemp) 
                    maxTemp = message.data[i];
            }
            
            if(maxTemp != -100 && maxTemp > tempBatt){
                tempBatt = maxTemp;
                lastValidTempBatt = tempBatt;
                lastBattUpdate = millis();
                battDataCount++;
            }
        }
        // Battery Single Temperature
        else if(id == ID_BATT_SINGLE && dlc >= 6){
            int battTemp = message.data[5];
            
            if(battTemp > tempBatt){
                tempBatt = battTemp;
                lastValidTempBatt = tempBatt;
                lastBattUpdate = millis();
                battDataCount++;
            }
        }
    }
    
    // Smart default values system
    if(ctrlDataCount == 0) {
        tempCtrl = DEFAULT_TEMP;
    } else if(millis() - lastCtrlUpdate > DATA_TIMEOUT) {
        tempCtrl = lastValidTempCtrl;
    }
    
    if(motorDataCount == 0) {
        tempMotor = DEFAULT_TEMP;
    } else if(millis() - lastMotorUpdate > DATA_TIMEOUT) {
        tempMotor = lastValidTempMotor;
    }
    
    if(battDataCount == 0) {
        tempBatt = DEFAULT_TEMP;
    } else if(millis() - lastBattUpdate > DATA_TIMEOUT) {
        tempBatt = lastValidTempBatt;
    }
}
