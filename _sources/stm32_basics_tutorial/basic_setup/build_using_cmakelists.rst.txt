Build Using CMakeLists
======================

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


Hope you are successful to build the project. If not, please check scripts you added before carefully.