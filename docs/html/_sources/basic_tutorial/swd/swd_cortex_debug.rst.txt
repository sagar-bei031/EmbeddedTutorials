SWD Cortex Debug
================

Cortex-Debug is an extension for Visual Studio Code to streamline the debug process when working with ARM Cortex-M microcontrollers.



Requirements
------------

If you did not install these previously, you need to install now.

- **Cortex-Debug**

  Install ``Cortex-Debug`` extension by **marus25** in VSCODE.

- **gdb-multiarch**

  Install ``gdb-multiarch`` by executing command ``sudo apt install gdb-multiarch``.


   
For **ST-Link** or **JLink**
----------------------------

Update or create ``.vscode/lauch.json`` file.

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

For ``jlink``, change "servertype": "jlink".



For **OpenOCD**
---------------

``OpenOCD`` server is better than ``ST-Link`` server. We also prefer to use ``OpenOCD`` instead of ``ST-Link`` but it is not neccessary. 

Install ``OpenOCD`` by executing command ``sudo apt install openocd``.

Update ``.vscode/launch.json``.

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



Run Debugger
------------

- Connet your ST-Link or JLink to your microcontroller and your PC.
- Go to ``Run and Debug`` section in VSCODE.
- Click ``Run`` button.

You will see a floating toolbar which you can use for ``continue``, ``step over``, ``step into``, ``step out``,  ``restart`` and ``stop``.