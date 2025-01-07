Cyclic Redundancy Check (CRC)
=============================

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

CRC is a technique to detect errors in data. It is widely used in communication systems to detect errors in data transmission. It is also used in data storage systems to detect errors in stored data. It is a type of hash function that takes an input data stream and produces a fixed-size hash value. The hash value is used to detect errors in the data stream. The hash value is appended to the data stream before transmission. The receiver calculates the hash value of the received data stream and compares it with the hash value received. If the hash values match, the data stream is considered error-free. If the hash values do not match, an error is detected.


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

See more at :newtab:`crccalc <https://crccalc.com/?crc=123456789&method=&datatype=ascii&outtype=hex>` or at :newtab:`wikipedia <https://en.wikipedia.org/wiki/Cyclic_redundancy_check>`.

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

Please see :newtab:`this article <https://www.sunshine2k.de/articles/coding/crc/understanding_crc.html>` and go through it to understand the CRC algorithm in detail. Take your time. Get a good understanding of the algorithm. This article is the best one, I have found on the internet.

After you know CRC-8, now it easy to understand other type. CRC8-8 is worth for small size of data but for bigger chunk or less collision, CRC-16 or CRC-32 are used.

Generating lookup table for CRC-16:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

   uint16_t poly = 0x1021;
   uint16_t remainder; 
   uint16_t crc16_table[256];
   
   for (int dividend = 0; dividend < 256; ++dividend)
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

   for (int index = 0; index < len; ++index)
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

.. literalinclude:: files/crc/crc.hpp
   :language: cpp
   :linenos:

**crc.tpp**:

.. literalinclude:: files/crc/crc.tpp
   :language: cpp
   :linenos:

**crc_testing.cpp**:

.. literalinclude:: files/crc/crc_testing.cpp
   :language: cpp
   :linenos:

Compile and run using your computer. To verify, use online crc calculator: :newtab:`sunshine2k <https://www.sunshine2k.de/coding/javascript/crc/crc_js.html>` or :newtab:`crccalc <https://crccalc.com>`.

.. code-block:: bash

   g++ crc_testing.cpp -o crc_testing
   ./crc_testing

**Output**:

.. code-block:: bash

   00000000        F4ACFB13        1DF50D35        E959F626        3BEA1A6A        CF46E179        261F175F        D2B3EC4C
   77D434D4        8378CFC7        6A2139E1        9E8DC2F2        4C3E2EBE        B892D5AD        51CB238B        A567D898
   EFA869A8        1B0492BB        F25D649D        06F19F8E        D44273C2        20EE88D1        C9B77EF7        3D1B85E4
   987C5D7C        6CD0A66F        85895049        7125AB5A        A3964716        573ABC05        BE634A23        4ACFB130
   2BFC2843        DF50D350        36092576        C2A5DE65        10163229        E4BAC93A        0DE33F1C        F94FC40F
   5C281C97        A884E784        41DD11A2        B571EAB1        67C206FD        936EFDEE        7A370BC8        8E9BF0DB
   C45441EB        30F8BAF8        D9A14CDE        2D0DB7CD        FFBE5B81        0B12A092        E24B56B4        16E7ADA7
   B380753F        472C8E2C        AE75780A        5AD98319        886A6F55        7CC69446        959F6260        61339973
   57F85086        A354AB95        4A0D5DB3        BEA1A6A0        6C124AEC        98BEB1FF        71E747D9        854BBCCA
   202C6452        D4809F41        3DD96967        C9759274        1BC67E38        EF6A852B        0633730D        F29F881E
   B850392E        4CFCC23D        A5A5341B        5109CF08        83BA2344        7716D857        9E4F2E71        6AE3D562
   CF840DFA        3B28F6E9        D27100CF        26DDFBDC        F46E1790        00C2EC83        E99B1AA5        1D37E1B6
   7C0478C5        88A883D6        61F175F0        955D8EE3        47EE62AF        B34299BC        5A1B6F9A        AEB79489
   0BD04C11        FF7CB702        16254124        E289BA37        303A567B        C496AD68        2DCF5B4E        D963A05D
   93AC116D        6700EA7E        8E591C58        7AF5E74B        A8460B07        5CEAF014        B5B30632        411FFD21
   E47825B9        10D4DEAA        F98D288C        0D21D39F        DF923FD3        2B3EC4C0        C26732E6        36CBC9F5
   AFF0A10C        5B5C5A1F        B205AC39        46A9572A        941ABB66        60B64075        89EFB653        7D434D40
   D82495D8        2C886ECB        C5D198ED        317D63FE        E3CE8FB2        176274A1        FE3B8287        0A977994
   4058C8A4        B4F433B7        5DADC591        A9013E82        7BB2D2CE        8F1E29DD        6647DFFB        92EB24E8
   378CFC70        C3200763        2A79F145        DED50A56        0C66E61A        F8CA1D09        1193EB2F        E53F103C
   840C894F        70A0725C        99F9847A        6D557F69        BFE69325        4B4A6836        A2139E10        56BF6503
   F3D8BD9B        07744688        EE2DB0AE        1A814BBD        C832A7F1        3C9E5CE2        D5C7AAC4        216B51D7
   6BA4E0E7        9F081BF4        7651EDD2        82FD16C1        504EFA8D        A4E2019E        4DBBF7B8        B9170CAB
   1C70D433        E8DC2F20        0185D906        F5292215        279ACE59        D336354A        3A6FC36C        CEC3387F
   F808F18A        0CA40A99        E5FDFCBF        115107AC        C3E2EBE0        374E10F3        DE17E6D5        2ABB1DC6
   8FDCC55E        7B703E4D        9229C86B        66853378        B436DF34        409A2427        A9C3D201        5D6F2912
   17A09822        E30C6331        0A559517        FEF96E04        2C4A8248        D8E6795B        31BF8F7D        C513746E
   6074ACF6        94D857E5        7D81A1C3        892D5AD0        5B9EB69C        AF324D8F        466BBBA9        B2C740BA
   D3F4D9C9        275822DA        CE01D4FC        3AAD2FEF        E81EC3A3        1CB238B0        F5EBCE96        01473585
   A420ED1D        508C160E        B9D5E028        4D791B3B        9FCAF777        6B660C64        823FFA42        76930151
   3C5CB061        C8F04B72        21A9BD54        D5054647        07B6AA0B        F31A5118        1A43A73E        EEEF5C2D
   4B8884B5        BF247FA6        567D8980        A2D17293        70629EDF        84CE65CC        6D9793EA        993B68F9
   check: 1697D06A
   hash: 07AAD778

