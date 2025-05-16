Game Controller
===============

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

A game controller is an important input device for manually controlling a robot. Most game controllers generally have two joysticks, two triggers, two bumpers, four pad buttons, four user buttons, and three special buttons. Some game controllers also have a vibration motor, LEDs, and a speaker. Each joystick has two potentiometers for the X and Y axes and a push button. Each trigger has a potentiometer for its axis.

The Xbox 360 and PlayStation controllers are two of the most popular game controllers. They can be connected to a computer using a USB cable or Bluetooth, and can also be connected to a microcontroller using USB or Bluetooth. In this tutorial, we are going to use a PS4 controller and an ESP32 WROOM32 module. The ESP32 supports both classic Bluetooth and BLE, while the PS4 controller only supports classic Bluetooth.


.. figure:: images/ps4.jpg
   :width: 500
   :align: center
   :alt: PS4 Controller

   **PS4 Controller (DualShock)**

.. figure:: images/xbox.jpg
   :width: 500
   :align: center
   :alt: Xbox 360 Controller

   **Xbox 360 Controller**

.. figure:: images/ps4_label.webp
   :width: 600
   :align: center
   :alt: PS4 Controller Label

   **PS4 Controller Label**

.. figure:: images/xbox_label.png
   :width: 600
   :align: center
   :alt: Xbox 360 Controller Label

   **Xbox 360 Controller Label**


2. Understanding the flow of Data and Signals from Game Controller to Actuator
------------------------------------------------------------------------------

.. figure:: images/joy_data_flow.png
   :width: 100%
   :align: center
   :alt: Flow of Data and Signals from Game Controller to Actuator

   **Flow of Data and Signals from Game Controller to Actuator**

The ESP32 acts as a wireless receiver, parsing HID data from the PS4 controller and converting it into a common JoyData format. This data is then sent to the STM32 via UART, where the STM32 uses the JoyData to control the actuators. The ESP32 can be replaced with a Raspberry Pi Pico W or any other. The standardized JoyData format makes it easy to swap out the receiver as needed.


3. Joystick Data Format from Receiving Controller
-------------------------------------------------

Creating a header file for the JoyData structure is a good practice, as it allows you to define the structure in a single place and include it in multiple source files. This makes it easier to include, maintain and update the structure if needed.

.. _joy_msg:

.. literalinclude:: files/game_controller/joy_msg.hpp
   :language: cpp
   :linenos:
   :caption: joy_msg.hpp

The total size of JoyData is 8-bytes and contains the following fields:

- **lx**: Left joystick X-axis value
- **ly**: Left joystick Y-axis value
- **rx**: Right joystick X-axis value
- **ry**: Right joystick Y-axis value
- **lt**: Left trigger value
- **rt**: Right trigger value
- **buttons**: Bitmask representing the state of the buttons. Each button is represented by a bit in the bitmask, where 1 indicates that the button is pressed and 0 indicates that it is not pressed.

The buttons are defined in the myPS4 and myXBox namespaces, and each button is assigned a unique value. The buttons are represented as bitmasks, which means that multiple buttons can be pressed at the same time.
The JoyData structure is packed to ensure that the data is aligned correctly in memory. The ``#pragma pack(push, 1)`` directive tells the compiler to align the structure on a 1-byte boundary, which means that there will be no padding between the fields of the structure. The ``#pragma pack(pop)`` directive restores the previous packing alignment.


4. Setting ESP32 as Receiver
----------------------------

.. figure:: images/esp32_wroom.jpg
   :width: 300
   :align: center
   :alt: ESP32 WROOM32

   **DOIT ESP32 DEVKIT V1**

There are some Arduino libraries available for interfacing PS4 controller with ESP32. Some examples for ESP32 IDF are also avialable which uses Bluetooth as well as USB. We are going to use Arduino library for this tutorial.

4.1. Installing ESP32 Board by Espressif in Arduino IDE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Open ``Arduino IDE``.
- Search for ``ESP32`` in the board manager.
- Install the board by ``Espressif``.

.. _find_mac:

4.2. Finding MAC Address of ESP32 and Setting up PS4 Controller
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The MAC address is used to pair the PS4 controller with the ESP32 board. Follow the steps below to find the MAC address of the ESP32 board and set up the PS4 controller:

- Open ``Arduino IDE`` and create a new sketch. 

- Copy the following code into the sketch:
   
  .. literalinclude:: files/game_controller/esp_mac_loockup.ino
     :language: cpp
     :linenos:
     :caption: esp_mac_loockup.ino

- Save the sketch as ``esp_mac_loockup.ino``.

- Select board ``DOIT ESP32 DEVKIT V1`` from ``Tools > Board > esp32``.

- Upload the code to the ESP32 board and open the Serial Monitor. The MAC address will be displayed in the Serial Monitor.

- Open ``SixaxisPairTool`` on Windows. See `installation <../geting_started/installation.html>`_ if you do not have. Plug the PS4 controller to PC using USB Cable. Driver for the controller will be installed, if it is first time.

- Connect the PS4 controller to the PC using a USB cable. The ``SixaxisPairTool`` will display the MAC address of the PS4 controller. Write the Bluetooth Mac Address of the ESP32 into ``Master MAC Adrress Field`` and click ``update``.


4.3. Using PS4Controller Library by Juan Pablo Marquez
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Install the library from Arduino Library Manager or download from :newtab:`here <https://docs.arduino.cc/libraries/ps4controller/>`.

