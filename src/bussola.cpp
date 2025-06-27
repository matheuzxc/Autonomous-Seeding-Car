#include "bussola.hpp"
#include <Wire.h>
#include <Arduino.h>
#include <math.h>

Bussola::Bussola(float offsetX, float offsetY, float scaleX, float scaleY, float declinacao, float alpha)
    : offsetX(offsetX), offsetY(offsetY), scaleX(scaleX), scaleY(scaleY),
      declinacao(declinacao), azimuteFiltrado(0), alpha(alpha) {}

void Bussola::begin(int sda, int scl) {
    Wire.begin(sda, scl);
    compass.init();
    Serial.println("Bússola iniciada.");
}

float Bussola::lerAzimuteFiltrado() {
    
    compass.read();

    float rawX = compass.getX();
    float rawY = compass.getY();

    float corrX = (rawX - offsetX) * scaleX;
    float corrY = (rawY - offsetY) * scaleY;

    float azimuteAtual = atan2(corrY, corrX) * 180.0 / PI;
    if (azimuteAtual < 0) azimuteAtual += 360;

    azimuteAtual += declinacao;
    if (azimuteAtual < 0) azimuteAtual += 360;
    if (azimuteAtual >= 360) azimuteAtual -= 360;

    float delta = azimuteAtual - azimuteFiltrado;
    if (delta > 180) delta -= 360;
    if (delta < -180) delta += 360;

    azimuteFiltrado += alpha * delta;
    if (azimuteFiltrado < 0) azimuteFiltrado += 360;
    if (azimuteFiltrado >= 360) azimuteFiltrado -= 360;
    Serial.print("Azimute filtrado: ");
    Serial.println(azimuteFiltrado);
    return azimuteFiltrado;
}
