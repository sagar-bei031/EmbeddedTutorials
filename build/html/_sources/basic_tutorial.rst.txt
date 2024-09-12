Basic Tutorial
==============

In this **Embedded Tutorial**, you will learn about **Embedded programming**, **Kinematics**, **Control Algorithm**, **filters**, **error detection and correction**, some useful maths and other many things. There are lots of topic to learn in this subject. Being interested in **Electronics**, it is essential to have knowledge about it.

For this tutorial, we are using **STM32F407VGT6** microcontroller. You can use any other microcontroller as well. The basic concepts are same for all microcontrollers. Before we works on the microcontroller, we need to know about it.


**About STM32F407VGT6**:

.. image:: images/stm32f407vgt6.jpg
   :width: 300
   :align: center
   :alt: STM32F407VGT6

.. image:: images/stm32f407vg-disc1.avif
   :width: 300
   :align: center
   :alt: STM32F407VG-DISC1

- Processor: ARM-Cortex M4
- Word length: 32 bit
- Max frequency: 168MHz
- Type: High performance
- Total pin count: 100
- Typical operating voltage: 3.3V 
- Power supply voltage: 1.8V-3.6V (Typical 3V3)
- Max power consumption: 240mA
- Max I0 pins consumption: 25mA Each
- IO pin voltage tolerant: 5V
- RAM: 192KB
- Flash: 1MB

You can find its features on `STM32CubeMX`. You also can find datasheet, reference mannual, schematic, footprints and other resources there.

See:

- `naming convenction <https://www.digikey.com/en/maker/tutorials/2020/understanding-stm32-naming-conventions>`_ 
- `datasheet <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/datasheet/dm00037051.pdf&ved=2ahUKEwi5uNulx72IAxVR1TgGHfcYAmIQFnoECBQQAQ&usg=AOvVaw07P8BbeoTlMpZCNdsHv1OP>`_
- `reference mannual <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf&ved=2ahUKEwiS2sXckL2IAxW3_aACHV3sIHsQFnoECBoQAQ&usg=AOvVaw2x8tbTRz8d9PfqXBk3qZ74>`_
- `documentation <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series/documentation.html&ved=2ahUKEwiS2sXckL2IAxW3_aACHV3sIHsQFnoECBwQAQ&usg=AOvVaw318Y8lno9LsAwj77l78ngk>`_


.. toctree::
   :maxdepth: 2
   :caption: Contents:

   basic_tutorial/gpio
   basic_tutorial/usb
   basic_tutorial/serial_wire


.. basic_tutorial/printf
.. basic_tutorial/debug
.. basic_tutorial/cpp_setup
.. basic_tutorial/timer
.. basic_tutorial/uart
.. basic_tutorial/i2c