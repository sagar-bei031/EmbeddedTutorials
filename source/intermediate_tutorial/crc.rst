Cyclic Redundancy Check (CRC)
=============================

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
   * - CRC-8
     - :math:`x^8 + x^2 + x + 1`
     - 0x07
     - Automotive, SMBus
   * - CRC-16-IBM
     - :math:`x^{16} + x^{15} + x^2 + 1`
     - 0x8005
     - IBM, ZMODEM
   * - CRC-16-CCITT
     - :math:`x^{16} + x^{12} + x^5 + 1`
     - 0x1021
     - Telecommunications, Bluetooth
   * - CRC-32 (Ethernet)
     - Standard polynomial for Ethernet
     - 0x04C11DB7
     - Ethernet, ZIP files
   * - CRC-64-ISO
     - :math:`x^{64} + x^4 + x^3 + x + 1`
     - 0x1B
     - Data storage, digital signatures

.. note::
   The actual length of the polynomial is one bit longer than the number of bits in the CRC. The most significant bit (MSB) is always 1. So, it is not included in the polynomial.

3.2. CRC Calculation
^^^^^^^^^^^^^^^^^^^^
The simplest CRC algorithm is the ``CRC-8`` algorithm. CRC can be expensive to calculate on real-time systems. So, for small crc sizes, it is better to use a lookup table.

Generating lookup table for CRC-8:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

   uint8_t remainder = 0x07; 
   // Do you know? The actual polynomial for CRC-8 is 9-bit long. But, the MSB is always 1. So, it is not included in the polynomial.

   uint8_t crc8_table[256];
   
   for (int dividend = 0; dividend < 256; ++dividend)
   {
       remainder = dividend;   
       for (uint8_t b = 8; b > 0; --b)
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
       crc8_table[dividend] = remainder; // remainder is the CRC value of dividend
   }

All the CRC value of ``0-256`` is stored in the table with the index as the dividend. For one byte data, the CRC is always in the table and is super easy. But for array, the remainder(CRC) of first byte (from table) is xored with the second byte, and the resulting value acts as dividend whose remainder(CRC from table) xored with third byte and so on. The remainder(CRC) of final byte calculated through this process is the remainder(CRC) of the whole array.

Calculating CRC-8 of array using lookup table:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c
   
   uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05}; // input data

   uint8_t dividend;
   uint8_t remainder = 0;

   for (uint16_t index = 0; index < len; ++index)
   {
       dividend = buf[index] ^ remainder;
       remainder = crc8_table[dividend];
   }

   printf("CRC-8: 0x%02X\n", remainder);

Please see `this article <https://www.sunshine2k.de/articles/coding/crc/understanding_crc.html>`__ and go through it to understand the CRC algorithm in detail. Take your time. Get a good understanding of the algorithm. This article is the best one, I have found on the internet.

