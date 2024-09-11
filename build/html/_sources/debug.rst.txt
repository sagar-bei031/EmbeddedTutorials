4. Debug Code
-------------

Well, we have not gone through the code yet. But we are just verifying if debugger is working or not.

- Install **Cortex-Debug** extension by **marus25** in VSCODE, if not installed previously.
- Update or create ``.vscode/lauch.json`` file.
   
- For **ST-Link** or **JLink**:

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

- For **OpenOCD**:

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

- Connet your ST-Link or JLink to your microcontroller.
- Go to **Run and Debug** section in VSCODE.
- Click **Run** button.

You will see a floating toolbar which you can use for ``continue``, ``step over``, ``step into``, ``step out``,  ``restart`` and ``stop``.

Hope you have successfully run debugger. If not, please check your connections and configurations. 