Matrix Operation
================

.. contents:: Contents
   :depth: 2
   :local:


1. Basic Setup
--------------

* Open STM32CubeMX and `generate basic code <../stm32_basics_tutorial/basic_setup/generate_basic_code.html>`_ for your board.

* Setup ``Makefile`` or ``CMakeLists.txt`` for **ARM Math**. See `arm math tutorial <arm_math.html>`_.
  
* Update ``Makefile`` or ``CMakeLists.txt`` to add **matrix functions**.

  .. tabs::

     .. group-tab:: Makefile
         
        .. code-block:: none
           :emphasize-lines: 4-10

           C_SOURCES = \
           ... \
           ... \
           Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.c \
           Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.c \
           Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.c \
           Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.c \
           Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.c \
           Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.c \
           Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.c 

     .. group-tab:: CMakeLists.txt

        .. code-block:: CMake
           :emphasize-lines: 4-10

            # Add sources to executable
            target_sources(${CMAKE_PROJECT_NAME} PRIVATE
                # Add user sources here
                Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.c
                Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.c
                Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.c
                Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.c
                Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.c
                Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.c
                Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.c
            )

* Add matrix check definition in ``Makefile`` or ``CMakeLists.txt``.

  .. tabs::

     .. group-tab:: Makefile
         
        .. code-block:: none
           :emphasize-lines: 5

           # C defines
           C_DEFS = \
           ... \
           -DARM_MATH_CM4 \
           -DARM_MATH_MATRIX_CHECK

     .. group-tab:: CMakeLists.txt

        .. code-block:: CMake
           :emphasize-lines: 5
           
           # Add project symbols (macros)
           target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
               # Add user defined symbols
               ARM_MATH_CM4
               ARM_MATH_MATRIX_CHECK
           )


2. Test Matrix Functions
------------------------

* Navigate to ``Core > Src`` and open ``main.c``.

* Include headers.

  .. tabs::
     
     .. group-tab:: SWV

        .. code-block:: c
           :emphasize-lines: 2-3
          
           /* USER CODE BEGIN Includes */
           #include <stdio.h>
           #include "arm_math.h"
           /* USER CODE END Includes */

     .. group-tab:: USB

        .. code-block:: c
           :emphasize-lines: 2-4
          
           /* USER CODE BEGIN Includes */
           #include <stdio.h>
           #include "arm_math.h"
           #include "usbd_cdc_if.h"
           /* USER CODE END Includes */

.. Warning::
   Do not forget to add compiler flag ``-u _printf_float`` in ``Makefile`` or ``CMakeLists.txt`` to print floating point numbers otherwise it will not print the numbers.

   .. tabs::
      
      .. group-tab:: Makefile
 
         Add to ``LDFLAGS``.
 
         .. code-block:: Makefile
            :emphasize-lines: 2
            
            LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
            LDFLAGS += -u _printf_float
 
      .. group-tab:: CMakeLists.txt
 
         Create target_link_options at the bottom.
 
         .. code:: CMake
            
            # Add compiler flags
            target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
                -u _printf_float
            )

 
- Overwrite definition of ``_write`` for ``printf`` as:

  .. tabs::
     
     .. group-tab:: SWV

        .. code-block:: c
           :emphasize-lines: 2-9
        
           /* USER CODE BEGIN 0 */
           int _write(int file, char *data, int len)
           {
             for (int i = 0; i < len; ++i)
             {
               ITM_SendChar(data[i]);
             }
             return len;
           }
           /* USER CODE END 0 */

     .. group-tab:: USB

        .. code-block:: c
           :emphasize-lines: 2-6
          
           /* USER CODE BEGIN 0 */
           int _write(int file, char *data, int len)
           {
             CDC_Transmit_FS((uint8_t*)data, (uint16_t)len);
             return len;
           }
           /* USER CODE END 0 */


