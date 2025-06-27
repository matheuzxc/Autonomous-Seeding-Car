#ifndef GPS_HPP
#define GPS_HPP

#include <Arduino.h>

void gps_init();
void gps_start_task();

float get_latitude();
float get_longitude();

#endif
