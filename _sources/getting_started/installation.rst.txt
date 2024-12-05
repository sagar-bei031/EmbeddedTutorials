Installation
============

.. contents:: Contents
   :depth: 2
   :local:

OS
--

We are using Ubuntu and Windows. Mostly, we will be using Ubuntu for development. But some software is only available for Windows. So, we will be using Windows for those.

1. Ubuntu  
   Download Ubuntu ISO from `here <https://ubuntu.com/download/desktop>`__.

2. Windows  
   Download Windows 10/11 ISO from `here <https://www.microsoft.com/en-us/software-download>`__.

Fundamental Tools and Software
------------------------------

.. list-table:: 
   :header-rows: 1
   :widths: 20 40 40

   * - Software
     - Description
     - Install Guide
   * - build-essential
     - Essential build tools like gcc, make, cmake, etc.
     - ``sudo apt install build-essential``
   * - vscode
     - Visual Studio Code
     - Install `Visual Studio Code <https://code.visualstudio.com/>`__.
   * - arm-none-eabi-gcc
     - GCC compiler for ARM-based microcontrollers
     - ``sudo apt install gcc-arm-none-eabi``
   * - GDB
     - GNU Debugger
     - ``sudo apt install gdb-multiarch``
   * - stlink-tools
     - Command line tools for STM32 flash
     - ``sudo apt install stlink-tools``
   * - Arduino IDE
     - Arduino IDE
     - Install `Arduino IDE <https://www.arduino.cc/en/software>`__.
   * - STM32CubeMx
     - STM32 configuration tool
     - Install from `STM32CubeMx <https://www.st.com/en/development-tools/stm32cubemx.html>`__.
   * - STM32CubeProgrammer
     - Program and debug STM32 devices
     - Install `STM32CubeProgrammer <https://www.st.com/en/development-tools/stm32cubeprog.html>`__.
   * - Pico SDK
     - Raspberry Pi Pico SDK
     - Install from `Pico SDK Guide <https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf>`__.
   * - JLink
     - JLink debugger
     - Install `JLink Debugger <https://www.segger.com/downloads/jlink/>`__.
   * - STM32CubeMonitor
     - Plot graphs for monitoring
     - Install `STM32CubeMonitor <https://www.st.com/en/development-tools/stm32cubemonitor.html>`__.
   * - Cortex Debug
     - VSCode extension for debugging
     - Install `Cortex Debug Extension <https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug>`__.

Other (Optional)
----------------

.. list-table:: 
   :header-rows: 1
   :widths: 20 40 40

   * - Software
     - Description
     - Install Guide
   * - OpenOCD
     - Open On-Chip Debugger
     - ``sudo apt install openocd``
   * - git
     - Version control system
     - ``sudo apt install git``
   * - SixaxisPairTool (Windows)
     - Pair PS4 controller with devices (ESP32).
     - Install `SixaxisPairTool <https://sixaxispairtool.en.lo4d.com/windows>`__.
   * - PlatformIO
     - PlatformIO IDE
     - Install `PlatformIO <https://platformio.org/install/ide?install=vscode>`__.
   * - Arduino CLI
     - Command line interface for Arduino
     - Install `Arduino CLI <https://arduino.github.io/arduino-cli/installation/>`__.
   * - STM32CubeIDE
     - STM32CubeIDE
     - Install `STM32CubeIDE <https://www.st.com/en/development-tools/stm32cubeide.html>`__.
   * - ESP-IDF
     - ESP32 SDK
     - Install from `ESP-IDF Guide <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/>`__.
   * - DFU Util
     - Device Firmware Upgrade utility
     - ``sudo apt install dfu-util``
