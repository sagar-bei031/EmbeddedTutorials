Game Controller
===============

.. contents:: Contents
   :depth: 2
   :local:


1. Introduction
---------------

Game controller is an important input device for controlling robot mannually. Most of game controllers generally have two joystics, two triggers, two bumpers, four pad buttons, four user buttons, and three special buttons.  Some of the game controllers have a vibration motor, leds, and a speaker. A joystick has two potentiometers for X and Y axis and a push button. A triggers has a potentiometer for the axis.

Xbox 360 and Playstation Controller are two most popular game controllers. They are connected to the computer using USB cable or Bluetooth. They are also connected to the microcontroller using USB cable or Bluetooth. In this tutorial, we are going to use PS4 controller and ESP32 WROOM32 module. It has classic bluetooth as well as BLE. PS4 controller only has classic bluetooth.


.. images:: images/ps4.webp
   :width: 600
   :align: center
   :alt: PS4 Controller

   **PS4 Controller (Duashock)**

.. images:: images/xbox.webp
   :width: 600
   :align: center
   :alt: Xbox 360 Controller

   **Xbox 360 Controller**


2. Setting ESP32 as Receiver
----------------------------

.. images:: images/esp32_wroom32.jpg
   :width: 300
   :align: right
   :alt: ESP32 WROOM32

   **ESP32 WROOM32**

There are some Arduino libraries available for interfacing PS4 controller with ESP32. Some examples for ESP32 IDF are also avialable which uses Bluetooth as well as USB. We are going to use Arduino library for this tutorial.

2.1. PS4Controller Library by Juan Pablo Marquez
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Install the library from Arduino Library Manager or download from :newtab:`here <https://docs.arduino.cc/libraries/ps4controller/>`.
