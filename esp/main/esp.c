#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../../fsm/control_fsm.h"
#include "../../controller/controller.h"

#define GPIO_INPUT_PIN_SEL (1ULL << GPIO_NUM_19 | 1ULL << GPIO_NUM_18)

void control_task(void *pvParam)
{
    int input_close = 0, input_open = 0;
    int state = DOOR_CLOSE, cnt = 0;
    float speed = 0, position = 0, setpoint = 0;
    float control_signal = 0;

    float kp = 50;
    float ki = kp * 6;

    PIDParams pid_params = {
        .kp = kp,
        .ki = ki,
        .kd = 0,
        .derivative = 0,
        .integral = 0,
        .error = 0,
        .prev_error = 0,
    };

    TickType_t xDelay = TS * 1000 / portTICK_PERIOD_MS;

    for (;;)
    {
        TickType_t xLastWakeTime = xTaskGetTickCount();

        if (2 == scanf("%f;%f", &speed, &position))
        {

            input_open = gpio_get_level(GPIO_NUM_18);
            input_close = gpio_get_level(GPIO_NUM_19);

            control_fsm(&state, &cnt, input_open, input_close, speed, position, &setpoint);

            pid_params.prev_error = pid_params.error;
            pid_params.error = setpoint - speed;

            control_signal = controller(&pid_params);

            printf("%.8f;%.8f;%d;%d\r\n", control_signal, setpoint, input_open, input_close);
        }

        xTaskDelayUntil(&xLastWakeTime, xDelay);
        // vTaskDelay(100 / portTICK_PERIOD_MS);

        // vTaskDelay(TS * 1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpio_config(&io_conf);

    xTaskCreatePinnedToCore(control_task, "Control Task", 2048, NULL, 1, NULL, 0);
}