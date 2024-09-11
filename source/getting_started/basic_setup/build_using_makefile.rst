
Build Using Makefile
====================

1. Open your project folder. It is better to use ``VSCODE``.

2. Open ``terminal`` at your project folder.

3. Build project using ``make`` command.

   It is very easy this time to build the project using Makefile. You just need to use the ``make`` command and nothig.
   
   .. code-block:: bash
   
      make -j
   
   ``-j`` is for doing all jobs code at once. It speeds up build time using parallel processing. If you want to do ``n`` jobs at once, use ``-jn``. For example, executing ``8`` tasks at once:
   
   .. code-block:: bash
   
      make -j8

You will learn more about ``make`` and ``makefile`` throughout this tutorial.  
