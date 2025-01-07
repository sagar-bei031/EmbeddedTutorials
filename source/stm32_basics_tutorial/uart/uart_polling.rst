UART with Polling
=================

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

UART in polling mode transmit data and receive data untill the data is transmitted and received respectively or timeout. This is the simplest way to use UART. But it is not efficient as it blocks the CPU for doing other job.



2. CubeMX Configuration
-----------------------

- Open CubeMX and `generate basic code <../basic_setup/generate_basic_code.html>`_ with:

  - microcontroller: ``stm32f407vgt6`` or board: ``STM32F407VG-DISC1``
  - project name: ``uart_polling``
  - Toolchain/IDE: ``Makefile``

- Move to STM32CubeMX ``Pinout and Congiguration``. From ``Categories``, select ``Connectivity > USART2``. Change ``mode`` to ``Asynchronous`` mode.

.. image:: images/uart_polling.webp
   :width: 100%
   :align: center
   :alt: usart2_polling

- Generate code and open the project.



3. Code to Send and Receive Data using UART Polling
---------------------------------------------------
    
- Navigate to ``Core > Src`` and open ``main.c``. 

- Include header file.

  .. tabs::
     
     .. group-tab:: SWV

        .. code-block:: c
           :emphasize-lines: 2
          
           /* USER CODE BEGIN Includes */
           #include <stdio.h>
           /* USER CODE END Includes */

     .. group-tab:: USB

        .. code-block:: c
           :emphasize-lines: 2-3
          
           /* USER CODE BEGIN Includes */
           #include <stdio.h>
           #include "usbd_cdc_if.h"
           /* USER CODE END Includes */


- Overwrite definition of ``_write`` as:

  .. tabs::
     
     .. group-tab:: SWV

        .. code-block:: c
           :emphasize-lines: 2-9
        
           /* USER CODE BEGIN 0 */
           int _write(int file, char *data, int len)
           {
             for (int i = 0; i < len; ++i)
             {
               ITM_SendChar(data[i]);
             }
             return len;
           }
           /* USER CODE END 0 */

     .. group-tab:: USB

        .. code-block:: c
           :emphasize-lines: 2-6
          
           /* USER CODE BEGIN 0 */
           int _write(int file, char *data, int len)
           {
             CDC_Transmit_FS((uint8_t*)data, (uint16_t)len);
             return len;
           }
           /* USER CODE END 0 */

- Add code for sender as well as receiver.

  .. code-block:: c
     :emphasize-lines: 3-6, 10-18
     
     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
     #define SENDER // comment this line to make for receiver
     
     #ifdef SENDER
       char msg[] = "Hello World\n";
     #endif
     
       while (1)
       {
     #ifdef SENDER
         HAL_UART_Transmit(&huart2, (uint8_t *)msg, sizeof(msg), 1000);
         HAL_Delay(1000);
     #else
         char c;
         HAL_UART_Receive(&huart2, (uint8_t *)&c, sizeof(c), 0); // 0 means if no data is available, it will return immediately
         printf("%c", c);
     #endif
         /* USER CODE END WHILE */
     
         /* USER CODE BEGIN 3 */
       }
       /* USER CODE END 3 */

- Build and flash sender code to sending controller.

- Comment ``#define SENDER``. Build and flash the receiver code to receiving controller.



4. Connection
-------------

- Connect **TX pin** of sender to **RX pin** of receiver.

- Connect **GND** of both controllers together.



References
----------

References are from ``STM32 HAL Driver`` documentation.

.. function:: HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)

   Sends an amount of data in blocking mode.

   **Note:** When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
   the sent data is handled as a set of u16. In this case, `Size` must indicate the number
   of u16 provided through `pData`.

   :param huart: Pointer to a UART_HandleTypeDef structure that contains the configuration information for the specified UART module.
   :type huart: UART_HandleTypeDef*
   :param pData: Pointer to data buffer (u8 or u16 data elements).
   :type pData: const uint8_t*
   :param Size: Amount of data elements (u8 or u16) to be sent.
   :type Size: uint16_t
   :param Timeout: Timeout duration.
   :type Timeout: uint32_t
   :return: HAL status.
   :rtype: HAL_StatusTypeDef


.. function:: HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)

   Receives an amount of data in blocking mode.

   **Note:**
   
   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01), the received data is handled as a set of ``u16``. In this case, Size must indicate the number of ``u16`` available through ``pData``.

   :param huart: Pointer to a ``UART_HandleTypeDef`` structure that contains the configuration information for the specified UART module.
   :param pData: Pointer to the data buffer (u8 or u16 data elements).
   :param Size: Amount of data elements (u8 or u16) to be received.
   :param Timeout: Timeout duration.
   :return: HAL status.
   :rtype: HAL_StatusTypeDef
