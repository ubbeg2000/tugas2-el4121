#include <stdlib.h>
#include <stdio.h>
#include "fsm/control_fsm.h"
#include "controller/controller.h"
#include "motor/motor.h"

int main()
{
    FILE *f = fopen("hil_simulation.csv", "w");

    // FSM VARIABLES
    int state = DOOR_OPEN, input_open = 1, input_close = 0, cnt = 0;
    float setpoint = 0, position = DOOR_LEN;

    // PID VARIABLES
    float kp = 50;
    float ki = 6 * kp;
    float control_signal = 0, prev_control_signal = 0;
    PIDParams pid_params = {
        .kp = kp,
        .ki = ki,
        .kd = 0,
        .derivative = 0,
        .integral = 0,
        .error = 0,
        .prev_error = 0,
    };

    // MOTOR VARIABLES
    float speed = 0, prev_speed = 0;

    fprintf(f, "input_open,input_close,setpoint,speed,position\n");

    for (int i = 0; i < 1000; i++)
    {
        input_open = (i < 220 && i > 170) || i < 50 ? 1 : 0;

        control_fsm(&state, &cnt, input_open, input_close, speed, position, &setpoint);

        pid_params.prev_error = pid_params.error;
        pid_params.error = setpoint - speed;

        prev_control_signal = control_signal;
        control_signal = controller(&pid_params);

        prev_speed = speed;
        speed = motor(control_signal, prev_control_signal, prev_speed);
        position += speed * TS;

        fprintf(f, "%d,%d,%.8f,%.8f,%.8f\n", input_open, input_close, setpoint, speed, position);
    }

    fclose(f);

    return 0;
}