5. Using STM32 CRC Hardware
---------------------------

STM32 microcontrollers have CRC-32 hardware. We can use it to calculate CRC-32.

.. note::
   ``STM32F103C8T6`` and ``STM32F407VGT6`` CRC hardware have no configuration, so only default CRC-32 can be calculated. Their default parameters are:

   - **Polynomial**: 0x04C11DB7
   - **Initial Value**: 0xFFFFFFFF
   - **Final XOR Value**: None (must be applied manually if needed).
   - **Reflect Input/Output**: Not supported in hardware (manual reflection required).

5.1. CubeMX Setup
^^^^^^^^^^^^^^^^^

`Generate baisc code <../stm32_basics_tutorial/basic_setup/generate_basic_code.html>`_ with:

- ``microcontroller``: ``STM32F103C8T6``
- ``project name``: ``crc_test``
- ``Toolchain/IDE``: ``Makefile``
 
Also enable ``USB`` for ``printf`` if ``ITM SWV`` not woriking (for bluepill using duplicate stlink which do not have SWO). See `this <../stm32_basics_tutorial/usb/usb_cdc.html>`_ for USB setup.

.. image:: images/crc_test_cubemx.png
   :width: 100%
   :align: center
   :alt: crc_test_cubemx.png
   :class: padded-image

5.2. Code Implementation
^^^^^^^^^^^^^^^^^^^^^^^^

Navigate to ``Core`` > ``Src`` > ``main.c`` and add the following code. Add the following includes.

.. code-block:: c
   :emphasize-lines: 3-5

   /* Private includes ----------------------------------------------------------*/
   /* USER CODE BEGIN Includes */
   #include <string.h>
   #include <stdio.h>
   #include "usbd_cdc_if.h"
   /* USER CODE END Includes */

Add the following test code to calculate CRC-32.

.. code-block:: c
   :emphasize-lines: 2-3, 10-16

   /* USER CODE BEGIN 2 */
   char data[] = "123456789";
   char buf[100]; // For CDC transmit
   /* USER CODE END 2 */
   
   /* Infinite loop */
   /* USER CODE BEGIN WHILE */
   while (1)
   {
     uint32_t crc = HAL_CRC_Calculate(&hcrc, (uint32_t *)data, strlen(data));
     snprintf(buf, sizeof(buf), "data: %s, crc: 0x%8lX\n", data, crc);
     // if it supports CRC Hardware configurtion
     // snprintf(buf, sizeof(buf), "POL: 0x%8lX, INIT: 0x%8lX, CRC: 0x%8lX\n", hcrc.Instance->POL, hcrc.Instance->INIT, crc); 
     CDC_Transmit_FS((uint8_t*)buf, strlen(buf));
     HAL_Delay(100);
     /* USER CODE END WHILE */
   
     /* USER CODE BEGIN 3 */
   }
   /* USER CODE END 3 */

Compile and upload the code. Open the serial terminal and you will see the CRC-32 of the data. Verify output using :newtab:`online CRC calculator <https://www.sunshine2k.de/coding/javascript/crc/crc_js.html>`.

