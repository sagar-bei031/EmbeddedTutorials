UART
----

UART (Universal Asynchronous Receiver Transmitter) is a simple, two-wire protocol for exchanging serial data. Asynchronous means no shared clock, so for UART to work, the same bit or baud rate must be configured on both sides of the connection. UART is a full-duplex protocol, meaning it can send and receive data simultaneously. It is very useful for debugging and communication between microcontroller and PC. It is also used in many embedded systems for communication between two microcontrollers. 

It has two lines:

- TX: Transmit line
- RX: Receive line

The UART configurations we prefer are:

- Baud rate: 115200
- Data bits: 8
- Stop bits: 1
- Parity: None

.. note::
   The baud rate must be the same on both sides of the connection.
   GND must be connected between the two devices.

.. warning::
   STM32F407VG-DISC1 default UART1 TX pin (PA9) does not work properly when the USB OTG is used because PA9 pin is also used for USB OTG. For more information, `see the schematic of the board <https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/schematic_pack/mb997-f407vgt6-b02_schematic.pdf&ved=2ahUKEwjtzuKMxu6IAxVmR2wGHYkYAl8QFnoECBsQAQ&usg=AOvVaw0S1_y_ksxURXPd02EFhSfS>`_.


.. toctree::
    :maxdepth: 1
    :caption: Contents:
  
    uart/uart_polling
    uart/uart_interrupt
    uart/uart_dma
    uart/uart_issues
    