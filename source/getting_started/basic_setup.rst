Basic Setup
===========

**Requirements and Verification**:

- make:

  .. code-block:: bash
       
     make --version

- cmake:

  .. code-block:: bash
       
     cmake --version

- arm-none-eabi-gcc:

  .. code-block:: bash
       
     arm-none-eabi-gcc --version


- gdb-multiarch:

  .. code-block:: bash
       
     gdb-multiarch --version

- stlink-tools:

  .. code-block:: bash
       
     stlink-tools --version

- STM32CubeMX

- VSCODE

- Any STM32 Microcontroller


After installing and verifying all the requirements, let's move to generate basic Hardware Abstraction Layer (HAL) code for stm32 microcontrollers.


.. toctree::
   :maxdepth: 2
   :caption: Contents:

   basic_setup/generate_basic_code
   basic_setup/build_using_makefile
   basic_setup/build_using_cmakelists
   basic_setup/flash_using_makefile
   basic_setup/flash_using_cmakelists