Highlights
==========

.. attention::

   **1**. This ST-Link V2 does not support ``SWV`` as there is no ``SWO`` pin. `Use USB instead of SWV <stm32_basics_tutorial/usb/usb_printf.html>`__.

   .. image:: images/debuggers/stlink.jpeg
      :width: 300
      :align: center
      :alt: stlink.jpeg


.. attention:: 

   | **2**. **CH34x USB devices** not pressent at ``/dev/tty*``?
   | Remove ``brltty`` package.

   .. code-block:: bash
      
      sudo apt autoremove brltty


.. tip::

   **3**. Remove burden of entering password every time while ``git clone`` and ``git push``. `Add SSH key to GitHub <getting_started/setup.html#ssh-setup>`__.


.. attention::

   | **4**. Building STM32 project using ``CMake`` does not generate binary file.
   | `You need to generate binary file <stm32_basics_tutorial/basic_setup/build_using_cmakelists.html#generate-binary-using-arm-none-eabi-objcopy>`__.


.. error::

   **5**. ``NRST`` pin of ST-Link is not connected to the ``NRST`` pin of the microcontroller but try to reset using ``st-flash`` command.

   .. code-block:: bash
    
      st-flash --reset write <your_binary_filename>.bin 0x8000000

   Remove ``--reset`` and reset manually or common ``NRST`` pins. 


.. danger::

   **6**. You must write you code inside comment block. Begin and End are specified by ``/* USER CODE BEGIN x */`` and ``/* USER CODE END x */``. Here ``x`` is the number. If you write outside this block, your code will be lost when you regenerate the code using CubeMX.


.. attention::

   | **7**. Have to disconnect ``USB`` after pressing ``reset`` button of STM32?
   | `You need to add pretreatment <stm32_basics_tutorial/usb/usb_reset_issue.html>`__.


.. attention::

   | **8**. Using ``cat`` command to see ``serial`` data from ``USB``?
   | Make sure boudrate of Serial is ``115200`` or use ``Arduino Serial Monitor``, ``PuTTY`` or other software.


.. warning::

   **9**. STM32F407VG-DISC1 default UART1 TX pin (PA9) does not work properly when the USB OTG is used because PA9 pin is also used for USB OTG. For more information, `see the schematic of the board <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/schematic_pack/mb997-f407vgt6-b02_schematic.pdf&ved=2ahUKEwjtzuKMxu6IAxVmR2wGHYkYAl8QFnoECBsQAQ&usg=AOvVaw0S1_y_ksxURXPd02EFhSfS>`_.


.. attention::

   | **10**: UART stops receiving but works fine after reset?
   | See `UART Issues <stm32_basics_tutorial/uart/uart_issues.html#uart-stops-receiving-but-works-fine-after-reset>`__.


.. note::

   **11**. Formula for **Frequency of PWM**:

   .. math::

      f_{\text{PWM}} = \frac{f_{\text{TIM}}}{\text{(ARR + 1) * (PSC + 1)}}

   Use calculator for `frequency <stm32_basics_tutorial/timer/pwm.html#changing-the-frequency-of-pwm>`__ and also for `ARR <stm32_basics_tutorial/timer/pwm.html#_arr_calculator>`__.

   
.. note::

   **12**. ``Open drain`` encoders need pullup resistors. For ``3V3`` VDD, ``4K7`` pull up resistors are better. For ``5V`` VDD, ``10K`` pull up resistors are better. 


.. caution::

   **13**. **STM32F407VG-DISC1 TIM1** gives problem in high speed encoder reading if cable length is long. It is better to use other timers for high speed encoder reading.

.. tip::

   **14**. If you timer as **counter** like **frequncy counter** or **encoder**. It is better to keep **ARR** value to maximum i.e. `65535` for 32-bit.


.. important::

   **15**. To print floating point, add ``-u _printf_float`` flag to ``LDFLAGS`` in **Makefile**.

   .. code-block:: makefile

      LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -u _printf_float


.. caution::

   **16**. If ``PWM pin`` is pulled up, it sends logic high at reset. So make sure not to use pulled up pins for ``PWM`` to control **motors**. But you can use the pulled up pins to control **servo motors**. **STM32F407VG-DISC1** board have many pulled up pins as it contains many peripherals. You can check them using **multimeter** under reset. To hold the reset, use **STM32CubeProgrammer**. If you connect it and open ``SWV``, it is under reset uintill you press ``START``. 


.. attention::
   
   **17**. ``SWV`` does not work in **STM32F407VG-DISC1** board if you use ``PB3`` pin because it is connected to ``SWO`` pin of **ST-Link**.


.. warning::

   **18**. Many bluepills found in Nepal have ``STM32F103C6T6`` microcontroller and have only 32KB flash memory. Using ``USB`` can overflow the flash memory.


.. important::
   
   **19**. **ITM** uses **SWO**, so select ``Debug`` option as ``Trace Asynchronous SW`` in **STM32CubeMX** configuration.