Flash Using Makefile
====================

.. contents:: Contents
   :depth: 2
   :local:


We use **ST-Link** or **JLink** to flash binary to stm32 microcontrollers.



1. Using ST-Link
----------------

- Add these at the bottom of **Makefile**.

  .. code-block:: makefile

     flash:
         st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000

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

- Add these lines at the bottom of the **Makefile**.

  .. code-block:: makefile

     device = STM32F103C8 # change device for your own
     $(BUILD_DIR)/jflash: $(BUILD_DIR)/$(TARGET).bin
         @touch $@
         @echo device $(device) > $@
         @echo -e si 1'\n'speed 4000 >> $@
         @echo loadbin $< 0x8000000 >> $@
         @echo -e r'\n'g'\n'qc >> $@

     jflash: $(BUILD_DIR)/jflash
         JLinkExe -commanderscript $<

- Connect your **JLink** to your microcontroller.

- Flash binary.

  .. code-block:: bash

     make jflash

  We can also do it better using ``bash script`` and ``jlink script``.

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
     loadbin build/MR_Slave.bin, 0x08000000
     r
     g
     exit

- Make ``flash.sh`` executable.

  .. code-block:: bash
  
     chmod +x flash.sh

- Flash binary.

  .. code-block:: bash
  
     ./flash.sh
