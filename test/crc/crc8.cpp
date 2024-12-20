/**
 * *********************************************************************************************
 * @file crc8.cpp
 * @brief Implementation file for the crc8 class
 * @author Robotics Team, IOE Pulchowk Campus
 * @date 2024
 *
 * For more information on CRC calculation in C, \
 * see \link https://barrgroup.com/embedded-systems/how-to/crc-calculation-c-code \endlink.
 ***********************************************************************************************
 */

#include "crc8.hpp"

CRC8 CRC8::Instance;
uint8_t CRC8::polynomial;
uint8_t CRC8::table_[CRC_HASH_TABLE_SIZE];

CRC8::CRC8()
{
    polynomial = CRC_POLYNOMIAL;
    initialize_table();
}

void CRC8::initialize_table()
{
    uint8_t remainder;
    int dividend = 0;

    for (; dividend < 256; ++dividend)
    {
        remainder = dividend;

        for (uint8_t b = 8; b > 0; --b)
        {
            if (remainder & (1 << 7))
            {
                remainder = (remainder << 1) ^ polynomial;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
        table_[dividend] = remainder;
    }
}

uint8_t CRC8::get_hash(uint8_t *buf, uint16_t len)
{
    uint8_t data;
    uint8_t remainder = 0;

    for (uint16_t index = 0; index < len; ++index)
    {
        data = buf[index] ^ remainder;
        remainder = table_[data];
    }

    return remainder;
}