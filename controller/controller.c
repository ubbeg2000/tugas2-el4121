#include "controller.h"

// float controller(float setpoint, float prev_setpoint, float prev_output)
// {
//     float res = 0;

//     res = (((TS * TD + 2) * KP * setpoint) + ((TSC * TD - 2) * KP * prev_setpoint) + (2 * prev_output)) / 2;

//     return res;
// }

float controller(PIDParams *pid_params)
{
    pid_params->integral += TS * (pid_params->error + pid_params->prev_error) / 2;
    pid_params->derivative = (pid_params->error - pid_params->prev_error) / TS;

    return pid_params->kp * pid_params->error + pid_params->ki * pid_params->integral + pid_params->kd + pid_params->error;
}