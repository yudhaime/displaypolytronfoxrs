#include "display.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "canbus.h"
#include "config.h"

TwoWire myWire = TwoWire(0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &myWire, -1);

// Fungsi untuk menentukan status temperature dengan 4 level
const char* getTempStatus(int temp, int type) {
    if(type == 0) { // ECU
        if(temp <= ECU_NORMAL_MAX) return "Normal";
        else if(temp <= ECU_WARM_MAX) return "Warm";
        else if(temp <= ECU_HIGH_MAX) return "High";
        else return "Over";
    }
    else if(type == 1) { // MOTOR
        if(temp <= MOTOR_NORMAL_MAX) return "Normal";
        else if(temp <= MOTOR_WARM_MAX) return "Warm";
        else if(temp <= MOTOR_HIGH_MAX) return "High";
        else return "Over";
    }
    else { // BATTERY
        if(temp <= BATT_NORMAL_MAX) return "Normal";
        else if(temp <= BATT_WARM_MAX) return "Warm";
        else if(temp <= BATT_HIGH_MAX) return "High";
        else return "Over";
    }
}

void initDisplay() {
    myWire.begin(SDA_PIN, SCL_PIN);
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)){
        Serial.println("SSD1306 gagal init");
        for(;;);
    }
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Init...");
    display.display();
    Serial.println("Display siap");
}

void updateDisplay(int page){
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    if(page == 1){
        // PAGE 1: Overview semua temperature
        display.setTextSize(1);
        display.setCursor(0, 4);
        display.print("ECU");
        display.setCursor(43, 4);
        display.print("MOTOR");
        display.setCursor(86, 4);
        display.print("BATT");
        
        display.setTextSize(2);
        display.setCursor(0, 16);
        display.print(tempCtrl);
        display.setCursor(43, 16);
        display.print(tempMotor);
        display.setCursor(86, 16);
        display.print(tempBatt);
    }
    else if(page == 2){
        // PAGE 2: ECU detail
        display.setTextSize(2);
        display.setCursor(0, 2);
        display.println("ECU");
        display.setCursor(0, 18);
        display.printf("%d%c ", tempCtrl, 247);
        display.print(getTempStatus(tempCtrl, 0));
    }
    else if(page == 3){
        // PAGE 3: MOTOR detail
        display.setTextSize(2);
        display.setCursor(0, 2);
        display.println("MOTOR");
        display.setCursor(0, 18);
        display.printf("%d%c ", tempMotor, 247);
        display.print(getTempStatus(tempMotor, 1));
    }
    else if(page == 4){
        // PAGE 4: BATT detail
        display.setTextSize(2);
        display.setCursor(0, 2);
        display.println("BATTERY");
        display.setCursor(0, 18);
        display.printf("%d%c ", tempBatt, 247);
        display.print(getTempStatus(tempBatt, 2));
    }

    display.display();
}