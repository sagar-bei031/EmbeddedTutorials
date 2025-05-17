Arduino Basics Tutorial
=======================

.. contents:: Contents
   :depth: 2
   :local:
   


Introduction
------------

``Arduino`` is an open-source electronics platform based on easy-to-use hardware and software. It consists of a microcontroller board, which can be programmed to sense and control the physical world. The ``Arduino IDE`` is used to write and upload code to the board. Well ``Arduino IDE`` is not limited to ``Arduino`` boards only, it can be used to program other microcontrollers as well.

Specifications for Arduino UNO R3
---------------------------------

.. list-table::
   :header-rows: 1

   * - **Specification**
     - **Details**
   * - Microcontroller
     - ATmega328P
   * - Processor
     - 8-bit AVR
   * - Clock Speed
     - 16 MHz
   * - I/O Voltage
     - 5 V
   * - Power Input Voltage (VIN Pin)
     - 7 V - 12 V (Typical 9 V)
   * - DC Current per I/O Pin
     - 20 mA
   * - Memory
     - 2KB SRAM, 32KB FLASH, 1KB EEPROM


Guidelines
----------

Tinkercad
~~~~~~~~~

You do not need to have ``Arduino`` board physically. You can use software platforms like ``Tinkercad``. or ``Proteus`` to simulate the code. The easiest and free one is ``Tinkercad``. You can create a free account and start using it :newtab:`here <https://www.tinkercad.com/>`.

Youtube Tutorials
~~~~~~~~~~~~~~~~~

There are many arduino tutorials available online. We recommend you a youtube playlist, :newtab:`New Arduino Programming by Paul MCWhorter<https://youtube.com/playlist?list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&si=uKKVvJbOPNuGyMVv>`. For real beginners, complete all the videos and use ``Tinkercad``. Some components may not be available in ``Tinkercad``. In that case, you can directly use physical components if available.

.. raw:: html

    <div style="position: relative; width: 100%; padding-bottom: 56.25%; height: 0; margin-bottom: 1em;">
        <iframe 
            src="https://www.youtube.com/embed/videoseries?si=qrLBoDZGhJ-RTVfk&amp;list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP"
            title="YouTube video player"
            style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"
            frameborder="0"
            allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share"
            referrerpolicy="strict-origin-when-cross-origin"
            allowfullscreen>
        </iframe>
    </div>

Knowledge Check
---------------

After completing the videos, you have to be able to do the following:

- Using resistors and color coding of resistors
- Breadboard Wiring
- Arduino Programming
    - Digital Input/Output (LED, push button) and External Interrupts (rising, falling)
    - Analog Input/Output (ADC, PWM)
    - Serial Communication (UART)
    - Using Libraries
- Actuator Interfacing
    - DC Motor
    - Servo Motor
    - Stepper Motor
- Using Sensors
    - Light Sensor (LDR)
    - Ultrasonic Sensor
    - Temperature and Humidity Sensor (DHT11/DHT22)
- 16x2 LCD Interfacing
- Using multimeter
- Using Oscilloscope