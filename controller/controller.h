#ifndef TS
#define TS 0.01
#endif

typedef struct PIDParams
{
    float kp;
    float ki;
    float kd;
    float integral;
    float derivative;
    float error;
    float prev_error;
} PIDParams;

float controller(PIDParams *pid_params);