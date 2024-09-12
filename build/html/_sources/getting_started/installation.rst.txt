Installation
============

OS
--

We are using Ubuntu and Windows. Mostly, we will be using Ubuntu for development. But some software is only available for Windows. So, we will be using Windows for those.

1. Ubuntu  
   Download Ubuntu ISO from https://ubuntu.com/download/desktop.

2. Windows  
   Download Windows 10/11 ISO from https://www.microsoft.com/en-us/software-download.

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
     - Install `Visual Studio Code <https://code.visualstudio.com/>`_.
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
     - Install `Arduino IDE <https://www.arduino.cc/en/software>`_.
   * - STM32CubeMx
     - STM32 configuration tool
     - Install from `STM32CubeMx <https://www.st.com/en/development-tools/stm32cubemx.html>`_.
   * - STM32CubeProgrammer
     - Program and debug STM32 devices
     - Install `STM32CubeProgrammer <https://www.st.com/en/development-tools/stm32cubeprog.html>`_.
   * - Pico SDK
     - Raspberry Pi Pico SDK
     - Install from `Pico SDK Guide <https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf>`_.
   * - JLink
     - JLink debugger
     - Install `JLink Debugger <https://www.segger.com/downloads/jlink/>`_.
   * - STM32CubeMonitor
     - Plot graphs for monitoring
     - Install `STM32CubeMonitor <https://www.st.com/en/development-tools/stm32cubemonitor.html>`_.
   * - Cortex Debug
     - VSCode extension for debugging
     - Install `Cortex Debug Extension <https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug>`_.

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
     - Install `SixaxisPairTool <https://sixaxispairtool.en.lo4d.com/windows>`_.
   * - PlatformIO
     - PlatformIO IDE
     - Install `PlatformIO <https://platformio.org/install/ide?install=vscode>`_.
   * - Arduino CLI
     - Command line interface for Arduino
     - Install `Arduino CLI <https://arduino.github.io/arduino-cli/installation/>`_.
   * - STM32CubeIDE
     - STM32CubeIDE
     - Install `STM32CubeIDE <https://www.st.com/en/development-tools/stm32cubeide.html>`_.
   * - ESP-IDF
     - ESP32 SDK
     - Install from `ESP-IDF Guide <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/>`_.
   * - DFU Util
     - Device Firmware Upgrade utility
     - ``sudo apt install dfu-util``
