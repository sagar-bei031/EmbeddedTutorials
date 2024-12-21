USB CDC
=======

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

USB CDC (Communication Device Class) is a class of USB devices that are used to transmit data between a computer and a USB device. The USB CDC class is used to emulate a serial port over USB. This allows the USB device to be used as a virtual COM port. The USB CDC class is commonly used in microcontroller projects to provide a simple and easy way to communicate with a computer.



2. CubeMX Configuration
-----------------------

- Open `STM32CubeMX`, create a new project and set up basic configuration. Follow the `generate_basic_code <../basic_setup/generate_basic_code.html>`__ with:

  - microcontroller: ``stm32f407vgt6`` or board: ``STM32F407VG-DISC1``
  - project name: ``usb_example``
  - Toolchain/IDE: ``Makefile``

- Move to STM32CubeMX ``Pinout and Congiguration``. From ``Categories``, select ``Connectivity > USB_OTG_FS``. Change ``mode`` to ``Device_Only`` mode.

.. image:: images/usb_otg_fs.webp
   :width: 100%
   :align: center
   :alt: usb_otg_fs

- From ``Categories``, select ``Middleware and Software Packs``. Find ``USB_DEVICE``. Change ``Class for FS IP`` to ``Communication Device Class (Virtual Port Com``.

.. image:: images/usb_device_mode.webp
   :width: 600
   :align: center
   :alt: usb_device_mode

- Generate code and open the project.

USB Device Middleware is added to the project. The middleware provides the USB CDC class implementation, configured to use the USB OTG FS peripheral in device mode and to emulate a virtual COM port over USB.




3. Code to Transmit Data using USB CDC
--------------------------------------

- Open project folder and navigate to ``Core > Src > main.c``.

- Add header ``usb_cdc_if.h``.

  .. code-block:: c
     
     /* USER CODE BEGIN INCLUDE */
     #include "usbd_cdc_if.h"
     /* USER CODE END INCLUDE */
  
- Add the following code to the ``main`` function to transmit "Hello World" over USB.

  .. code-block:: c

     /* USER CODE BEGIN 2 */
     char msg[] = "Hello World\n";
     /* USER CODE END 2 */
     
     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
     while (1)
     {
       CDC_Transmit_FS((uint8_t*)msg, sizeof(msg));
       HAL_Delay(100);
       /* USER CODE END WHILE */
       
       /* USER CODE BEGIN 3 */
     }
     /* USER CODE END 3 */

- Build and flash.



4. Hardware Setup and Connection
--------------------------------

Connect your microcontroller to your PC using USB cable. For simplicity, open ``Serial Monitor`` in ``Arduino IDE``. You can see printing "Hello World" on the ``Serial Monitor`` continuosly. 

You can also use your ``terminal`` to see the message from the microcontroller. 

.. note::

   This debian package ``brltty`` creates issue on finding USB port address, especially for ``CPxxxx`` USB driver. So, remove ``brltty``.

   .. code-block:: bash
      
      sudo apt autoremove brltty

Open ``terminal``. Check the ``USB Port`` of the microcontroller. Type command:
 
.. code-block:: bash

   ls /dev/ttyACM0 # hit tab after `ACM`.
 
STM32 microcontroller USB ports are commonly have port address ``ACM0``, ``ACM1``, ``ACM2`` rather ``USB0``, ``USB1``, ``USB2``.

Print ``serial data`` on ``terminal``. For USB port ``ACM0``:

.. code-block:: bash
   
   cat /dev/ttyACM0

You can see "Hello World" printing continuosly on the ``terminal``.



Now you learn to send data over USB using ``printf`` in `next <usb_printf.html>`_ tutorial.



.. warning::
   Many bluepilsl found in Nepal have ``STM32F103C6T6`` microcontroller and have only 32KB flash memory. Using ``USB`` can overflow the flash memory.


References
----------

References are from ``STM32 HAL Driver`` documentation.

.. c:function:: uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)

   Transmits data over the USB IN endpoint via the CDC interface.

   :param Buf: Buffer of data to be sent.
   :param Len: Number of data bytes to be sent.
   :returns: ``USBD_OK`` if all operations succeed, otherwise ``USBD_FAIL`` or ``USBD_BUSY``.
   :note: This function handles data transmission via the USB CDC interface.
