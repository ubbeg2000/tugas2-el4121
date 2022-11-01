#include "control_fsm.h"

void control_fsm(int *state, int *cnt, int input_open, int input_close, float speed, float position, float *output)
{
    switch (*state)
    {
    case DOOR_CLOSE:
    {
        if (input_open == 1)
        {
            *state = ACC_UP_MAX;
            *output = 0;
        }
        else if (input_close == 1)
        {
            *state = DOOR_CLOSE;
            *output = 0;
        }
        break;
    }
    case DOOR_OPEN:
    {
        if (input_close == 1)
        {
            *state = ACC_DOWN_MIN;
            *output = 0;
        }
        else
        {
            if (*cnt >= 0)
            {
                *state = DOOR_OPEN;
                *cnt = *cnt - 1;
                *output = 0;
            }
            else if (input_open == 1)
            {
                *cnt = OPEN_DURATION;
                *state = DOOR_OPEN;
                *output = 0;
            }
            else
            {
                *state = ACC_DOWN_MIN;
                *output = 0;
            }
        }
        break;
    }
    case DOOR_OPENING:
    {
        if (position < OPEN_TH)
        {
            *state = DOOR_OPENING;
        }
        else
        {
            *state = ACC_DOWN_0;
        }
        break;
    }
    case DOOR_CLOSING:
    {
        if (input_open == 1)
        {
            *state = ACC_UP_MAX;
        }
        else
        {
            if (position > CLOSE_TH)
            {
                *state = DOOR_CLOSING;
                *output = MIN_SPEED;
            }
            else
            {
                *state = ACC_UP_0;
                *output = MIN_SPEED;
            }
        }
        break;
    }
    case ACC_UP_0:
    {
        if (speed < 0)
        {
            *state = ACC_UP_0;
            *output = *output + ACC_RATE;
        }
        else
        {
            *state = DOOR_CLOSE;
            *output = 0;
        }
        break;
    }
    case ACC_DOWN_0:
    {
        if (speed > 0)
        {
            *state = ACC_DOWN_0;
            *output = *output - ACC_RATE;
        }
        else
        {
            *cnt = OPEN_DURATION;
            *state = DOOR_OPEN;
            *output = 0;
        }
        break;
    }
    case ACC_UP_MAX:
    {
        if (speed <= MAX_SPEED)
        {
            *state = ACC_UP_MAX;
            *output = *output + ACC_RATE;
        }
        else
        {
            *state = DOOR_OPENING;
            *output = MAX_SPEED;
        }
        break;
    }
    case ACC_DOWN_MIN:
    {
        if (speed >= MIN_SPEED)
        {
            *state = ACC_DOWN_MIN;
            *output = *output - ACC_RATE;
        }
        else
        {
            *state = DOOR_CLOSING;
            *output = MIN_SPEED;
        }
        break;
    }
    default:
        break;
    }
}