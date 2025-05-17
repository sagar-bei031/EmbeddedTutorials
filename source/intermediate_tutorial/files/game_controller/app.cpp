#include <stdio.h>

#include "usart.h"
#include "joystick.hpp"
#include "app.h"

Joystick joystick(&huart4);
uint32_t last_loop_tick = 0;
uint32_t last_rx_tick = 0;
uint32_t last_print_tick = 0;

void setup()
{
    joystick.init();
    printf("Joystick initialized\n");
    last_loop_tick = HAL_GetTick();
}

void loop()
{
    if (HAL_GetTick() - last_loop_tick < 10)
    return;

    last_loop_tick = HAL_GetTick();

    // Must call every 10ms or less.
    bool is_joystick_updated = joystick.update();

    if (!joystick.connected())
    {
        printf("Joystick not connected\n");
    }

    if (is_joystick_updated)
    {
        if (HAL_GetTick() - last_print_tick > 100)
        {
            last_print_tick = HAL_GetTick();
            joystick.print_data();
            // joystick.print_received_data();
        }
    }

    float lx, ly, rx, ry, lt, rt;
    lx = joystick.lx();
    ly = joystick.ly();
    rx = joystick.rx();
    ry = joystick.ry();
    lt = joystick.lt();
    rt = joystick.rt();

    bool is_lb_clicked = joystick.clicked(PS4::L1);
    bool is_rb_clicked = joystick.clicked(PS4::R1);

    // only clicked is true if the button is clicked and no other button is pressed
    bool is_lb_only_clicked = joystick.only_clicked(PS4::L1);
    bool is_rb_only_clicked = joystick.only_clicked(PS4::R1);
    bool is_lb_pressed = joystick.pressed(PS4::L1);
    bool is_rb_pressed = joystick.pressed(PS4::R1);
    bool is_lb_long_pressed = joystick.long_pressed(PS4::L1);
    bool is_rb_long_pressed = joystick.long_pressed(PS4::R1);

    // experiment yourself :)
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == joystick.uart.get_uart_instance())
    {
        joystick.uart_callback();
        last_rx_tick = HAL_GetTick();

        if (HAL_GetTick() - last_rx_tick > 30)
        {
            last_rx_tick = HAL_GetTick();
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
        }
    }
}