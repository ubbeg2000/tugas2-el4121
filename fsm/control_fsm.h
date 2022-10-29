#define DOOR_OPEN 60
#define DOOR_CLOSE 61
#define DOOR_OPENING 62
#define DOOR_CLOSING 63
#define ACC_UP_0 64
#define ACC_DOWN_0 65
#define ACC_UP_MAX 66
#define ACC_DOWN_MIN 67

#define OPEN_DURATION 300

#ifndef TS
#define TS 0.01
#endif

#define MAX_SPEED 0.5
#define MIN_SPEED (-MAX_SPEED)
#define DOOR_LEN 1.0

#define ACC_SAMPLE 50
#define OPEN_TH (DOOR_LEN - ACC_SAMPLE * MAX_SPEED * TS / 2)
#define CLOSE_TH (ACC_SAMPLE * MAX_SPEED * TS / 2)
#define ACC_RATE (MAX_SPEED / ACC_SAMPLE)

void control_fsm(int *state, int *cnt, int input_open, int input_close, float speed, float position, float *output);