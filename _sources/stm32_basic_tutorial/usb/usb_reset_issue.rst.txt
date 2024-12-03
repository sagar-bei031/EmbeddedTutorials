USB Reset Issue
===============

After reseting the microcontroller, the USB connection is lost. This is because the USB connection is not re-initialized after reset. But in some cases, the receiver can get data and need to turn off and on.

To solve this issue, we need to re-initialize the USB connection after reset. We can do this by adding pretreatement code inside ``MX_USB_DEVICE_Init`` function of ``USB_DEVICE/App/usb_device.c``.

.. code-block:: c

   /* USER CODE BEGIN USB_DEVICE_Init_PreTreatment */
   /* Rendering hardware reset harmless (no need to replug USB cable): */
   GPIO_InitTypeDef GPIO_InitStruct = {0};
   
   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
   
   /*Configure GPIO pin : PA12, a.k.a. USB_DP */
   GPIO_InitStruct.Pin = GPIO_PIN_12;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
   
   HAL_Delay(5);
   /* Hardware reset rendered harmless! */
   /* USER CODE END USB_DEVICE_Init_PreTreatment */


.. warning::
   
   Make sure, the above pretreatement code is not creating any problem. Generally we do not use it for discovery board but use it for bluepill board.
