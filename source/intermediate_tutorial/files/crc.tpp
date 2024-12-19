/**
 * @file crc.tpp
 * @brief Inline implementation file for the CRC template class.
 * 
 * This file contains the inline implementation of the CRC template class, 
 * including methods for bit reflection, table computation, and CRC calculation.
 * 
 * @ref https://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
 * 
 * @details
 * The CRC template class supports computation of CRC values for 8-bit, 16-bit, 
 * and 32-bit types. This file includes the reflection function, constructors 
 * for default and parameterized configurations, table initialization, and the 
 * main hash computation function. Additionally, the CRC lookup table can be printed 
 * for debugging or validation purposes.
 * 
 * @note
 * Ensure that the CRC polynomial is non-zero when using the parameterized constructor.
 * 
 * @warning
 * The CRC template does not allow copy construction or assignment.
 * 
 * @author 
 * Sagar Chaudhary
 * 
 * @date 
 * 2024
 */

#include <string.h>
#include <stdio.h>

#include "crc.hpp"

/**
 * @brief Reflects the bits of a value.
 * 
 * @tparam CRC_Type The type of the value (e.g., uint8_t, uint16_t, uint32_t).
 * @param value The value to reflect.
 * @param num_bits The number of bits to reflect.
 * @return The reflected value.
 */
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

/**
 * @brief Default constructor for CRC-8 configuration.
 */
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

/**
 * @brief Default constructor for CRC-16 configuration.
 */
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

/**
 * @brief Default constructor for CRC-32 configuration.
 */
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

/**
 * @brief Parameterized constructor for CRC configuration.
 * 
 * @param polynomial The polynomial for CRC calculation.
 * @param initial_crc The initial CRC value.
 * @param final_xor The final XOR value.
 * @param reflect_input Flag to enable input bit reflection.
 * @param reflect_output Flag to enable output bit reflection.
 */
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

/**
 * @brief Initializes the CRC instance, including table computation and validation.
 */
template <typename CRC_Type>
inline void CRC<CRC_Type>::initialize()
{
    this->compute_table();

    const char crc_validation_string[] = CRC_VALIDATION_STRING;
    this->check_ = this->compute_hash((uint8_t *)crc_validation_string, strlen(crc_validation_string));
}

/**
 * @brief Computes the CRC lookup table.
 */
template <typename CRC_Type>
inline void CRC<CRC_Type>::compute_table()
{
    // Calculate CRC of all 256 possible byte values.
    for (uint dividend = 0; dividend < 256; ++dividend)
    {
        // Align the byte to leftmost position.
        CRC_Type remainder = dividend << (this->width - 8);

        for (int bit = 8; bit > 0; --bit)
        {
            // Left shift till bit 1 found at MSB.
            if (remainder & (1 << (width - 1)))
            {
                // XOR with polynomial if MSB is 1.
                // The MSB of polynomial is always 1 which is not included. So, MSB polynomial ^ MSB of remainder = 0.
                // That's why it is left lefted first then XORed to find remainder.
                remainder = (remainder << 1) ^ this->polynomial_;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }

        // Store the remainder in the lookup table.
        this->table_[dividend] = remainder;
    }
}

/**
 * @brief Computes the CRC hash for the given data.
 * 
 * @param data Pointer to the input data.
 * @param len Length of the input data.
 * @return The computed CRC value.
 */
template <typename CRC_Type>
inline CRC_Type CRC<CRC_Type>::compute_hash(const uint8_t *data, const size_t len) const
{
    // Initialize the remainder with the initial CRC value.
    CRC_Type remainder = this->initial_crc_;
    uint8_t dividend;

    // data cannot be nullptr.
    if (data != nullptr)
    {
        // Initial CRC is XORed with first byte; the CRC of resulting is XORed with second byte and so on.
        // The final CRC is XORed with final_xor_.

        for (size_t index = 0; index < len; ++index)
        {
            // Reflect byte from data if enabled.
            dividend = reflect_input_ ? reflect_bits(data[index], 8) : data[index];
            
            // Left most byte of remainder is XORed with data as data is one byte in each step.
            dividend ^= (remainder >> (this->width - 8));

            // CRC of resultant is taken from lookup table.
            // Used left most byte of remainder is removed shifting left by 8.
            // Now, XORed to find new remainder.
            remainder = table_[dividend] ^ (remainder << 8);
        }
    }

    // Reflect remainder if enabled and XOR with final xor value.
    return (reflect_output_ ? reflect_bits(remainder, this->width) : remainder) ^ this->final_xor_;
}

/**
 * @brief Prints the CRC lookup table to the console.
 */
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
