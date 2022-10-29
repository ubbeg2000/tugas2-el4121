#include "motor.h"

float motor(float input, float prev_input, float prev_output)
{
    float res = 0;

    res = ((input + prev_input) * K * TS - prev_output * (TS - 2 * TC)) / (2 * TC + TS);

    return res;
}