Flash Using Makefile
====================

.. contents:: Contents
   :depth: 2
   :local:


We use **ST-Link** or **JLink** to flash binary to stm32 microcontrollers.



1. Using ST-Link
----------------

- Add these at the bottom of **Makefile**.

  .. literalinclude:: makefiles/flash
     :language: makefile

  If you want to **reset after flash**, update to:

  .. literalinclude:: makefiles/flash_reset
     :language: makefile

  .. warning::
     To **reset after flash**, make sure that **reset pin of st-link is connected to reset pin of microcontroller**. Otherwise, it will not work and give error. In discovery board, it is connected by default.
  
  ``st-flash`` command is part of ``stlink-tools``. Here, **binary file** is upload to **flash memory** of microcontroller Starting from address ``0x8000000``.

  If you want to learn more about ``st-flash command``, run:

  .. code-block:: bash

     st-flash --help

- Connect your **ST-Link** to your microcontroller.

- Flash binary.

  .. code-block:: bash

     make flash



2. Using JLink
--------------

- Create ``flash.sh`` file at your project folder.

  .. code-block:: bash

     #!/bin/bash

     set +e

     JLinkExe -if SWD -speed 4000 -autoconnect 1 -CommanderScript flash.jlink

- Create ``flash.jlink`` file at your project folder.

  .. code-block::
      
     device STM32F103C6
     r
     h
     loadbin build/<your_binary_filename>.bin, 0x08000000
     r
     g
     exit

  Change ``binary filename``.

- Make ``flash.sh`` executable.

  .. code-block:: bash
  
     chmod +x flash.sh

- Flash binary.

  .. code-block:: bash
  
     ./flash.sh
