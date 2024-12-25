/**
 ******************************************************************************
 * @file    crc8.hpp
 * @brief   Header file 8-bit SMBus CRC calculation
 * @author  Robotics Team, IOE Pulchowk Campus
 ******************************************************************************
 */

#ifndef CRC8_HPP
#define CRC8_HPP

#include <stdint.h>

#define CRC8_SMBUS_POLYNOMIAL 0x07 /**< CRC-8 polynomial for SMBus. */

/**
 * @brief Class for CRC-8 checksum calculation.
 */
class CRC8
{
public:
    /**
     * @brief Calculate CRC-8 checksum for uint8_t type data.
     * @param buf Pointer to the data buffer.
     * @param len Length of the data buffer.
     * @return CRC-8 checksum value.
     */
    static uint8_t get_hash(const uint8_t *data, const uint16_t len);

    /**
     * @brief Print the CRC hash table.
     */
    static void print_table();

    static uint8_t get_polynomial() { return polynomial_; } /**< Get the CRC polynomial. */
    static uint8_t get_check() { return check_; }           /**< Get the CRC check value. */
    static const uint8_t *get_table() { return table_; }    /**< Get the CRC hash table. */

    static CRC8 Instance; /**< Singleton instance of CRC8 class. */

private:
    static uint8_t polynomial_; /** CRC polynomial **/
    static uint8_t check_;      /**< CRC check value. */
    static uint8_t table_[256]; /**< CRC hash table. */

    /**
     * @brief Private constructor for CRC8 class.
     */
    CRC8();

    /**
     * @brief Initialize the CRC hash table.
     */
    static void initialize_table();
};

#endif // CRC_HPP