Cyclic Redundancy Check (CRC)
=============================

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

CRC is a technique to detect errors in data transmission. It is widely used in communication systems to detect errors in data transmission. It is also used in data storage systems to detect errors in stored data. It is a type of hash function that takes an input data stream and produces a fixed-size hash value. The hash value is used to detect errors in the data stream. The hash value is appended to the data stream before transmission. The receiver calculates the hash value of the received data stream and compares it with the hash value received. If the hash values match, the data stream is considered error-free. If the hash values do not match, an error is detected.


2. Types of CRC
---------------

There are many types of CRC algorithms. The most common types are ``CRC-8``, ``CRC-16``, and ``CRC-32``. The number in the name of the CRC algorithm represents the size of the hash value produced by the algorithm. For example, CRC-8 produces an 8-bit hash value, CRC-16 produces a 16-bit hash value, and CRC-32 produces a 32-bit hash value.


3. Understanding CRC
--------------------

The algorithm works by dividing the input data stream by a ``fixed polynomial``. The remainder of the division is the ``hash value``.

3.1. CRC Polynomials
^^^^^^^^^^^^^^^^^^^^
Many industries have standardized on specific polynomials for compatibility and proven reliability.

.. list-table:: CRC Polynomials
   :header-rows: 1
   :widths: 20 40 15 25

   * - Name
     - Polynomial
     - Hex
     - Applications
   * - CRC-8-SMBUS
     - :math:`x^8 + x^2 + x + 1`
     - ``0x07``
     - Automotive, SMBus
   * - CRC-16-IBM
     - :math:`x^{16} + x^{15} + x^2 + 1`
     - ``0x8005``
     - IBM, ZMODEM
   * - CRC-16-CCITT
     - :math:`x^{16} + x^{12} + x^5 + 1`
     - ``0x1021``
     - Telecommunications, Bluetooth
   * - CRC-32-ISO
     - :math:`x^{32} + x^{26} + x^{23} + x^{22} + x^{16} + x^{12} + x^{11} + x^{10} + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1`
     - ``0x04C11DB7``
     - Ethernet, ZIP files
   * - CRC-64-ISO
     - :math:`x^{64} + x^4 + x^3 + x + 1`
     - ``0x1B``
     - Data storage, digital signatures

See more at `crccalc <https://crccalc.com/?crc=123456789&method=&datatype=ascii&outtype=hex>`__ or at `wikipedia <https://en.wikipedia.org/wiki/Cyclic_redundancy_check>`__.

.. note::
   The actual length of the polynomial is one bit longer than the number of bits in the CRC. The most significant bit (MSB) is always 1. So, it is not included in the polynomial.

3.2. CRC Calculation
^^^^^^^^^^^^^^^^^^^^
The simplest CRC algorithm is the ``CRC-8`` algorithm. CRC can be expensive to calculate on real-time systems. So, it is better to use a lookup table.

Generating lookup table for CRC-8:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

   uint8_t poly = 0x07;
   // Do you know? The actual polynomial for CRC-8 is 9-bit long. But, the MSB is always 1. So, it is not included in the polynomial.

   uint8_t remainder; 
   uint8_t crc8_table[256];
   
   for (int dividend = 0; dividend < 256; ++dividend)
   {
       remainder = dividend;   
       for (int b = 8; b > 0; --b)
       {
           if (remainder & (1 << 7))  // if MSB is 1
           {
               remainder = (remainder << 1) ^ poly; // XOR with polynomial. The MSB is removed because, (MSB of remainder i.e. 1) ^ (MSB of 9-bit polynomial i.e. 1) = 0 always.
           }
           else
           {
               remainder = (remainder << 1); // left shift till MSB becomes 1
           }
       }
       crc8_table[(uint8_t)dividend] = remainder; // remainder is the CRC value of dividend
   }

All the CRC value of ``0-256`` is stored in the table with the index as the dividend. For one byte data, the CRC is always in the table and is super easy. But for array, the remainder(CRC) of first byte (from table) is xored with the second byte, and the resulting value acts as dividend whose remainder(CRC from table) xored with third byte and so on. The remainder(CRC) of final byte calculated through this process is the remainder(CRC) of the whole array.

Calculating CRC-8 of array using lookup table:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c
   
   uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05}; // input data

   uint8_t dividend;
   uint8_t remainder = 0;

   for (int index = 0; index < len; ++index)
   {
       dividend = data[index] ^ remainder;
       remainder = crc8_table[dividend];
   }

   printf("CRC-8: 0x%02X\n", remainder);

Please see `this article <https://www.sunshine2k.de/articles/coding/crc/understanding_crc.html>`__ and go through it to understand the CRC algorithm in detail. Take your time. Get a good understanding of the algorithm. This article is the best one, I have found on the internet.

After you know CRC-8, now it easy to understand other type. CRC8-8 is worth for small size of data but for bigger chunk or less collision, CRC-16 or CRC-32 are used.