- Create a new sketch and paste the following contents:

  .. literalinclude:: files/game_controller/esp_rx_ps4_library.ino
     :language: cpp
     :linenos:
     :caption: esp_rx_ps4_library.ino

- Save the sketch as ``esp_rx_ps4_library.ino``.

- Create a new file ``joy_msg.hpp`` in the same directory as the sketch. Copy the contents of the JoyData structure from :ref:`above <joy_msg>` into this.

- Create two files ``crc8.hpp`` and ``crc8.cpp`` in the same directory as the sketch. The contents of these files are as follows:

.. _crc8:

  .. literalinclude:: files/game_controller/crc8.hpp
     :language: cpp
     :linenos:
     :caption: crc8.hpp

  .. literalinclude:: files/game_controller/crc8.cpp
     :language: cpp
     :linenos:
     :caption: crc8.cpp

- Select board ``DOIT ESP32 DEVKIT V1`` from ``Tools > Board > esp32``.

- Select  port and upload the sketch to the ESP32 board.

- Open the Serial Monitor. Press the ``PS button`` on the PS4 controller to turn it on. You should see the joystick data changing according to the input from the PS4 controller.


4.4. Using ESP32_Bluepad32
~~~~~~~~~~~~~~~~~~~~~~~~~~

- In Arduino IDE, go to ``File > Preferences`` and add the following URL to the ``Additional Board Manager URLs`` field:

  .. code-block:: text
  
     https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json

- Open the Board Manager by going to ``Tools > Board > Board Manager``. Search for ``esp32_bluepad32`` by Ricardo Quesda and install the package.

- Create a new sketch and paste the following contents:

  .. literalinclude:: files/game_controller/esp_rx_bluepad.ino
     :language: cpp
     :linenos:
     :caption: esp_rx_bluepad.ino

- Save the sketch as ``esp_rx_bluepad.ino``.

- Create a new file ``joy_msg.hpp`` in the same directory as the sketch. Copy the contents of the JoyData structure from :ref:`above <joy_msg>` into this.

- Create two files ``crc8.hpp`` and ``crc8.cpp`` in the same directory as the sketch. The contents are same as :ref:`above <crc8>`.

- Select board ``DOIT ESP32 DEVKIT V1`` from ``Tools > Board > esp32_bluepad32``.

- Select  port and upload the sketch to the ESP32 board.

- Open the Serial Monitor. Press the ``PS button`` and the ``Share button`` on the PS4 controller to pair it with the ESP32 board. You should see the joystick data changing according to the input from the PS4 controller.

For more information on the ESP32_Bluepad32 package, see the `documentation <https://bluepad32.readthedocs.io/en/latest/plat_arduino>`_.


5. Setting Raspberry Pi Pico W as Receiver
------------------------------------------

.. figure:: images/pi_pico_w.jpg
   :width: 300
   :align: center
   :alt: Raspberry Pi Pico W

   **Raspberry Pi Pico W**

For the Raspberry Pi Pico W, we use ``Pico SDK``. The Pico SDK is a C/C++ SDK for the Raspberry Pi Pico and Pico W. It provides a set of libraries and tools to help you develop applications for the Pico and Pico W.

Till now, we have provided code straight on the page. Now, we are going to deal with huge code base. So we will provide the link of github repository. Follow the following instructions below to set up the Pico SDK and build the code for receving from PS4 controller:

- To install Pico SDK, run ``pico_setup.sh`` cloning from `here <https://github.com/raspberrypi/pico-setup.git>`_.

  .. code-block:: bash
  
     git clone https://github.com/raspberrypi/pico-setup.git
     cd pico-setup
     export SKIP_VSCODE=1 && bash pico_setup.sh

- Clone `this  repository <https://github.com/Robotics-Club-Pulchowk/picow_ds4.git>`_  and update submodule.

  .. code-block:: bash
  
     git clone https://github.com/Robotics-Club-Pulchowk/picow_ds4.git
     cd picow_ds4
     git submodule update --init --recursive

- Find out ``MAC Address`` of PS4 Controller. In easy way, connect it to yout PC and see the ``MAC Address``.

- Get into the source code folder, open ``Src/bt_hid.c``, scroll down a little and replace ``remote_addr_string`` value by the MAC address of PS4.

- To print data on ``Serial Monitor``, enable stdio usb by editing this line of ``Src/CMakeLists.txt``.

  .. code-block:: cmake
  
     pico_enable_stdio_usb(picow_ds4 1)

- From the project directory, make build folder, execute ``cmake`` and ``makefile``.

  .. code-block:: bash
  
      cd picow_ds4
      git submodule update --init --recursive
      mkdir build
      cd build
      cmake .. # you might use `-DPICO_BOARD=pico_w -DPICO_SDK_PATH=/your/path/to/pico-sdk` if environment is not set
      make -j4
  
  ``.uf2`` file is used for programming ``Pico``. You can find it at ``build/src/picow_ds4.uf2``

- Hold the boot button and connect the Pico W to PC using USB.

- Drag and drop the ``picow_ds4.uf2`` file from ``build/src`` to Pico W ``Mass Storage``. You also can use similar command.

  .. code-block:: bash
   
     # Just hit `tab` `tab` after `/media`.
     cp picow_ds4.uf2 /media/pi/PICOW

- Long press ``share`` and ``PS4 button`` simultaneous untill fast blink of PS4 LED. It will connect to Pico W. Pico W blinks its green LED if no controller is connected and solid green if it detects and connects to a controller.

Pico W sends uart packet same as ESP32 througth its UART0 default Tx and Rx pin i.e. ``pin 0`` and ``pin 1``.
