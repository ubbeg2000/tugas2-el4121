#include "controller.h"

float controller(PIDParams *pid_params)
{
    pid_params->integral += TS * (pid_params->error + pid_params->prev_error) / 2;
    pid_params->derivative = (pid_params->error - pid_params->prev_error) / TS;

    return pid_params->kp * pid_params->error + pid_params->ki * pid_params->integral + pid_params->kd + pid_params->error;
}