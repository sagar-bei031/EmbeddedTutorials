#include <memory.h>

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
uint8_t transmitting_bytes[sizeof(Twist) + 2];

uint32_t last_tranmsit_tick = 0;
uint32_t last_led_blink_tick = 0;

void setup()
{
}

void loop()
{
    if (HAL_GetTick() - last_tranmsit_tick < 10)
        return;

    twist.vx = 0.5f;
    twist.vy = 0.5f;
    twist.w = 0.0f;

    transmitting_bytes[0] = START_BYTE;
    memcpy(transmitting_bytes + 1, &twist, sizeof(twist));
    transmitting_bytes[sizeof(transmitting_bytes) - 1] = CRC8::get_hash((uint8_t *)&twist, sizeof(twist));

    HAL_UART_Transmit_DMA(&huart1, (uint8_t *)transmitting_bytes, sizeof(transmitting_bytes));

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

// Make sure you have enabled the UART interrupt in the CubeMX
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == huart1.Instance)
    {
        blink_led();
    }
}