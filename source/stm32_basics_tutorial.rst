STM32 Basics Tutorial
=====================

.. contents:: Contents
   :depth: 2
   :local:


Introduction
------------

In this **STM32 Basics Tutorial**, you will learn to use **GPIO**, **USB**, **SWD**, **UART**, **Timer** and other peripherals of STM32 microcontroller. This tutorial is for beginners who are new to STM32 microcontroller. We will use **STM32CubeMX** to generate the code and **arm-none-eabi-gcc** to compile and **stlink-tools** or **STM32CubeProgrammer** to flash the code. See the `installation <getting_started/installation.html>`__.

For this tutorial, we are using **STM32F407VGT6** microcontroller used in ``STM32F407VG-DISC1`` board. You can use any other microcontroller as well. The basic concepts are same for all microcontrollers. Before we works on the microcontroller, we need to know about it.


About STM32F407VGT6
-------------------

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: images/controllers/stm32f407vgt6.jpg
          :height: 300
          :align: center
          :alt: STM32F407VGT6

          **STM32F407VGT6**
   
     - .. figure:: images/controllers/stm32f407vg-disc1.avif
          :height: 300
          :align: center
          :alt: STM32F407VG-DISC1

          **STM32F407VG-DISC1**


.. list-table::
   :header-rows: 1

   * - **Specification**
     - **Details**
   * - Processor
     - ARM Cortex-M4
   * - Word length
     - 32-bit
   * - Max frequency
     - 168 MHz
   * - Type
     - High performance
   * - Total pin count
     - 100
   * - Typical operating voltage
     - 3.3 V
   * - Power supply voltage
     - 1.8 V - 3.6 V (Typical 3.3 V)
   * - Max power consumption
     - 240 mA
   * - Max I/O pins consumption
     - 25 mA each
   * - I/O pin voltage tolerant
     - 5 V
   * - RAM
     - 192 KB
   * - Flash
     - 1 MB


You can find its features on `STM32CubeMX`. You also can find datasheet, reference mannual, schematic, footprints and other resources there.


.. seealso::

   - `Naming convenction <https://www.digikey.com/en/maker/tutorials/2020/understanding-stm32-naming-conventions>`__ 

   - `User mannual <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/user_manual/um1472-discovery-kit-with-stm32f407vg-mcu-stmicroelectronics.pdf&ved=2ahUKEwjhv-7qubmKAxWOzzgGHfIOBZgQFnoECB8QAQ&usg=AOvVaw2bVxKBN4t1kKDB9FXzgrq7>`__.

   - `Schematic <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/schematic_pack/mb997-f407vgt6-b02_schematic.pdf&ved=2ahUKEwi9jdGcurmKAxWT3jgGHYmPAqUQFnoECBsQAQ&usg=AOvVaw0S1_y_ksxURXPd02EFhSfS>`__.

   - `Datasheet <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/datasheet/dm00037051.pdf&ved=2ahUKEwi5uNulx72IAxVR1TgGHfcYAmIQFnoECBQQAQ&usg=AOvVaw07P8BbeoTlMpZCNdsHv1OP>`__

   - `Reference mannual <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf&ved=2ahUKEwiS2sXckL2IAxW3_aACHV3sIHsQFnoECBoQAQ&usg=AOvVaw2x8tbTRz8d9PfqXBk3qZ74>`__

   - `Documentation <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series/documentation.html&ved=2ahUKEwiS2sXckL2IAxW3_aACHV3sIHsQFnoECBwQAQ&usg=AOvVaw318Y8lno9LsAwj77l78ngk>`__


About STM32F103C8T6
-------------------

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: images/controllers/stm32f103c8.webp
          :height: 300
          :align: center
          :alt: STM32F103C8

          **STM32F103C8**
   
     - .. figure:: images/controllers/bluepill.jpg
          :height: 300
          :align: center
          :alt: Bluepill

          **Bluepill**


.. list-table::
   :header-rows: 1

   * - **Specification**
     - **Details**
   * - Processor
     - ARM Cortex-M3
   * - Word length
     - 32-bit
   * - Max frequency
     - 72 MHz
   * - Type
     - Mainstream performance
   * - Total pin count
     - 48
   * - Typical operating voltage
     - 3.3 V
   * - Power supply voltage
     - 2.0 V - 3.6 V
   * - Max power consumption
     - 34 mA at 72 MHz
   * - Max I/O pins consumption
     - 25 mA each
   * - I/O pin voltage tolerant
     - 5 V
   * - RAM
     - 20 KB
   * - Flash
     - 64 KB (some variant have 128 KB)

.. warning::
   Many bluepill found in Nepal uses ``STM32F103C6T6`` microcontroller. It is less powerful than ``STM32F103C8T6``.


.. toctree::
   :maxdepth: 2
   :caption: Contents:

   stm32_basics_tutorial/basic_setup
   stm32_basics_tutorial/gpio
   stm32_basics_tutorial/usb
   stm32_basics_tutorial/swd
   stm32_basics_tutorial/uart
   stm32_basics_tutorial/timer
