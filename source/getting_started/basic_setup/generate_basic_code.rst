Generate Basic Code
===================


1. Microcontroller Selection
----------------------------

- Open ``STM32CubeMX``.

- Click ``New Project``.

- Select ``MCU/MPU Selector`` if you want to select microcontroller IC number or select ``Board Selector`` if you want to select using development board number. For example, **STM32F407G-DISC1** from ``Board Selector`` or **STM32F407VG** from ``MCU/MPU Selector``.

- Select particular microcontroller from list on right side and click ``Start Project``. 

  .. image:: images/board_selector.webp
    :width: 600
    :alt: Board Selector

You might be asked to initialize peripheral with their **default mode**. Click ``No``. But if you want to use default mode, click ``Yes``.


2. Pinout & Configuration
-------------------------

- Clear default pinouts by pressing ``Ctrl + P`` and ``Enter``.

- Go to ``RCC > High Speed Clock (HSE)`` and select ``Crystal Ceramic Resonator``.

  .. image:: images/rcc.webp
     :width: 600
     :alt: RCC

- Go to ``SYS > Debug`` and select ``Serial Wire``.

  .. image:: images/sw.webp
     :width: 600
     :alt: SW  

Now you can select pins for LED, UART, Timers and many more. But leave them for now.


3. Clock Configuration
----------------------

- Specify ``HCLK (MHx)``. We prefer to use maximum clock frequency. For example, **168 MHz** if using **STM32F407VGT6** or **72 MHz** if using **STM32F103C8**.

  .. image:: images/clock.webp
    :width: 600
    :alt: Clock


4. Project Manager
------------------

   4.1. Project
   ^^^^^^^^^^^^

   - Write ``Project Name``.

   - Write ``Project Location```.

   - Select ``Toolchanin/IDE``. We prefer to choose **Makefile**. **CMake** was not available before.

     .. image:: images/project.webp
        :width: 600
        :alt: Project

   4.2. Code Generator
   ^^^^^^^^^^^^^^^^^^^

   - Select copy all used libraries in to the project folder.

   - Tick:

     - Generate peripheral initialization as a pair '.c/.h' file per peripheral.
     - Keep user code when regenerating.
     - Delete priviously generated file when not in use.

   - Generate code by clicking ``GENERATE CODE``.

     .. image:: images/code_generator.webp
        :width: 600
        :alt: Code Generator

Navigate to project folder, open it using ``VSCODE``. If you chose ``Makefile`` as your toolchain, you would find ``Makefile``` in the project folder. If you chose ``CMake`` as your toolchain, you would find ``CMakeLists.txt`` in the project folder. We shall later talk about the project structure, now move to **build** the project.