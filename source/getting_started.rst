Getting Started
===============

.. toctree::
   :hidden:
   :glob:

   getting_started/installation
   getting_started/setup

.. contents:: Contents
   :depth: 2
   :local:


Introduction
------------

In this **Embedded Tutorials** section, I will guide you through programming **STM32 controllers**, **ESP32** and **Rashberry PI Pico**, sharing the techniques and approaches I commonly use." I will guide more on **STM32 controllers** from basic but not for others. I generally use **Arduino IDE** for programming **ESP32** and **Rashberry PI Pico**. I am not going to guide the basics of **Arduino programming**.

For **Arduino programming**, see `arduino documentation <https://docs.arduino.cc/>`__. I recommend to watch `New Arduino Tutorials by Paul McWhorter <https://youtube.com/playlist?list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&si=MG7z_3GhUvpTm6F_>`_ on ``YouTube``. Even you do not need hardware for learning **Arduino programming**. You can use `Tinkercad <https://www.tinkercad.com/>`__ for simulation.

For **extra tutorials**, I recommend `CONTROLLERSTECH <https://controllerstech.com/>`__ and `DeepBlueMbedded <https://deepbluembedded.com>`__.
   
Some devices, softwares, and programming languages going to be used:


Controllers
-----------

1. STM32 Controllers
^^^^^^^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: images/controllers/STM32F407G-DISC1_Blue.jpg
          :height: 300
          :alt: STM32F407VG-DISC1

          **STM32F407VG-DISC1**: STM32F407VGT6

     - .. figure:: images/controllers/bluepill.jpg
          :height: 300
          :alt: Blue Pill

          **Blue Pill**: STM32F103C8, STM32F103C6

.. attention::
   Original Blue Pill has **STM32F103C8** microcontroller. But in Nepal, it usually comes with **STM32F103C6** microcontroller.


2. ESP Controllers
^^^^^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: images/controllers/esp32_wroom.jpg
          :height: 300
          :alt: ESP32 WROOM32

          **ESP32 WROOM32**

     - .. figure:: images/controllers/nodemcu.jpg
          :height: 300
          :alt: NodeMCU

          **NodeMCU**: ESP8266


3. Raspberry Pi Controllers
---------------------------

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: images/controllers/pi_pico.jpg
          :height: 300
          :alt: PI PICO

          **Raspberry PI PICO**: RP2040

     - .. figure:: images/controllers/pi_pico_w.png
          :height: 300
          :alt: PI PICO W

          **Raspberry Pi PICO W**: RP2040 + CYW43439


4. Arduino Controllers
----------------------

.. list-table::
   :widths: 33 33 33
   :align: center
   :class: image-grid

   * - .. figure:: images/controllers/arduino_uno.jpg
          :height: 300
          :alt: Arduino UNO

          **Arduino UNO**

     - .. figure:: images/controllers/arduino_nano.jpg
          :height: 300
          :alt: Arduino NANO

          **Arduino NANO**

     - .. figure:: images/controllers/arduino_mega.jpg
         :height: 300
         :alt: Arduino MEGA

         **Arduino MEGA**

.. note::
   **Rashberry PI PICO W** is extension of **Rashberry PI PICO** with **Infenion CYW43439** connectivity chip.


Debuggers
---------

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: images/debuggers/stlink.jpeg
          :height: 300
          :alt: ST-Link V2 Duplicate

          **ST-Link V2**

     - .. figure:: images/debuggers/jlink-edu.jpeg
          :height: 300
          :alt: JLink Edu Mini

          **JLink Edu Mini**

.. Attention::
    The **ST-Link V2** shown above is duplicate. The original is shown below:

    .. image:: images/debuggers/stlink-original.jpeg
       :width: 300
       :align: center
       :alt: ST-Link V2 Original


Programming and Scripting Laguages
----------------------------------

.. list-table::
   :widths: 33 33 33
   :align: center
   :class: image-grid

   * - .. figure:: images/program_logos/c_logo.png
          :height: 150
          :alt: C

          **C**

     - .. figure:: images/program_logos/cpp_logo.png
          :height: 150
          :alt: C++

          **C++**

     - .. figure:: images/program_logos/python_logo.png
          :height: 150
          :alt: Python

          **Python**

   * - .. figure:: images/program_logos/makefile_logo.png
          :height: 100
          :alt: Make

          **Make**

     - .. figure:: images/program_logos/cmake_logo.png
          :height: 100
          :alt: CMake
   
          **CMake**

     - .. figure:: images/program_logos/bash_logo.png
          :height: 100
          :alt: Bash
 
          **Bash**
          

**Softwares and SDKs** are on `next <getting_started/installation.html>`_ installation guide.
