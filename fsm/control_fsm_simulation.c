#include <stdlib.h>
#include <stdio.h>
#include "control_fsm.h"

int main()
{
    FILE *f = fopen("control_fsm_simulation.csv", "w");
    int state = DOOR_OPEN, prev_state = DOOR_OPEN, input_open = 1, input_close = 0, cnt = 0;
    float ts = 0.01, output = 0, position = DOOR_LEN, speed = 0;

    fprintf(f, "input_open,input_close,output,position\n");

    for (int i = 0; i < 1000; i++)
    {
        input_open = (i < 220 && i > 170) || i < 50 ? 1 : 0;

        control_fsm(&state, &cnt, input_open, input_close, speed, position, &output);

        speed = output;
        position += output * TS;

        fprintf(f, "%d,%d,%.8f,%.8f\n", input_open, input_close, output, position);
    }

    fclose(f);

    return 0;
}