SWD Printf
==========

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

SWD also can be used to print data. But we cannot get them normally. We need speacial program to see which is ``Serial Wire Viewer (SWV)``. ``STM32CubeProgrammer`` has  SWV. Download it from `installation <../../getting_started/installation.html>`_.



2. Overwrite Definition of printf
---------------------------------

* `Generate baisc code <../basic_setup/generate_basic_code.html>`_.

* Create a new file ``printf_conf.c`` in ``Core/Src`` folder.

* Add the following code to the file:
  
  .. code-block:: c
     
     #include "stm32f4xx_hal.h"

     int _write(int file, char *data, int len)
     {
         for (int i = 0; i < len; ++i)
         {
             ITM_SendChar(data[i]);
         }
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
     /* USER CODE END Includes */


* Update ``main`` function to print "Hello World" over SWD.

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

* Build and flash.



5. Open SWV on STM32CubeProgrammer
----------------------------------

* Open ``STM32CubeProgrammer``.

* Connect your microcontroller to your PC using USB cable through ``ST-Link``.

* Click on ``Connect``.

* Click on ``SWV``.

* Set ``Core Clock`` to the microcontroller clock frequency configured in ``STM32CubeMx``. It is ``168MHz`` in this case.

* Click on ``Start``.



You can see the message "Hello World" on the ``SWV`` continously.
