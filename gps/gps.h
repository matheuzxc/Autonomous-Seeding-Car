// gps.h
#ifndef GPS_H
#define GPS_H

void gps_init(void);
void gps_start_task(void);

extern float gps_latitude;
extern float gps_longitude;

#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 100 
// Define the tick rate (adjust as per your FreeRTOS configuration)
#endif

#endif // GPS_H