/**
 * @file crc.hpp
 * @brief Header file for the CRC template class, providing support for CRC computation with customizable parameters.
 *
 * This file defines a template class for calculating CRC (Cyclic Redundancy Check) with support for reflection and various CRC types.
 *
 * @details
 * The `CRC` template class supports 8-bit, 16-bit, and 32-bit CRC calculations with configurable polynomials,
 * initial values, final XOR values, and input/output bit reflections. It includes functionality for table generation
 * and bit reflection. The default configuration values and polynomial constants for common CRC types (e.g., CRC-8 SMBus,
 * CRC-16 CCITT, CRC-32 ISO) are also provided.
 *
 * @note
 * This implementation enforces compile-time type checks to ensure only valid CRC types are used.
 *
 * @author
 * Sagar Chaudhary
 *
 * @date
 * 2024
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

// Definitions of some CRC standards
#define CRC8_SMBUS_POLYNOMIAL 0x07      ///< Polynomial for CRC-8 SMBus
#define CRC8_SMBUS_INITIAL_CRC 0x00     ///< Initial value for CRC-8 SMBus
#define CRC8_SMBUS_FINAL_XOR 0x00       ///< Final XOR value for CRC-8 SMBus
#define CRC8_SMBUS_REFLECT_INPUT false  ///< Input reflection for CRC-8 SMBus
#define CRC8_SMBUS_REFLECT_OUTPUT false ///< Output reflection for CRC-8 SMBus

#define CRC16_CCITT_POLYNOMIAL 0x1021    ///< Polynomial for CRC-16 CCITT
#define CRC16_CCITT_INITIAL_CRC 0xFFFF   ///< Initial value for CRC-16 CCITT
#define CRC16_CCITT_FINAL_XOR 0x0000     ///< Final XOR value for CRC-16 CCITT
#define CRC16_CCITT_REFLECT_INPUT false  ///< Input reflection for CRC-16 CCITT
#define CRC16_CCITT_REFLECT_OUTPUT false ///< Output reflection for CRC-16 CCITT

#define CRC32_ISO_POLYNOMIAL 0x04C11DB7  ///< Polynomial for CRC-32 ISO
#define CRC32_ISO_INITIAL_CRC 0xFFFFFFFF ///< Initial value for CRC-32 ISO
#define CRC32_ISO_FINAL_XOR 0xFFFFFFFF   ///< Final XOR value for CRC-32 ISO
#define CRC32_ISO_REFLECT_INPUT true     ///< Input reflection for CRC-32 ISO
#define CRC32_ISO_REFLECR_OUTPUT true    ///< Output reflection for CRC-32 ISO

#define CRC_VALIDATION_STRING "123456789" ///< Standard validation string for CRC

/**
 * @class CRC
 * @brief Template class for CRC computation.
 *
 * @tparam CRC_Type The CRC type, must be one of `CRC8_Type`, `CRC16_Type`, or `CRC32_Type`.
 *
 * @details
 * This class allows calculation of CRC using a lookup table for improved performance.
 * It supports customizable parameters such as polynomial, initial value, and bit reflection.
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
     * @brief Default constructor.
     */
    CRC();

    /**
     * @brief Constructor with customizable parameters.
     *
     * @param polynomial The polynomial for CRC calculation.
     * @param initial_crc The initial CRC value (default is 0).
     * @param final_xor The final XOR value (default is 0).
     * @param reflect_input Enable input bit reflection (default is false).
     * @param reflect_output Enable output bit reflection (default is false).
     */
    CRC(CRC_Type polynomial, CRC_Type initial_crc = 0, const CRC_Type final_xor = 0,
        bool reflect_input = false, bool reflect_output = false);

    /**
     * @brief Deleted copy constructor.
     */
    CRC(const CRC &) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    CRC &operator=(const CRC &) = delete;

    /**
     * @brief Compute the CRC hash for the given data.
     *
     * @param data Pointer to the input data.
     * @param len Length of the input data.
     * @return The computed CRC value.
     */
    CRC_Type compute_hash(const uint8_t *data, const size_t len) const;

    /**
     * @brief Print the CRC lookup table.
     */
    void print_table() const;

    // Getters for class members
    const CRC_Type get_polynomial() const;  ///< Get the polynomial used for CRC.
    const CRC_Type get_initial_crc() const; ///< Get the initial CRC value.
    const CRC_Type get_final_xor() const;   ///< Get the final XOR value.
    const CRC_Type *get_table() const;      ///< Get the CRC lookup table.
    const CRC_Type get_check() const;       ///< Get the validation CRC value.

    /**
     * @brief Reflect the bits of a value.
     *
     * @param value The value to reflect.
     * @param num_bits Number of bits to reflect.
     * @return The reflected value.
     */
    static CRC_Type reflect_bits(CRC_Type value, int num_bits);

    static constexpr int width = sizeof(CRC_Type) * 8; ///< CRC width in bits.

private:
    void initialize();    ///< Initialize CRC parameters.
    void compute_table(); ///< Compute the CRC lookup table.

    const CRC_Type polynomial_;  ///< Polynomial for CRC calculation.
    const CRC_Type initial_crc_; ///< Initial CRC value.
    const CRC_Type final_xor_;   ///< Final XOR value.
    const bool reflect_input_;   ///< Input bit reflection flag.
    const bool reflect_output_;  ///< Output bit reflection flag.
    CRC_Type table_[256];        ///< Lookup table for CRC calculation.
    CRC_Type check_;             ///< Validation CRC value.
};

#include "crc.tpp"

#endif // CRC_HPP
