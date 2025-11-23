#include <Arduino.h>
#include "display.h"
#include "canbus.h"
#include "config.h"

int currentPage = 1;
bool lastButton = HIGH;
unsigned long lastDebounce = 0;

void setup() {
    Serial.begin(115200);
    while(!Serial) delay(10);

    initDisplay();

    if(!initCAN()){
        Serial.println("Gagal init CAN!");
        while(1) delay(1000);
    }

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.println("Sistem mulai... Mode Listen Only");
}

void loop() {
    updateCAN();

    // Tombol ganti halaman (1-4)
    bool btn = digitalRead(BUTTON_PIN);
    if(btn==LOW && lastButton==HIGH && (millis()-lastDebounce>DEBOUNCE_DELAY)){
        currentPage++;
        if(currentPage>4) currentPage=1;
        lastDebounce = millis();
    }
    lastButton = btn;

    updateDisplay(currentPage);
    delay(100);
}