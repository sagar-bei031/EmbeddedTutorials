/**
 * *********************************************************************************************
 * @file    crc.hpp
 * @brief   Header file for CRC template class
 * @author  Sagar Chaudhary
 * @date    2024
 ***********************************************************************************************
 */

#ifndef CRC_HPP
#define CRC_HPP

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <type_traits>

/**
 * @typedef CRC8_Type
 * @brief Defines an 8-bit CRC type.
 */
using CRC8_Type = uint8_t;

/**
 * @typedef CRC16_Type
 * @brief Defines a 16-bit CRC type.
 */
using CRC16_Type = uint16_t;

/**
 * @typedef CRC32_Type
 * @brief Defines a 32-bit CRC type.
 */
using CRC32_Type = uint32_t;

#define CRC8_SMBUS_POLYNOMIAL 0x07
#define CRC8_SMBUS_INITIAL_CRC 0x00
#define CRC8_SMBUS_FINAL_XOR 0x00
#define CRC8_SMBUS_REFLECT_INPUT false
#define CRC8_SMBUS_REFLECT_OUTPUT false

/// Polynomial for CRC-16 CCITT
#define CRC16_CCITT_POLYNOMIAL 0x1021
#define CRC16_CCITT_INITIAL_CRC 0xFFFF
#define CRC16_CCITT_FINAL_XOR 0X0000
#define CRC16_CCITT_REFLECT_INPUT false
#define CRC16_CCITT_REFLECT_OUTPUT false

/// Polynomial for CRC-32 ISO
#define CRC32_ISO_POLYNOMIAL 0x04C11DB7
#define CRC32_ISO_INITIAL_CRC 0xFFFFFFFF
#define CRC32_ISO_FINAL_XOR 0XFFFFFFFF
#define CRC32_ISO_REFLECT_INPUT true
#define CRC32_ISO_REFLECR_OUTPUT true

/// Default string used for CRC validation
#define CRC_VALIDATION_STRING "123456789"

/**
 * @class CRC
 * @brief Template class for CRC calculation with reflection support.
 *
 * @tparam CRC_Type The type of CRC (CRC8_Type, CRC16_Type, or CRC32_Type).
 */
template <typename CRC_Type>
class CRC
{
    static_assert(std::is_same<CRC_Type, CRC8_Type>::value ||
                      std::is_same<CRC_Type, CRC16_Type>::value ||
                      std::is_same<CRC_Type, CRC32_Type>::value,
                  "CRC template class only supports CRC8_Type, CRC16_Type, and CRC32_Type!");

public:
    /**
     * @brief Default constructor for CRC
     */
    CRC();

    /**
     * @brief Parametric Constructor for CRC
     *
     * @param polynomial The polynomial for CRC calculation
     * @param initial_CRC The initial CRC value
     * @param final_CRC_XOR The final CRC XOR value
     * @param input_reflection Flag to enable input reflection
     * @param output_reflection Flag to enable output reflection
     */
    CRC(CRC_Type polynomial, CRC_Type initial_crc = 0, const CRC_Type final_xor = 0,
        bool reflect_input = false, bool reflect_output = false);

    /**
     * @brief Delete copy constructor
     */
    CRC(const CRC &) = delete;

    /**
     * @brief Delete assignment operator
     */
    CRC &operator=(const CRC &) = delete;

    /**
     * @brief Compute the CRC hash for the given data
     *
     * @param data The data for which CRC hash is to be computed
     * @param len The length of the data
     * @return The computed CRC hash
     */
    CRC_Type compute_hash(const uint8_t *data, const size_t len) const;

    /**
     * @brief Print the CRC table
     */
    void print_table() const;

    const CRC_Type get_polynomial() const { return polynomial_; }       ///< Get the polynomial
    const CRC_Type get_initial_crc() const { return initial_crc_; }     ///< Get the initial CRC
    const CRC_Type get_final_xor() const { return final_xor_; } ///< Get the final CRC XOR
    const CRC_Type *get_table() const { return table_; }                ///< Get the CRC table
    const CRC_Type get_check() const { return check_; }                 ///< Get the CRC check

    /**
     * @brief Reflect bits of a value
     *
     * @param value The value whose bits are to be reflected
     * @param num_bits The number of bits to reflect
     * @return The reflected value
     */
    static CRC_Type reflect_bits(CRC_Type value, int num_bits);

    static constexpr int width = sizeof(CRC_Type) * 8;

private:
    void initialize();
    void compute_table();

    const CRC_Type polynomial_;
    const CRC_Type initial_crc_;
    const CRC_Type final_xor_;
    const bool reflect_input_;
    const bool reflect_output_;
    CRC_Type table_[256];
    CRC_Type check_;
};

#include "crc.tpp"

#endif // CRC_HPP
