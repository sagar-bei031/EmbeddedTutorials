UART Issues
===========

1. UART stops receiving but works fine after reset.
---------------------------------------------------

It is caused if interrupt is not handled properly or receiving flow goes out of sync. To resolve this issue, you can either use `HAL_UART_ErrorCallback` or check DMA status or both.

1.1. Use **HAL_UART_ErrorCallback**:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The callback function ``HAL_UART_ErrorCallback`` is called when an error occurs. You can use this callback to handle the error. For example:

.. code-block:: c

   void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
   {
     if (huart->Instance == huart2.Instance)
     {
         // Handle error
         HAL_UART_Receive_DMA(&huart2, (uint8_t *)RxBuffer, RXBUFFERSIZE);
     }
     else if (huart->Instance == joystick.uart.get_uart_instance())
     {
         // Handle error by initializing the joystick again
         joystick.init();
     }
   }

1.2. Check DMA status:
^^^^^^^^^^^^^^^^^^^^^^
You can check the DMA status to ensure that the DMA is working properly. While receiving data, the DMA status is ``HAL_DMA_STATE_BUSY``. If it is not, you can reinitialize the DMA by triggering DMA receive again inside looping function

.. code-block:: c

   void run_robot()
   {
      if (huart->hdmarx->State != HAL_DMA_STATE_BUSY)
      {
          HAL_UART_Receive_DMA(&huart2, (uint8_t *)RxBuffer, RXBUFFERSIZE);
      }
      else if (joystick.uart.hdmarx->State != HAL_DMA_STATE_BUSY)
      {
          joystick.init();
      }
    }


2. **HAL_UART_TxCpltCallback** is not called.
---------------------------------------------
It is neccessary to enable the UART TX interrupt. If the interrupt is not enabled, the callback function will not be called. You can use ``STM32CubeMX`` to enable the UART TX interrupt.

- Open your project on ``STM32CubeMX``.
- Go to ``Comminication > USARTx > Configuration > NVIC Settings``.
- Enable ``USARTx global interrupt``.


3. Receiving data even pins are not connected.
----------------------------------------------
It is caused by the noise in the circuit like:

- Soldering flux not cleaned properly.
- Touching the pins with fingers.
- UART wires are too close to the power or actuator wires.
