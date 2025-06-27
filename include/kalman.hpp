#pragma once

class KalmanFilter {
private:
    float estimate;
    float error_estimate;
    float error_measure;
    float kalman_gain;

public:
    KalmanFilter(float init_estimate = 0, float est_error = 1, float meas_error = 1)
        : estimate(init_estimate), error_estimate(est_error), error_measure(meas_error) {}

    float update(float measurement) {
        // Ganho de Kalman
        kalman_gain = error_estimate / (error_estimate + error_measure);
        // Atualiza estimativa
        estimate = estimate + kalman_gain * (measurement - estimate);
        // Atualiza erro de estimativa
        error_estimate = (1 - kalman_gain) * error_estimate;

        return estimate;
    }

    float getEstimate() const {
        return estimate;
    }
};
