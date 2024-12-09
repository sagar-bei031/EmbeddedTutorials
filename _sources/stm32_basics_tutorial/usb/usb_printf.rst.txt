`previous <usb_cdc.html>`_

Printf over USB
===============

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

We cannot understand non character data type after printed on screen. In order to see them clearly, we need to first convert them to ``ASCII`` using ``snprintf`` function. Rather than using ``CDC_Transmit_FS``, we can overwrite the definition of ``printf`` function to print on USB neatly.



2. Overwrite Definition of printf
---------------------------------

* Create a new file ``printf_conf.c`` in ``Core/Src`` folder.

* Add the following code to the file:
  
  .. code-block:: c
     
     #include "stm32f4xx_hal.h"
     #include "usbd_cdc_if.h"
     
     int _write(int file, char *data, int len)
     {
         CDC_Transmit_FS((uint8_t*)data, (uint16_t)len);
         return len;
     }



3. Update Makefile
------------------

* Add ``printf_conf.c`` to ``Makefile > C_SOURCES``.

  .. code-block:: none
  
     C_SOURCES = \
     ... \
     ... \
     Core/Src/printf_conf.c

* Add ``-u _printf_float`` flag to ``LDFLAGS``. This is for floating point support.

  .. code-block:: makefile
     
     LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -u _printf_float



4. Update main.c
----------------

* Open ``Core > Src > main.c``. Add ``stdio.h`` header.

  .. code-block:: c

     /* Private includes ----------------------------------------------------------*/
     /* USER CODE BEGIN Includes */
     #include <stdio.h>
     #include "usbd_cdc_if.h"
     /* USER CODE END Includes */

* Update ``main`` function to print "Hello World" over USB.

  .. code-block:: c
     
     /* USER CODE BEGIN 2 */
     uint32_t n = 0;
     /* USER CODE END 2 */      
     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
     while (1)
     {
       printf ("Hello World! %lu\n", n++);
       HAL_Delay(100);
       /* USER CODE END WHILE */      
       /* USER CODE BEGIN 3 */
     }
     /* USER CODE END 3 */



Now you can build and flash the code. See the output on ``terminal`` or ``Serial Monitor`` as `previous <usb_cdc.html>`_.



References
----------

References are from ``CMSIS`` documentation.

.. function:: uint32_t ITM_SendChar(uint32_t ch)

   ITM Send Character.

   **Details**:  
   - Transmits a character via the ITM channel 0.  
   - Just returns if no debugger is connected that has booked the output.  
   - Is blocking if a debugger is connected, but the previous character sent has not been transmitted.

   :param uint32_t ch: Character to transmit.
   :returns: The transmitted character.
   :rtype: uint32_t
