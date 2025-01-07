UART with DMA
=============

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

Direct Memory Access (DMA) is very useful feature in microcontrollers. It allows data transfer between peripherals and memory without CPU intervention. This is very useful in UART communication where data is received and transmitted continuously. In this tutorial, we will learn how to use UART with DMA.


2. CubeMX Configuration
-----------------------

- Open CubeMX and `generate basic code <../basic_setup/generate_basic_code.html>`_ with:

  - microcontroller: ``stm32f407vgt6`` or board: ``STM32F407VG-DISC1``
  - project name: ``usb_polling``
  - Toolchain/IDE: ``Makefile``

- Move to STM32CubeMX ``Pinout and Congiguration``. From ``Categories``, select ``Connectivity > USART2``. Change ``mode`` to ``Asynchronous`` mode.

- Under ``Configuration > DMA Settings``, add ``USART2_RX`` and ``USART2_TX`` DMA request.

- Under ``Configuration > NVIC Settings``, enable ``USART2 global interrupt``.

.. image:: images/uart_dma.webp
   :width: 100%
   :align: center
   :alt: usart2_dma

- Generate code and open the project.



3. Code to Send and Receive Data using UART Interrupt
-----------------------------------------------------

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

- Add global variable to store received data.

  .. code-block:: c
  
     /* USER CODE BEGIN PV */
     char c;
     /* USER

- Add code for sending as well as receiving in ``main()``.

  .. code-block:: c
     :emphasize-lines: 2-5, 12-22
     
     /* USER CODE BEGIN 2 */
     char msg[] = "Hello from controller 1\n";
     uint32_t last_transmit = 0;

     HAL_UART_Receive_DMA(&huart2, (uint8_t *)&c, sizeof(c)); // Start receiving
     /* USER CODE END 2 */

     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
     while (1)
     {
       if (HAL_GetTick() - last_transmit > 1000)
       {
         HAL_UART_Transmit_DMA(&huart2, (uint8_t *)msg, sizeof(msg));
         last_transmit = HAL_GetTick();
       }

       if (!(HAL_UART_GetState(&huart2) & HAL_UART_STATE_BUSY_RX))
       {
        HAL_UART_Receive_DMA(&huart2, (uint8_t *)&c, sizeof(c)); // Start receiving in case of no reception
       }
     /* USER CODE END WHILE */
 
     /* USER CODE BEGIN 3 */
     }
     /* USER CODE END 3 */

- Add callback function for UART RX DMA just above ``main()``.

  .. code-block:: c
     :emphasize-lines: 1-8
  
     void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
     {
       if (huart->Instance == USART2)
       {
         printf("%c", c);
         HAL_UART_Receive_DMA(&huart2, (uint8_t *)&c, sizeof(c)); // Receive again
       }
     }
     
     /* USER CODE END 0 */

- Build and flash the code to both controllers.



4. Connection
-------------

- Connect **TX pin** of sender to **RX pin** of receiver.

- Connect **GND** of both controllers together.



References
----------

References are from ``STM32 HAL Driver`` documentation.

.. function:: HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)

   Sends an amount of data in DMA mode.

   **Notes**:  
   - When UART parity is not enabled (`PCE = 0`) and Word Length is configured to 9 bits (`M1-M0 = 01`), the sent data is handled as a set of `u16`. In this case, *Size* must indicate the number of `u16` provided through *pData*.

   :param huart: Pointer to a `UART_HandleTypeDef` structure containing configuration information for the specified UART module.
   :param pData: Pointer to data buffer (contains `u8` or `u16` data elements).
   :param Size: Number of data elements (`u8` or `u16`) to be sent.
   :returns: HAL status.
   :rtype: HAL_StatusTypeDef


.. function:: HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)

   Receives an amount of data in DMA mode.

   **Notes**:  
   - When UART parity is not enabled (`PCE = 0`) and Word Length is configured to 9 bits (`M1-M0 = 01`), the received data is handled as a set of `u16`. In this case, *Size* must indicate the number of `u16` available through *pData*.
   - When the UART parity is enabled (`PCE = 1`), the received data contains the parity bit.

   :param huart: Pointer to a `UART_HandleTypeDef` structure containing configuration information for the specified UART module.
   :param pData: Pointer to data buffer (contains `u8` or `u16` data elements).
   :param Size: Number of data elements (`u8` or `u16`) to be received.
   :returns: HAL status.
   :rtype: HAL_StatusTypeDef
