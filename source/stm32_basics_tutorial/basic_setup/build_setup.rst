Build setup
===========

.. contents:: Contents
   :depth: 2
   :local:


Buid using Makefile
-------------------

1. Open your project folder. It is better to use ``VSCODE``.

2. Open ``terminal`` from your project folder.

3. Build project using ``make`` command.

   It is very easy this time to build the project using Makefile. You just need to use the ``make`` command and nothig.
   
   .. code-block:: bash
   
      make -j
   
   ``-j`` is for doing all jobs code at once. It speeds up build time using parallel processing. If you want to do ``n`` jobs at once, use ``-jn``. For example, executing ``8`` tasks at once:
   
   .. code-block:: bash
   
      make -j8


4. If you want to clean the project, use ``make clean``.


Build using CMake
-----------------

1. Open your project folder. It is better to use ``VSCODE``.

2. Open ``terminal`` from your project folder.

3. Build project using ``cmake`` command.

   .. code-block:: bash

      mkdir build
      cd build
      cmake ..
      make -j

.. _generate-binary-using-arm-none-eabi-objcopy:

   But this does not generate ``.bin`` file which is needed for flashing the microcontroller. To generate, you need to use ``arm-none-eabi-objcopy``.

   .. code-block:: bash

      arm-none-eabi-objcopy -O binary <your_project_name.elf> <your_project_name.bin>

   We always do this job. So, it is better to generate binary file using CMake. 

4. Add these lines at the bottom of **CMakeLists.txt**.
   
   .. code-block:: cmake

      # Generate binary
      add_custom_command(
          OUTPUT ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
          COMMAND arm-none-eabi-objcopy -O binary ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
          DEPENDS ${CMAKE_PROJECT_NAME}
          COMMENT "Converting ELF to binary"
      )

      # Binary target
      add_custom_target(bin ALL
          DEPENDS ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
          COMMENT "Generating binary file"
      )

   To build using only one line of command, a script file is needed. 

5. Create a ``build.sh`` file at your project folder for compiling and generating binary file.

   .. code-block:: bash
      :caption: flash.sh

      #!/bin/bash

      set +e

      if [[ "$1" == "clean" ]]; then
          rm -rf build
      fi

      if [ ! -d "build" ]; then
          mkdir build
      fi

      cd build
      cmake ..
      make -j
      cd ..

6. Make ``build.sh`` executable.

   .. code-block:: bash

      chmod +x build.sh

7. Compile using one line of command.

   .. code-block:: bash

      ./build.sh

   To clean first then build, run:
   
   .. code-block:: bash
   
       ./build.sh clean
