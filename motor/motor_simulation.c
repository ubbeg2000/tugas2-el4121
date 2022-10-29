#include <stdlib.h>
#include <stdio.h>
#include "motor.h"

int main()
{
    float setpoint = 0, output = 0, prev_setpoint = 0, prev_output = 0, position = 0;
    FILE *file = fopen("motor_simulation.csv", "w");

    fprintf(file, "time,setpoint,output,position\n");

    for (int i = 0; i < 1000; i++)
    {
        setpoint = 1;
        output = motor(setpoint, prev_setpoint, prev_output);
        position += output * TS;

        fprintf(file, "%.8f,%.8f,%.8f,%.8f\n", TS * i, setpoint, output, position);

        prev_setpoint = setpoint;
        prev_output = output;
    }

    fclose(file);

    return 0;
}