#include <Arduino.h>
#include "control_motor.hpp"

Motor motorEsquerdo(18, 19, 5, 0);  // Exemplo de pinos para o motor esquerdo
Motor motorDireito(21, 22, 4, 1);   // Exemplo de pinos para o motor direito

void setup() {
    motorEsquerdo.begin();
    motorDireito.begin();
    motorEsquerdo.setSpeed(255); 
    motorDireito.setSpeed(255);
}

void loop() {
    motorEsquerdo.forward(); 
    motorDireito.backward();   
    delay(1000);              
    
    motorDireito.setSpeed(0);
    motorEsquerdo.setSpeed(0);
    delay(1000);   

    motorEsquerdo.backward(); 
     motorDireito.forward(); 
     delay(1000);             
}