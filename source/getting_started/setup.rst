Setup
=====

.. contents:: Contents
   :depth: 2
   :local:

1. CH34x USB Driver Setup
-----------------------------

We sometimes get problem with USB driver for ``CH340/CH341`` USB to serial converter. It can be solved by removing ``brltty`` package.

Remove ``brltty``.

.. code-block:: bash

   sudo apt autoremove brltty


2. Creating ``.desktop`` files for application on Linux
-----------------------------------------------------------

Some applications do not appear on application menu which can be solved by creating ``.desktop`` file. Create a ``.desktop`` files at ``/home/$USER/.local/share/applications``. Add following informations:

.. code-block::

   [Desktop Entry]
   Name=<Name>
   Comment=<Content>
   Exec=<path/to/executable>
   Icon=<path/to/icon>

Some applications which do not appear on application menu are:

Arduino IDE
~~~~~~~~~~~

Creat 'arduino-ide.desktop' file in ``~/.local/share/applications`` directory, and add the following content:

.. code-block::

   [Desktop Entry]
   Name=Arduino IDE
   Comment=Arduino IDE 2.3.2
   Exec=/home/sagar/.arduino-ide_2.3.2_Linux_64bit/arduino-ide
   Icon=/home/sagar/.arduino-ide_2.3.2_Linux_64bit/resources/app/resources/icons/512x512.png
   Terminal=false
   Type=Application
   Categories=Development

STM32CubeMX
~~~~~~~~~~~
Create 'STM32CubeMX.desktop' file in ``~/.local/share/applications`` directory, and add the following content:

.. code-block::

   [Desktop Entry]
   Categories=Development
   Comment=STM32CubeMX 6.12.0
   Comment[en]=STM32CubeMX-Cube 6.12.0
   Encoding=UTF-8
   Exec=/home/sagar/STM32CubeMX/STM32CubeMX
   Icon=/home/sagar/STM32CubeMX/help/STM32CubeMX.ico
   Name=STM32CubeMX
   Name[en]=STM32CubeMX
   Path=/home/sagar/STM32CubeMX
   Type=Application
   X-KDE-SubstituteUID=false
   X-KDE-Username=root
   StartupWMClass=com-st-microxplorer-maingui-STM32CubeMX

``STM32CubeMX`` icon does not appear on dock. The last three lines solve the problem. 

Update desktop database.

.. code-block:: bash

   update-desktop-database ~/.local/share/applications

.. note::
   Make sure, the executable file has permission for execution. If not, you can change it as:

   .. code-block:: bash

      sudo chmod +x <path/to/executable>


3. STM32CubeProgrammer Setup
----------------------------

``STM32Cube_Programmer_CLI`` is not on environment by default. So, create a symbolic link to your ``STM32_Programmer_CLI`` in ``~/.local/bin``.

.. code-block:: bash

   mkdir -p ~/.local/bin # if does not exist
   ln -s ~/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI ~/.local/bin/STM32_Programmer_CLI


4. Git Setup
------------

Set username and email.

.. code-block:: bash

   git config --global user.name "Your Name"
   git config --global user.email "your.email@example.com"

Set default code editor.

.. code-block:: bash

   git config --global core.editor "code --wait"


Verify configurations.

.. code-block:: bash

   git config --list


5. SSH Setup
------------
To push code on repository using ``https``, you need to enter password every time. So, we use ``ssh`` for authentication.

Generate an SSH key:

.. code-block:: bash

   ssh-keygen -t ed25519 -C "your_email@example.com"

Press ``Enter`` to save the key to the default location.

Add the SSH key to the agent:

.. code-block::

   eval "$(ssh-agent -s)"
   ssh-add ~/.ssh/id_ed25519

See the ssh-key.

.. code-block:: 
   
   cat ~/.ssh/id_ed25519.pub

Add the ssh-key to your github account. Go to ``Github > Settings > SSH and GPG Keys``. Add new ssh key.
