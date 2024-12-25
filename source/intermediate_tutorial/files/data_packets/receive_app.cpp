#include <memory.h>
#include <stdio.h>

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "crc8.hpp"
#include "app.h"

#define START_BYTE 0xA5

struct Twist
{
    float vx;
    float vy;
    float w;
};

Twist twist = {0.0f, 0.0f, 0.0f};
uint8_t receiving_bytes[sizeof(Twist) + 2];
bool is_waiting_for_start_byte = true;
uint16_t rx_seq = 0;
uint16_t used_rx_seq = 0;

uint32_t last_receive_tick = 0;
uint32_t last_led_blink_tick = 0;
uint32_t last_print_tick = 0;


void setup()
{
    HAL_UART_Receive_DMA(&huart1, (uint8_t *)receiving_bytes, 1);
    is_waiting_for_start_byte = true;
}

void loop()
{
    if (HAL_GetTick() - last_tranmsit_tick < 10)
        return;

    if (rx_seq != used_rx_seq)
    {
        print_twist();
        used_rx_seq = rx_seq;
    }

    if (huart1.gstate != HAL_UART_STATE_BUSY_TX)
    {
        HAL_UART_Receive_DMA(&huart1, (uint8_t *)receiving_bytes, 1);
        is_waiting_for_start_byte = true;
        blink_led(); // blink led to show error
    }

    last_tranmsit_tick = HAL_GetTick();
}

void blink_led()
{
    if (HAL_GetTick() - last_led_blink_tick > 100)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        last_led_blink_tick = HAL_GetTick();
    }
}

void print_twist()
{
    if (HAL_GetTick() - last_print_tick > 100)
    {
        printf("vx: %f, vy: %f, w: %f\n", twist.vx, twist.vy, twist.w);
        last_print_tick = HAL_GetTick();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    __HAL_UART_FLUSH_DRREGISTER(huart);

    if (huart->Instance == huart1.Instance)
    {
        if (is_waiting_for_start_byte)
        {
            // verify start byte
            if (receiving_bytes[0] == START_BYTE)
            {
                HAL_UART_Receive_DMA(&huart1, (uint8_t *)receiving_bytes + 1, sizeof(Twist) + 1);
                is_waiting_for_start_byte = false;
            }
            else
            {
                HAL_UART_Receive_DMA(&huart1, (uint8_t *)receiving_bytes, 1);
                blink_led(); // blink led to show error
            }
        }
        else
        {
            // verify hash
            if (receiving_bytes[sizeof(receiving_bytes) - 1] == CRC8::get_hash(receiving_bytes + 1, sizeof(Twist)))
            {
                memcpy(&twist, receiving_bytes + 1, sizeof(Twist));
                rx_seq++;
            }
            else
            {
                blink_led(); // blink led to show error
            }

            is_waiting_for_start_byte = true;
            last_receive_tick = HAL_GetTick();
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    __HAL_UART_FLUSH_DRREGISTER(huart);

    if (huart->Instance == huart1.Instance)
    {
        HAL_UART_Receive_DMA(&huart1, (uint8_t *)receiving_bytes, 1);
        is_waiting_for_start_byte = true;
        blink_led(); // blink led to show error
    }
}