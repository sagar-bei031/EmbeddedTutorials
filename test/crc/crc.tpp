/**
 * *********************************************************************************************
 * @file    crc.tpp
 * @brief   Inline implementation file for the CRC template class
 * @ref     https://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
 * @author  Sagar Chaudhary
 * @date    2024
 ***********************************************************************************************
 */

#include <string.h>
#include <stdio.h>

#include "crc.hpp"

template <typename CRC_Type>
inline CRC_Type CRC<CRC_Type>::reflect_bits(CRC_Type value, int num_bits)
{
    CRC_Type reflected = 0;
    for (int i = 0; i < num_bits; ++i)
    {
        if (value & (1 << i))
        {
            reflected |= (1 << (num_bits - 1 - i));
        }
    }
    return reflected;
}

template <>
CRC<CRC8_Type>::CRC()
    : polynomial_(CRC8_SMBUS_POLYNOMIAL),
      initial_crc_(CRC8_SMBUS_INITIAL_CRC),
      final_xor_(CRC8_SMBUS_FINAL_XOR),
      reflect_input_(CRC8_SMBUS_REFLECT_INPUT),
      reflect_output_(CRC8_SMBUS_REFLECT_OUTPUT)
{
    this->initialize();
}

template <>
CRC<CRC16_Type>::CRC()
    : polynomial_(CRC16_CCITT_POLYNOMIAL),
      initial_crc_(CRC16_CCITT_INITIAL_CRC),
      final_xor_(CRC16_CCITT_FINAL_XOR),
      reflect_input_(CRC16_CCITT_REFLECT_INPUT),
      reflect_output_(CRC16_CCITT_REFLECT_OUTPUT)
{
    this->initialize();
}

template <>
CRC<CRC32_Type>::CRC()
    : polynomial_(CRC32_ISO_POLYNOMIAL),
      initial_crc_(CRC32_ISO_INITIAL_CRC),
      final_xor_(CRC32_ISO_FINAL_XOR),
      reflect_input_(CRC32_ISO_REFLECT_INPUT),
      reflect_output_(CRC32_ISO_REFLECR_OUTPUT)
{
    this->initialize();
}

template <typename CRC_Type>
CRC<CRC_Type>::CRC(CRC_Type polynomial, CRC_Type initial_crc, CRC_Type final_xor,
                   bool reflect_input, bool reflect_output)
    : polynomial_(polynomial),
      initial_crc_(initial_crc),
      final_xor_(final_xor),
      reflect_input_(reflect_input),
      reflect_output_(reflect_output)
{
    if (polynomial == 0)
        printf("ERROR::CRC polynomial cannot be zero\n");

    this->initialize();
}

template <typename CRC_Type>
inline void CRC<CRC_Type>::initialize()
{
    this->compute_table();

    const char crc_validation_string[] = CRC_VALIDATION_STRING;
    this->check_ = this->compute_hash((uint8_t *)crc_validation_string, strlen(crc_validation_string));
}

template <typename CRC_Type>
inline void CRC<CRC_Type>::compute_table()
{
    for (uint dividend = 0; dividend < 256; ++dividend)
    {
        CRC_Type remainder = dividend << (this->width - 8);

        for (int bit = 8; bit > 0; --bit)
        {
            if (remainder & (1 << (width - 1)))
            {
                remainder = (remainder << 1) ^ this->polynomial_;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }

        this->table_[(uint8_t)dividend] = remainder;
    }
}

template <typename CRC_Type>
inline CRC_Type CRC<CRC_Type>::compute_hash(const uint8_t *data, const size_t len) const
{
    CRC_Type remainder = this->initial_crc_;
    uint8_t dividend;

    if (data != nullptr)
    {
        for (size_t index = 0; index < len; ++index)
        {
            dividend = reflect_input_ ? reflect_bits(data[index], 8) : data[index];
            dividend ^= (remainder >> (this->width - 8));
            remainder = table_[dividend] ^ (remainder << 8);
        }
    }

    return (reflect_output_ ? reflect_bits(remainder, this->width) : remainder) ^ this->final_xor_;
}

template <typename CRC_Type>
inline void CRC<CRC_Type>::print_table() const
{
    for (int i = 0; i < 256; ++i)
    {
        printf("%0*X", this->width / 4, this->table_[i]);

        if ((i + 1) % 8 == 0)
        {
            printf("\n");
        }
        else
        {
            printf("\t");
        }
    }
}
