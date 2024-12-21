Encoder
=======

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

Rotating encoder is a input device that provides information about the direction and amount of rotation of a shaft. It has minimum two outputs, A and B, which are 90 degrees out of phase. The encoder generates a pulse each time it is rotated by a certain amount. The direction of rotation can be determined by the order of the pulses on the A and B channels.

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: images/hall_encoder.jpeg
          :height: 300
          :align: center
          :alt: Hall Encoder

          **Magnetic Encoder**
   
     - .. figure:: images/yumo_encoder.webp
          :height: 300
          :align: center
          :alt: Yumo Encoder
    
          **Open Drain Rotary Encoder**          

.. image:: images/encoder_pulse.png
   :width: 80%
   :align: center
   :alt: Encoder Channel Waveform

.. note::

    Above **magnetic encoder** does not need pull up resistors as it has **built-in pull up resistors**. But the **open drain encoder** needs **pull up resistors**. For ``3V3`` VDD, ``4K7`` pull up resistors are better. For ``5V`` VDD, ``10K`` pull up resistors are better. 


2. CubeMX Configuration
-----------------------

- Open CubeMX and `generate basic code <../basic_setup/generate_basic_code.html>`__ with:

  - microcontroller: ``stm32f407vgt6`` or board: ``STM32F407VG-DISC1``
  - project name: ``microsecond_tick``
  - Toolchain/IDE: ``Makefile``

- Go to ``Pinout and Congiguration > Timers > TIM1``. Select ``Encoder Mode`` for **Combined Channels**.

- Under ``Parameter Settings > Encoder``, change the **Encoder Mode** to ``Encoder Mode T1 and T2``. It is better to keep **AutoReload Register** value to ``65535``.

- Generate Code.

  .. image:: images/encoder_conf.webp
     :width: 100%
     :align: center
     :alt: Encoder Configuration


3. Code to Read Encoder Count
-----------------------------

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

- Add code to read encoder count.
    
    .. code-block:: c
      
       /* USER CODE BEGIN 2 */
       HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
       uint32_t encoder_count = 0;
       /* USER CODE END 2 */
       
       /* Infinite loop */
       /* USER CODE BEGIN WHILE */
       while (1)
       {
         encoder_count = htim1.Instance->CNT;
         // You also can use:
         // encoder_count = __HAL_TIM_GET_COUNTER(&htim1);
 
          printf("Count: %lu\n", encoder_count);
 
          HAL_Delay(100);
       }
       /* USER CODE END WHILE */


4. Observe Output
-----------------

- Connect encoder A and B channels to ``TIM1_CH1`` pin and ``TIM1_CH2`` pin respectively.

- Open ``STM32CubeProgrammer`` and see count on ``SWV`` by rotating encoder. If you used USB, see on terminal or serial monitor.


.. caution::

   **STM32F407VG-DISC1 TIM1** gives problem in high speed encoder reading if cable length is long. It is better to use other timers for high speed encoder reading.


**Assignment**: Calculate RPM.
