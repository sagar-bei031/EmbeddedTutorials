UART with Interrupt
===================

In interrupt mode, the UART hardware generates an interrupt signal to the CPU when data is arrived (RX interrupt), data transmission is completed (TX interrupt) and even there are errors like parity error, framing error etc. It reduces the amount of time that we have to wait for data to be transmitted or received.



1. CubeMX Configuration
-----------------------

- Open CubeMX and `generate_basic_code <../../getting_started/basic_setup/generate_basic_code.html>`_ with:

  - microcontroller: ``stm32f407vgt6`` or board: ``STM32F407VG-DISC1``
  - project name: ``uart_interrupt``
  - Toolchain/IDE: ``Makefile``

- Move to STM32CubeMX ``Pinout and Congiguration``. From ``Categories``, select ``Connectivity > USART2``. Change ``mode`` to ``Asynchronous`` mode.

- Under ``Configuration > NVIC Settings``, enable ``USART2 global interrupt``.

.. image:: images/uart_interrupt.webp
   :width: 600
   :align: center
   :alt: usart2_polling

- Generate code and open the project.



2. Code to Send and Receive Data using UART Interrupt
-----------------------------------------------------

- Navigate to ``Core > Src`` and open ``main.c``. 

- Include ``stdio.h`` for printf to print received data.

  .. code-block:: c
  
     /* USER CODE BEGIN Includes */
     #include <stdio.h>
     /* USER CODE END Includes */

- Overwrite definition of ``_write`` as:

  .. code-block:: c
  
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

- Add global variable to store received data.

  .. code-block:: c
  
     /* USER CODE BEGIN PV */
     char c;
     /* USER

- Add code for sending as well as receiving in ``main()``.

  .. code-block:: c
     
     /* USER CODE BEGIN 2 */
     char msg[] = "Hello from controller 1\n";

     HAL_UART_Receive_IT(&huart2, (uint8_t *)&c, sizeof(c)); // Start receiving
     /* USER CODE END 2 */

     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
     uint32_t last_transmit = 0;
     while (1)
     {
       if (HAL_GetTick() - last_transmit > 1000)
       {
         HAL_UART_Transmit_IT(&huart2, (uint8_t *)msg, sizeof(msg));
         last_transmit = HAL_GetTick();
       }

       if (!(HAL_UART_GetState(&huart2) & HAL_UART_STATE_BUSY_RX))
       {
        HAL_UART_Receive_IT(&huart2, (uint8_t *)&c, sizeof(c)); // Start receiving in case of no reception
       }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */

- Add callback function for UART RX interrupt just above ``main()``.

  .. code-block:: c
  
     void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
     {
       if (huart->Instance == USART2)
       {
         printf("%c", c);
         HAL_UART_Receive_IT(&huart2, (uint8_t *)&c, sizeof(c)); // Receive again
       }
     }
     
     /* USER CODE END 0 */

- Build and flash the code to both controllers.



3. Connection
-------------

- Connect **TX pin** of sender to **RX pin** of receiver.

- Connect **GND** of both controllers together.



References
----------

References are from ``STM32 HAL Driver`` documentation.

.. function:: HAL_StatusTypeDef HAL_UART_Transmit_IT(huart, pData, Size)

   Sends an amount of data in non-blocking mode.

   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
   the sent data is handled as a set of u16. In this case, Size must indicate the number
   of u16 provided through pData.

   :param huart: Pointer to a UART_HandleTypeDef structure that contains
                 the configuration information for the specified UART module.
   :param pData: Pointer to data buffer (u8 or u16 data elements).
   :param Size:  Amount of data elements (u8 or u16) to be sent.
   :return: HAL status.


.. function:: HAL_StatusTypeDef HAL_UART_Receive_IT(huart, pData, Size)

   Receives an amount of data in non-blocking mode.

   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
   the received data is handled as a set of u16. In this case, Size must indicate the number
   of u16 available through pData.

   :param huart: Pointer to a UART_HandleTypeDef structure that contains
                 the configuration information for the specified UART module.
   :param pData: Pointer to data buffer (u8 or u16 data elements).
   :param Size:  Amount of data elements (u8 or u16) to be received.
   :return: HAL status.



.. note::

   **Interrupt mode IO operation**

   - Send an amount of data in non-blocking mode using ``HAL_UART_Transmit_IT()``.
   - At the end of transmission, the callback ``HAL_UART_TxCpltCallback`` is executed,
     allowing the user to add custom code by customizing this function pointer.
   - Receive an amount of data in non-blocking mode using ``HAL_UART_Receive_IT()``.
   - At the end of reception, the callback ``HAL_UART_RxCpltCallback`` is executed,
     allowing the user to add custom code by customizing this function pointer.
   - In case of transfer error, the function ``HAL_UART_ErrorCallback()`` is executed,
     allowing the user to add custom code by customizing this function pointer.
