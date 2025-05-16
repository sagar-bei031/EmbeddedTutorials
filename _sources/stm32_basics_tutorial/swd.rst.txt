SWD
===

Serial Wire Debug  (SWD) is a lightweight debug protocol from ARM. The physical layer of SWD consists of following lines:

- **Serial Wire Clock (SWCLK)**: A clock driver by the host.
- **Serial Wire Input Output(SWDIO)**: A bidirectional data line for debugging.
- **Serial Wire Output (SWO)**: A trace output line for **Serial Wire Viewer** (SWV).


.. attention::
   This ST-Link V2 does not support ``SWV`` as there is no ``SWO`` pin. `Use USB instead of SWV <stm32_basics_tutorial/usb/usb_printf.html>`_.

   .. image:: ../_static/images/debuggers/stlink.jpeg
      :width: 300
      :align: center
      :alt: stlink.jpeg
   

.. toctree::
   :maxdepth: 1
   :caption: Contents:
   
   swd/debug_using_swd
   swd/print_using_swd