* Write code to print matrix.

  .. code-block:: C
     :emphasize-lines: 3-13

     // ...

     void print_matrix(arm_matrix_instance_f32 *matrix)
     {
       for (int i = 0; i < matrix->numRows; i++)
       {
         for (int j = 0; j < matrix->numCols; j++)
         {
           printf("%f\t", matrix->pData[i * matrix->numCols + j]);
         }
         printf("\n");
       }
     }
     /* USER CODE END 0 */

* Write code to test matrix functions.

  .. code-block:: c
     :emphasize-lines: 2-12, 20-53

     /* USER CODE BEGIN 2 */
       arm_matrix_instance_f32 m1;
       float m1data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
       arm_mat_init_f32(&m1, 3, 3, m1data);
     
       arm_matrix_instance_f32 m2;
       float m2data[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
       arm_mat_init_f32(&m2, 3, 3, m2data);
     
       arm_matrix_instance_f32 result;
       float resultdata[9];
       arm_mat_init_f32(&result, 3, 3, resultdata);
       /* USER CODE END 2 */
     
       /* Infinite loop */
       /* USER CODE BEGIN WHILE */
       while (1)
       {
         /* USER CODE END WHILE */
         printf("Adding m1 and m2, result:\n");
         arm_mat_add_f32(&m1, &m2, &result);
         print_matrix(&result);
         HAL_Delay(1000);
     
         printf("Subtracting m1 and m2, result:\n");
         arm_mat_sub_f32(&m1, &m2, &result);
         print_matrix(&result);
         HAL_Delay(1000);
     
         printf("Multiplying m1 and m2, result:\n");
         arm_mat_mult_f32(&m1, &m2, &result);
         print_matrix(&result);
         HAL_Delay(1000);
     
         printf("Multiplying m1 by 2\n");
         arm_mat_scale_f32(&m1, 2, &result);
         print_matrix(&result);
         HAL_Delay(1000);
     
         printf("Transposing m1\n");
         arm_mat_trans_f32(&m1, &result);
         print_matrix(&result);
         HAL_Delay(1000);
     
         printf("Inverting m1\n");
         if (arm_mat_inverse_f32(&m1, &result) == ARM_MATH_SUCCESS)
         {
           print_matrix(&result);
         }
         else
         {
           printf("Matrix is not invertible\n");
         }
         /* USER CODE BEGIN 3 */
       }
       /* USER CODE END 3 */

3. Test Output:
---------------
  
.. code-block:: text

   Adding m1 and m2, result:
   10.000000       10.000000       10.000000
   10.000000       10.000000       10.000000
   10.000000       10.000000       10.000000
   Subtracting m1 and m2, result:
   -8.000000       -6.000000       -4.000000
   -2.000000       0.000000        2.000000
   4.000000        6.000000        8.000000
   Multiplying m1 and m2, result:
   30.000000       24.000000       18.000000
   84.000000       69.000000       54.000000
   138.000000      114.000000      90.000000
   Multiplying m1 by 2
   2.000000        4.000000        6.000000
   8.000000        10.000000       12.000000
   14.000000       16.000000       18.000000
   Transposing m1
   1.000000        4.000000        7.000000
   2.000000        5.000000        8.000000
   3.000000        6.000000        9.000000
   Inverting m1
   Matrix is not invertible


4. Creating Matrix Class and Overloading Operators
--------------------------------------------------

* Setup your ``Makefile`` or ``CMakeLists.txt`` for ``C++``. See `cpp setup <./cpp_setup_in_stm32.html>`_.

* Create ``matrix32.hpp`` inside ``Core/Inc``. Copy these contents.
  
  .. literalinclude:: files/matrix/matrix32.hpp
     :language: cpp
     :linenos:
     :caption: matrix32.hpp

* Create ``app.h`` inside ``Core/Inc`` and ``app.cpp`` inside ``Core/Src``. Copy these contents.
  
  .. literalinclude:: files/matrix/app.h
     :language: cpp
     :linenos:
     :caption: app.h

  .. literalinclude:: files/matrix/app.cpp
     :language: cpp
     :linenos:
     :caption: app.cpp

* Include ``app.h`` in ``main.c``.
  
  .. code-block:: c
     :emphasize-lines: 3
     
     /* USER CODE BEGIN Includes */
     // ..
     #include "app.h"
     /* USER CODE END Includes */

* Call ``init()`` and ``run()`` functions. Also comment out previous codes from while loop.
  
  .. code-block:: c
     :emphasize-lines: 14, 22

     /* USER CODE BEGIN 2 */
     // arm_matrix_instance_f32 m1;
     // float m1data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
     // arm_mat_init_f32(&m1, 3, 3, m1data);
   
     // arm_matrix_instance_f32 m2;
     // float m2data[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
     // arm_mat_init_f32(&m2, 3, 3, m2data);
   
     // arm_matrix_instance_f32 result;
     // float resultdata[9];
     // arm_mat_init_f32(&result, 3, 3, resultdata);
   
     init();
     /* USER CODE END 2 */
   
     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
     while (1)
     {
       /* USER CODE END WHILE */
       run();
       // printf("Adding m1 and m2, result:\n");
       // arm_mat_add_f32(&m1, &m2, &result);
       // print_matrix(&result);
       // HAL_Delay(1000);
   
       // printf("Subtracting m1 and m2, result:\n");
       // arm_mat_sub_f32(&m1, &m2, &result);
       // print_matrix(&result);
       // HAL_Delay(1000);
   
       // printf("Multiplying m1 and m2, result:\n");
       // arm_mat_mult_f32(&m1, &m2, &result);
       // print_matrix(&result);
       // HAL_Delay(1000);
   
       // printf("Multiplying m1 by 2\n");
       // arm_mat_scale_f32(&m1, 2, &result);
       // print_matrix(&result);
       // HAL_Delay(1000);
   
       // printf("Transposing m1\n");
       // arm_mat_trans_f32(&m1, &result);
       // print_matrix(&result);
       // HAL_Delay(1000);
   
       // printf("Inverting m1\n");
       // if (arm_mat_inverse_f32(&m1, &result) == ARM_MATH_SUCCESS)
       // {
       //   print_matrix(&result);
       // }
       // else
       // {
       //   printf("Matrix is not invertible\n");
       // }
       /* USER CODE BEGIN 3 */
     }
     /* USER CODE END 3 */

* Add sources to ``Makefile`` or ``CMakeLists.txt``.
  
  .. tabs::

     .. group-tab:: Makefile
         
        .. code-block:: none
           :emphasize-lines: 4

           # C sources
           C_SOURCES = \
           ... \
           Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.c

        .. code-block:: cpp
           :emphasize-lines: 3
           
           # CXX sources
           CXX_SOURCES =  \
           Core/Src/app.cpp

     .. group-tab:: CMakeLists.txt

        .. code-block:: CMake
           :emphasize-lines: 4-5

            # Add sources to executable
            target_sources(${CMAKE_PROJECT_NAME} PRIVATE
                # ...
                Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.c
                Core/Src/app.cpp
            )


5. Test Ouput of Matrix Class 
-----------------------------

.. code-block:: text

   Adding m1 and m2, result:
   10.000000       10.000000       10.000000
   10.000000       10.000000       10.000000
   10.000000       10.000000       10.000000
   Subtracting m1 and m2, result:
   -8.000000       -6.000000       -4.000000
   -2.000000       0.000000        2.000000
   4.000000        6.000000        8.000000
   Multiplying m1 and m2, result:
   30.000000       24.000000       18.000000
   84.000000       69.000000       54.000000
   138.000000      114.000000      90.000000
   Multiplying m1 by 2
   2.000000        4.000000        6.000000
   8.000000        10.000000       12.000000
   14.000000       16.000000       18.000000
   Transposing m1
   1.000000        4.000000        7.000000
   2.000000        5.000000        8.000000
   3.000000        6.000000        9.000000
   Inverting m1
   EXCEPTION:: MATRIX INVERSION FAILED !!


.. tip::

   The raw arm math matrix functions are efficient than the matrix class. So use the matrix class for small matrices only.