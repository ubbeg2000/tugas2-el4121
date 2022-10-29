#include <stdlib.h>
#include <stdio.h>
#include "../motor/motor.h"
#include "../controller/controller.h"

int main()
{
    float setpoint = 0, prev_setpoint = 0, controller_output = 0, prev_controller_output = 0;
    float output = 0, prev_output = 0, position = 0;

    float kp = 50;
    float ki = 6 * kp;

    PIDParams pid_params = {
        .kp = kp,
        .ki = ki,
        .kd = 0,
        .derivative = 0,
        .integral = 0,
        .error = 0,
        .prev_error = 0,
    };

    FILE *file = fopen("controller_simulation.csv", "w");

    fprintf(file, "time,setpoint(speed),setpoint(acceleration),speed,acceleration\n");

    for (int i = 0; i < 1000; i++)
    {

        prev_output = output;
        output = motor(controller_output, prev_controller_output, prev_output);
        position += output * TS;

        prev_setpoint = setpoint;
        if (i < 100)
        {
            setpoint = (float)i / 100;
        }
        else if (i > 900)
        {
            setpoint = (float)(1000 - i) / 100;
        }
        else
        {
            setpoint = 1;
        }

        pid_params.prev_error = pid_params.error;
        pid_params.error = setpoint - output;

        prev_controller_output = controller_output;

        controller_output = controller(&pid_params);

        fprintf(file, "%.8f,%.8f,%.8f,%.8f,%.8f\n", TS * i, setpoint, (setpoint - prev_setpoint) / TS, output, (output - prev_output) / TS);
    }

    fclose(file);

    return 0;
}