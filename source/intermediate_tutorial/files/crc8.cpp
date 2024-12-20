/**
 * *********************************************************************************************
 * @file crc8.cpp
 * @brief Implementation file for the 8-bit SMBus CRC class
 * @author Robotics Team, IOE Pulchowk Campus
 * @date 2024
 *
 * For more information on CRC calculation in C, \
 * see \link https://barrgroup.com/embedded-systems/how-to/crc-calculation-c-code \endlink.
 ***********************************************************************************************
 */

#include <stdio.h>
#include "crc8.hpp"

CRC8 CRC8::Instance;
uint8_t CRC8::polynomial_;
uint8_t CRC8::check_;
uint8_t CRC8::table_[256];

CRC8::CRC8()
{
    polynomial_ = CRC8_SMBUS_POLYNOMIAL;
    initialize_table();

    uint8_t data[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    check_ = get_hash(data, sizeof(data));
}

void CRC8::initialize_table()
{
    uint8_t remainder;
    int dividend;
    int bit;

    for (dividend = 0; dividend < 256; ++dividend)
    {
        remainder = dividend;

        for (bit = 8; bit > 0; --bit)
        {
            if (remainder & 0x80)
            {
                remainder = (remainder << 1) ^ polynomial_;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
        table_[(uint8_t)dividend] = remainder;
    }
}

uint8_t CRC8::get_hash(const uint8_t *data, uint16_t len)
{
    uint8_t remainder = 0;
    uint8_t dividend;
    int i;

    for (i = 0; i < len; ++i)
    {
        dividend = data[i] ^ remainder;
        remainder = table_[dividend];
    }

    return remainder;
}

void CRC8::print_table()
{
    for (int i = 0; i < 256; ++i)
    {
        printf("0x%02X, ", table_[i]);
        if ((i + 1) % 8 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}