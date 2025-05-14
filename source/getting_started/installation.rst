Installation
============

.. contents:: Contents
   :depth: 2
   :local:

We are using **Ubuntu** and **Windows**. Mostly, we will be using **Ubuntu** for development. But some softwares are only available for **Windows**. So, we will be using **Windows** for those.

Seeing below, you might think, "There are too many software to install. I don't want to install all of them." But don't worry. You can skip the software you don't need right now. When you realize you need it, you can install directly from official website or use this page for help. Fundamental tools are those we are going to use. Optional tools are alternative tools and are not neccessary now.

Fundamental Tools and Software
------------------------------

.. list-table:: 
   :header-rows: 1
   :widths: 5 15 40 40

   * - SN
     - Software
     - Description
     - Install Guide
   * - 1.
     - build-essential
     - Essential build tools like gcc, make, cmake, etc.
     - ``sudo apt install build-essential``
   * - 2.
     - arm-none-eabi-gcc
     - GCC compiler for ARM-based microcontrollers
     - ``sudo apt install gcc-arm-none-eabi``
   * - 3.
     - GDB
     - GNU Debugger
     - ``sudo apt install gdb-multiarch``
   * - 4.
     - stlink-tools
     - Command line tools for STM32 flash
     - ``sudo apt install stlink-tools``
   * - 5.
     - STM32CubeMx
     - STM32 configuration tool
     - Install from :newtab:`STM32CubeMx <https://www.st.com/en/development-tools/stm32cubemx.html>`.
   * - 6.
     - STM32CubeProgrammer
     - Program and debug STM32 devices
     - Install :newtab:`STM32CubeProgrammer <https://www.st.com/en/development-tools/stm32cubeprog.html>`.
   * - 7.
     - STM32CubeMonitor
     - Plot graphs for monitoring
     - Install :newtab:`STM32CubeMonitor <https://www.st.com/en/development-tools/stm32cubemonitor.html>`.
   * - 8.
     - Arduino IDE
     - Arduino IDE
     - Install :newtab:`Arduino IDE <https://www.arduino.cc/en/software>`.
   * - 9.
     - Pico SDK
     - Raspberry Pi Pico SDK
     - Install from :newtab:`Pico SDK Guide <https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf>`.
   * - 10.
     - JLink
     - JLink debugger
     - Install :newtab:`JLink Debugger <https://www.segger.com/downloads/jlink/>`.
   * - 11.
     - VSCode
     - Visual Studio Code
     - Install :newtab:`Visual Studio Code <https://code.visualstudio.com/>`.
   * - 12.
     - Cortex Debug
     - VSCode extension for debugging
     - Install :newtab:`Cortex Debug Extension <https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug>`.
   * - 13.
     - OpenOCD
     - Open On-Chip Debugger
     - ``sudo apt install openocd``
   * - 14.
     - Git
     - Version control system
     - ``sudo apt install git``


Other (Optional)
----------------

.. list-table:: 
   :header-rows: 1
   :widths: 5 15 40 40

   * - SN
     - Software
     - Description
     - Install Guide
   * - 1.
     - SixaxisPairTool (Windows)
     - Pair PS4 controller with devices (ESP32).
     - Install :newtab:`SixaxisPairTool <https://sixaxispairtool.en.lo4d.com/windows>`.
   * - 2. 
     - DFU Util
     - Device Firmware Upgrade utility
     - ``sudo apt install dfu-util``
   * - 3.
     - PlatformIO
     - PlatformIO IDE
     - Install :newtab:`PlatformIO <https://platformio.org/install/ide?install=vscode>`.
   * - 4.
     - Arduino CLI
     - Command line interface for Arduino
     - Install :newtab:`Arduino CLI <https://arduino.github.io/arduino-cli/installation/>`.
   * - 5.
     - STM32CubeIDE
     - STM32CubeIDE
     - Install :newtab:`STM32CubeIDE <https://www.st.com/en/development-tools/stm32cubeide.html>`.
   * - 6.
     - ESP-IDF
     - ESP32 SDK
     - Install from :newtab:`ESP-IDF Guide <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/>`.
