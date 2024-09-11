Flash Using CMakeLists
======================

We use **ST-Link** or **JLink** to flash binary to stm32 microcontrollers.



1. Using ST-Link
----------------

- Add these lines at the bottom of **CMakeLists.txt**.
  
  .. code-block:: cmake
  
     # Flash target
     add_custom_target(flash
         COMMAND st-flash write ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin 0x8000000
         DEPENDS ${CMAKE_PROJECT_NAME}
         COMMENT "Flashing binary to microcontroller"
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
     )

- Connect your **JLink** to your microcontroller.

- Flash binary by running this command from ``build`` folder.

  .. code-block:: bash

     make jflash


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
