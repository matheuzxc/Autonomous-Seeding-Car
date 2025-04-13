#include "remote_control.hpp"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

static const char* TAG = "REMOTE CONTROL";


RemoteControl::RemoteControl(Motor& _MotorA, Motor& _MotorB): MotorA(_MotorA),MotorB(_MotorB){}



void RemoteControl::RemoteUpdate(){

    if(SerialBT.available()){
        msgBluetooth = SerialBT.readStringUntil('\n');
        msgBluetooth.trim();

        if(msgBluetooth == "F"){
            RemoteControl::front();
            delay(50);
        }else if (msgBluetooth == "B"){
            RemoteControl::back();
            delay(50);
        }else if (msgBluetooth == "L"){
            RemoteControl::left();
            delay(50);
        }else if (msgBluetooth == "R"){
            RemoteControl::right();
            delay(50);
        }else{
            Serial.println("Mensagem não reconhecida:" + msgBluetooth);
        }
    }
}

// void RemoteControl::RemoteUpdateFromDabble(){
//     Dabble.processInput();  // Atualiza os dados recebidos do app

//     int x = GamePad.getx_axis();
//     int y = GamePad.gety_axis();

//     // Lógica de movimentação
//     if (y > 10) {
//         RemoteControl::front();
//     } else if (y < -10) {
//         RemoteControl::back();
//     } else if (x > 10) {
//         RemoteControl::right();
//     } else if (x < -10) {
//         RemoteControl::left();
//     } else {
//         MotorA.stop();
//         MotorB.stop();
//     }
// }


void RemoteControl::Begin(){
    
    bool sucesso = SerialBT.begin("Autonomous Car Remote");
    //Dabble.begin("Autonomous Car Remote");
     if (sucesso) {
         Serial.println("Bluetooth iniciado com sucesso, conecte-se.");
        
     } else {
         Serial.println("Falha ao iniciar o Bluetooth!");
     }
}

void RemoteControl::front(){
    MotorA.forward();
    MotorB.forward();
    Serial.println("Ir para frente.");
}
void RemoteControl::back(){
    MotorA.forward();
    MotorB.forward();
    Serial.println("Ir para trás.");
}
void RemoteControl::left(){
    MotorA.backward();
    MotorB.forward();
    Serial.println("Ir para esquerda");
}
void RemoteControl::right(){
    MotorA.forward();
    MotorB.backward();
    Serial.println("Ir para direita");
}
