Setup
=====



1. Generate Basic Code
----------------------

1.1. Microcontroller Selection
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
- Open ``STM32CubeMX``.
- Click ``New Project``.
- Select ``MCU/MPU Selector`` if you want to select microcontroller IC number or select ``Board Selector`` if you want to select using development board number. For example, **STM32F407G-DISC1** from ``Board Selector`` or **STM32F407VG** from ``MCU/MPU Selector``.
- Select particular microcontroller from list on right side and click ``Start Project``.

You might be asked to initialize peripheral with their **default mode**. Click ``No``. But if you want to use default mode, click ``Yes``.


1.2. Pinout & Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^
-  Clear default pinouts by pressing ``Ctrl + P`` and ``Enter``.
-  Go to ``RCC > High Speed Clock (HSE)`` and select ``Crystal Ceramic Resonator``.
-  Go to ``SYS > Debug`` and select ``Serial Wire``.

Now you can select pins for LED, UART, Timers and many more. But leave them for this tutorial.


1.3. Clock Configuration
^^^^^^^^^^^^^^^^^^^^^^^^
- Specify ``HCLK (MHx)``. We prefer to use maximum clock frequency. For example, **168 MHz** if using **STM32F407VGT6** or **72 MHz** if using **STM32F103C8**.


1.4. Project Manager
^^^^^^^^^^^^^^^^^^^^

1.4.1. Project
~~~~~~~~~~~~~~
- Write ``Project Name``.
- Write ``Project Location```.
- Select ``Toolchanin/IDE``. We prefer to choose **Makefile**. **CMake** was not available before.

1.4.2. Code Generator
~~~~~~~~~~~~~~~~~~~~~
- Select copy all used libraries in to the project folder.
- Tick:
    - Generate eripheral initialization as a pair '.c/.h' file per peripheral.
    - Keep user code when regenerating.
    - Delete priviously generated file when not in use.

Generate code by clicking ``GENERATE CODE``. Open your project folder, open terminal at your project folder and run ``make`` command in your terminal.

If you have selected **CMake** for your project.

.. code-block:: bash

   mkdir build
   cd build
   cmake ..
   make

But this does not generate ``.bin`` file which is needed for flashing you microcontroller. To generate, you need to use ``arm-none-eabi-objcopy``.

.. code-block:: bash
    
   arm-none-eabi-objcopy -O binary <your_project_name.elf> <your_project_name.bin>



2. Add Codes to Makefile for Flashing
-------------------------------------

For **ST-Link**, add these at the bottom of **Makefile**.

.. code-block:: makefile
    
   flash:
       st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

For **JLink**, add these lines at the bottom of the **Makefile**.

.. code-block:: makefile
    
   device = STM32F103C8
   $(BUILD_DIR)/jflash: $(BUILD_DIR)/$(TARGET).bin
   	@touch $@
   	@echo device $(device) > $@
   	@echo -e si 1'\n'speed 4000 >> $@
   	@echo loadbin $< 0x8000000 >> $@
   	@echo -e r'\n'g'\n'qc >> $@
   
   jflash: $(BUILD_DIR)/jflash
   	JLinkExe -commanderscript $<


Use ``make flash`` or ``make jflash`` commands in order to flash.



3. Debugging Setup
------------------

- Install **Cortex-Debug** extension by **marus25** in VSCODE, if not installed previously.
- Update or create ``.vscode/lauch.json`` the json as below.
   
For **ST-Link** or **JLink**:

.. code-block:: json

   {
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Cortex Debug",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/build/BasicSetup.elf",
            "request": "launch",
            "type": "cortex-debug",
            "runToEntryPoint": "main",
            "device": "STM32F407VG",
            "interface": "swd",
            "servertype": "stlink",
            "gdbPath": "/usr/bin/gdb-multiarch"
        }
    ]
   }

For **OpenOCD**:

.. code-block:: json

   {
       "version": "0.2.0",
       "configurations": [
           {
               "name": "OpenOCD Debug",
               "cwd": "${workspaceFolder}",
               "executable": "${workspaceFolder}/build/BasicSetup.elf",
               "request": "launch",
               "type": "cortex-debug",
               "runToEntryPoint": "main",
               "device": "STM32F407VG",
               "interface": "swd",
               "servertype": "openocd",
               "configFiles": [
                   "interface/stlink-v2-1.cfg",
                   "target/stm32f4x.cfg"
               ],
               "gdbPath": "/usr/bin/gdb-multiarch"
           }
       ]
   }

For more about **OpenOCD**, watch `this <https://www.youtube.com/watch?v=_1u7IOnivnM>`_.