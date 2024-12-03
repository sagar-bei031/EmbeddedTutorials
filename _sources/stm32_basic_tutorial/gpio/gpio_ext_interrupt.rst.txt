Previously, we have completed `gpio input <gpio_input.html>`_.

GPIO External Interrupt
=======================

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
--------------- 

External interrupt is used to read the input pin asynchronously. It is used to read the input pin without polling the pin. The controller will execute the code only when the pin state changes.

Interrupt can be generated on the rising edge, falling edge, or both edges. It can also be generated on the low level or high level.

In this tutorial, we will see how to use external interrupt to detect rising edge signal on pin ``PA0`` i.e. button press and use it to toggle led.



2. CubeMX Configuration
-----------------------

- Open the ``STM32CubeMX``, update pin ``PA0`` to ``GPIO_EXTI0``.

- From ``Pinout & Configuration``, go to ``GPIO`` and under ``NVIC`` tab, enable ``EXTI line0 intereupt``.

 .. image:: images/gpio_exti_enable.webp
    :width: 600
    :align: center
    :alt: gpio_exti_enable

- Under ``GPIO`` tab, select ``PA0-WKP`` list. From ``PA0-WKP Configuration``, check ``GPIO Mode`` to ``External Interrupt Mode with Rising edge trigger detection``.

 .. image:: images/gpio_exti_rising_edge.webp
    :width: 600
    :align: center
    :alt: gpio_exti_rising_edge

- Generate code.



3. Code to Toggle LED using External Interrupt
----------------------------------------------

- Open project folder. Navigate to ``Core/Src/main.c``. Add ``HAL_GPIO_EXTI_Callback`` function above the ``main`` function. 

  .. code-block:: c
  
     /* USER CODE BEGIN 0 */
     void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
     {
       // Toggle green led on pin PD12 when button is pressed.
       if (GPIO_Pin == GPIO_PIN_0)
       {
         HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
       }
     }
     /* USER CODE END 0 */

.. note::

  ``HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)`` is a callback function which is called when the external interrupt is generated. It is used to handle the interrupt. It is weakly defined inside ``HAL Driver``.

- Update the ``while`` block of the ``main`` function to show processor can do other job simultaneously.

  .. code-block:: c

     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
     while (1)
     {
       // Toggle Orage Led Continously
       HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
       HAL_Delay(100);
       /* USER CODE END WHILE */
   
       /* USER CODE BEGIN 3 */
     }
     /* USER CODE END 3 */

- Build and flash the code.



4. Observation
--------------

- Orage led on pin ``PD13`` blinking continuously.
- Pressing the user button on pin ``PA0``,  the green led on pin ``PD12`` toggles.



.. note::

   It is possible that pressing the button toggles the led multiple times. This is because the button is mechanical and it bounces. We will see how to debounce the button in the later tutorial.