Generating lookup table for CRC-16:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

   uint16_t poly = 0x1021;
   uint16_t remainder; 
   uint16_t crc16_table[256];
   
   for (uint dividend = 0; dividend < 256; ++dividend)
   {
       remainder = dividend << 8; // This is the difference from CRC-8. The 8 bits are aligned to MSB of 16-bit. For CRC-32, it is shifted left by 24;
       for (int b = 8; b > 0; --b)
       {
           if (remainder & (1 << 7))  // if MSB is 1
           {
               remainder = (remainder << 1) ^ poly; // XOR with polynomial. The MSB is removed because, (MSB of remainder i.e. 1) ^ (MSB of 9-bit polynomial i.e. 1) = 0 always.
           }
           else
           {
               remainder = (remainder << 1); // left shift till MSB becomes 1
           }
       }
       crc16_table[(uint8_t)dividend] = remainder; // remainder is the CRC value of dividend
   }

Calculating CRC-16 of array using lookup table:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c
   
   uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05}; // input data

   uint8_t dividend;
   uint16_t remainder = 0;

   for (uint index = 0; index < len; ++index)
   {
       dividend = data[index] ^ (remainder >> 8); // For CRC-16, remainder have to be shifted right by 8. For CRC-32, it is 24. 
       remainder = crc16_table[dividend];
   }

   printf("CRC-16: 0x%04X\n", remainder);

You got the idea. Now, you can generate the lookup table for CRC-32 and calculate the CRC-32 of the data. The are also some parameters like initial value, final XOR value, input reflected, output reflected and check value, which can be used to improve the CRC calculation. But, the above code is the basic one.


4. Implementing CRC in C++
--------------------------

Let's implement the CRC algorithm in C++ using template class. I hope you have basic knowledge of C++ programming. In embedded programming, use of C++ standard library (eg: iostream, std::vector) is not recommended. Create and copy these three files.

crc.hpp:
^^^^^^^^

.. literalinclude:: files/crc.hpp
   :language: cpp
   :linenos:

crc.tpp:
^^^^^^^^

.. literalinclude:: files/crc.tpp
   :language: cpp
   :linenos:

crc_testing.cpp:
^^^^^^^^^^^^^^^^

.. literalinclude:: files/crc_testing.cpp
   :language: cpp
   :linenos:

Compile and run using your computer. To verify, use online crc calculator: `sunshine2k <https://www.sunshine2k.de/coding/javascript/crc/crc_js.html>`__ or `crccalc <https://crccalc.com>`__.

.. code-block:: bash

   g++ crc_testing.cpp -o crc_testing
   ./crc_testing

5. Using STM32 CRC Hardware
---------------------------

STM32 microcontrollers have CRC-32 hardware. We can use it to calculate CRC-32.

.. note::
   ``STM32F103C8T6`` and ``STM32F407VGT6`` CRC hardware have no configuration, so only default CRC-32 can be calculated. Their default parameters are:

   - **Polynomial**: 0x04C11DB7
   - **Initial Value**: 0xFFFFFFFF
   - **Final XOR Value**: None (must be applied manually if needed).
   - **Reflect Input/Output**: Not supported in hardware (manual reflection required).

`Generate baisc code <../stm32_basics_tutorial/basic_setup/generate_basic_code.html>`__ with:

- ``microcontroller``: ``STM32F103C8T6``
- ``project name``: ``crc_test``
- ``Toolchain/IDE``: ``Makefile``
 
Also enable ``USB`` for ``printf`` if ``ITM SWV`` not woriking (for bluepill using duplicate stlink). See `this <../stm32_basics_tutorial/usb/usb_cdc.html>`__ for USB setup.

.. image:: images/crc_test_cubemx.png
   :width: 100%
   :align: center
   :alt: crc_test_cubemx.png
   :class: padded-image

Navigate to ``Core`` > ``Src`` > ``main.c`` and add the following code. Add the following includes.

.. code-block:: c

   /* Private includes ----------------------------------------------------------*/
   /* USER CODE BEGIN Includes */
   #include <string.h>
   #include <stdio.h>
   #include "usbd_cdc_if.h"
   /* USER CODE END Includes */

Add the following test code to calculate CRC-32.

.. code-block:: c

   /* USER CODE BEGIN 2 */
   char data[] = "123456789";
   char buf[100]; // For CDC transmit
   /* USER CODE END 2 */
   
   /* Infinite loop */
   /* USER CODE BEGIN WHILE */
   while (1)
   {
     uint32_t crc = HAL_CRC_Calculate(&hcrc, (uint32_t *)data, strlen(data));
     snprintf(buf, sizeof(buf), "data: %s, crc: %lu\n", data, crc);
     CDC_Transmit_FS((uint8_t*)buf, strlen(buf));
     /* USER CODE END WHILE */
   
     /* USER CODE BEGIN 3 */
   }
   /* USER CODE END 3 */

Compile and upload the code. Open the serial terminal and you will see the CRC-32 of the data.