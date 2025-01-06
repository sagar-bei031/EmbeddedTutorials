ARM Maths
=========

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

**Microcontrollers** generally have microprocessors having **low computation capacity**. Even some of them do not have **Floating-Point Processing Unit (FPU)**. So it can be very expensive to do even common mathematics like **floating point** calculation, **trigonometric** calculation, **matrix** calculation etc. So, to do such calculation efficienty, we use **Cortex Microcontroller Software Interface Standard (CMSIS)** **arm maths library**. If you are more interested about floating point and floating point library, search for **Qfplib** and **IEE 754**.

In STM32 project, ``arm_math`` header and source files are inside ``Drivers >  CMSIS > DSP``. ``Cortex M3`` microcontrollers do not have **FPU** so there is **linkable math library** inside ``Drivers > CMSIS > Lib``.


2. Linking Arm Math Library for ARM Cortex-M3
---------------------------------------------

You can link the library by adding the GCC library path ``Drivers/CMSIS/Lib/GCC`` and the linker flag "libarm_cortexM3l_math.a in the Makefile.

.. code-block:: none

   # libraries
   LIBS = -lc -lm -lnosys -l:libarm_cortexM3l_math.a
   LIBDIR = -LDrivers/CMSIS/Lib/GCC/


3. Using Arm Math Library
-------------------------

Add the DSP include path in the **Makefile**.

.. code-block:: none

   # C includes
   C_INCLUDES =  \
   ...
   -IDrivers/CMSIS/DSP/Include

To use the arm math library, you need to include the header file ``arm_math.h`` in your source file.

.. code-block:: c

   #include "arm_math.h"


Let's suppose you want to calculate **sine** and **cosine** of an angle. To do so, you need to add the respective sources in the **Makefile**.

.. code-block:: none

   # C sources
   C_SOURCES = \
   ...
   Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.c \
   Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.c

Don't forget to define ARM_MATH version in the **Makefile**.

.. code-block:: none

   # C defines
   C_DEFS =  \
   ...
   -DARM_MATH_CM3 # For Cortex M3, -DARM_MATH_CM4 for Cortex M4

Now you can use the functions ``arm_sin_f32`` and ``arm_cos_f32`` to calculate the sine and cosine of an angle.

.. code-block:: c

   float32_t angle = 0.5;
   float32_t sine = arm_sin_f32(angle);
   float32_t cosine = arm_cos_f32(angle);


Issues
------

.. error::
   Drivers/CMSIS/Include/core_cm4.h:105:8: error: #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      105 |       #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"

You may get such error for **Cortex M4** or others having **FPU**. To solve this, define ``-D__FPU_PRESENT=1U`` in the **Makefile**.

.. code-block:: none

   # C defines
   C_DEFS =  \
   ...
   -D__FPU_PRESENT=1U # For having FPU

Now let's learn to use matrix function