Timer
=====

Timers are essential peripherals in embedded systems, used for precise control and measurement of time-related tasks. They are hardware modules that count clock pulses and perform operations at specified intervals or durations.

Application of timers
---------------------

1. Delays:
^^^^^^^^^^

   Create precise delays for debouncing, communication protocols, or other timing-critical tasks.

2. Pulse Width Modulation (PWM):
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
   
   Generate PWM signals for controlling motors, LEDs, or other actuators.

3. Event Counting:
^^^^^^^^^^^^^^^^^^
   
   Count external events like button presses or pulses from a rotary encoder.

4. Frequency Measurement
^^^^^^^^^^^^^^^^^^^^^^^^

   Measure the frequency or duty cycle of an external signal.

5. Periodic Tasks
^^^^^^^^^^^^^^^^^

   Trigger periodic interrupts for tasks like sampling sensors or updating displays.

6. System Monitoring
^^^^^^^^^^^^^^^^^^^^

   Watchdog timers help monitor and reset the system if it becomes unresponsive.


.. toctree::
   :maxdepth: 1
   :caption: Contents:
   
   timer/pwm
   timer/encoder
   timer/microsecond_delay
   timer/frequency_counter