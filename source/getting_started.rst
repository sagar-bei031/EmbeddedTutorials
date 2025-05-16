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

Before we start, it is important to understand the concepts of **hardware** and **software**. **Hardware** refers to the electronic and mechanical components of a system.
**Software** is a combination of instructions, programs, data, and documentation used to program and perform specific tasks. An **embedded system** is a combination of both **hardware** and **software**, designed to perform a specific task. The hardware and software used in embedded systems are task-specific. Commonly, microcontrollers are used in embedded systems due to their programmability and ease of use. Programs are written specifically for the microcontroller and are uploaded using a device programmer.

Let’s visually introduce some of the controllers and tools we will be using in this tutorial.


Controllers
-----------

1. STM32 Controllers
^^^^^^^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: _static/images/controllers/STM32F407G-DISC1_Blue.jpg
          :height: 300
          :alt: STM32F407VG-DISC1

          **STM32F407VG-DISC1**: STM32F407VGT6

     - .. figure:: _static/images/controllers/bluepill.jpg
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

   * - .. figure:: _static/images/controllers/esp32_wroom.jpg
          :width: 300
          :alt: ESP32 WROOM32

          **ESP32 WROOM32**

     - .. figure:: _static/images/controllers/nodemcu.jpg
          :width: 300
          :alt: NodeMCU

          **NodeMCU**: ESP8266


3. Raspberry Pi Controllers
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: _static/images/controllers/pi_pico.jpg
          :height: 300
          :alt: PI PICO

          **Raspberry PI PICO**: RP2040

     - .. figure:: _static/images/controllers/pi_pico_w.jpg
          :height: 300
          :alt: PI PICO W

          **Raspberry Pi PICO W**: RP2040 + CYW43439


4. Arduino Controllers
^^^^^^^^^^^^^^^^^^^^^^

.. list-table::
   :widths: 33 33 33
   :align: center
   :class: image-grid

   * - .. figure:: _static/images/controllers/arduino_uno.jpg
          :width: 300
          :alt: Arduino UNO

          **Arduino UNO**

     - .. figure:: _static/images/controllers/arduino_nano_t.jpg
          :width: 300
          :alt: Arduino NANO

          **Arduino NANO**

     - .. figure:: _static/images/controllers/arduino_mega.jpg
         :width: 300
         :alt: Arduino MEGA

         **Arduino MEGA**

.. note::
   **Rashberry PI PICO W** is extension of **Rashberry PI PICO** with **Infenion CYW43439** connectivity chip.


Device Programmers and Debuggers
--------------------------------

.. list-table::
   :widths: 50 50
   :align: center
   :class: image-grid

   * - .. figure:: _static/images/debuggers/stlink.jpeg
          :width: 300
          :alt: ST-Link V2 Duplicate

          **ST-Link V2**

     - .. figure:: _static/images/debuggers/jlink-edu.jpeg
          :width: 300
          :alt: JLink Edu Mini

          **JLink Edu Mini**

.. Attention::
    The **ST-Link V2** shown above is duplicate. The original one looks shown below:

    .. image:: _static/images/debuggers/stlink-original.jpg
       :width: 300
       :align: center
       :alt: ST-Link V2 Original


Programming and Scripting Laguages
----------------------------------

.. list-table::
   :align: center
   :class: image-grid

   * - .. figure:: _static/images/program_logos/c_logo.png
          :width: 150
          :alt: C

          **C**

     - .. figure:: _static/images/program_logos/cpp_logo.png
          :width: 150
          :alt: C++

          **C++**

     - .. figure:: _static/images/program_logos/python_logo.png
          :width: 150
          :alt: Python

          **Python**

   * - .. figure:: _static/images/program_logos/makefile_logo.png
          :width: 150
          :alt: Make

          **Make**

     - .. figure:: _static/images/program_logos/cmake_logo.png
          :width: 150
          :alt: CMake
   
          **CMake**

     - .. figure:: _static/images/program_logos/bash-icon.svg
          :width: 150
          :alt: Bash
 
          **Bash**
          

**Softwares and SDKs** are on `next <getting_started/installation.html>`_ installation guide.
