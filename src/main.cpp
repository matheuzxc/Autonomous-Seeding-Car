#include <Arduino.h>
#include "control_motor.hpp"
#include "remote_control.hpp"
#include <esp_log.h>


Motor motorB(18, 19, 5, 0);  
Motor motorA(21, 22, 4, 1);   
RemoteControl remote(motorA, motorB);

void setup() {   
    Serial.begin(115200);
    delay(1000);
    remote.Begin();
}

void loop() {
    motorA.begin();
    motorB.begin();
    remote.RemoteUpdate();
}