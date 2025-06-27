#ifndef BUSSOLA_HPP
#define BUSSOLA_HPP

#include <QMC5883LCompass.h>

class Bussola {
private:
    QMC5883LCompass compass;
    float offsetX, offsetY, scaleX, scaleY, declinacao;
    float azimuteFiltrado;
    float alpha;

public:

    Bussola(float offsetX, float offsetY, float scaleX, float scaleY, float declinacao, float alpha = 0.1);

    void begin(int sda, int scl);
    
    float lerAzimuteFiltrado();
};

#endif
