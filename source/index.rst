.. Embedded Tutorials master file, created by
   sphinx-quickstart on Wed Sep 11 10:27:34 2024.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. toctree::
   :titlesonly:
   :maxdepth: 2
   :caption: Contents:
   :hidden:

   getting_started
   arduino_basics_tutorial
   stm32_basics_tutorial
   intermediate_tutorial
   highlights

.. note::
   This tutorial is tailored for **students of IOE, Pulchowk Campus**, addressing their specific requirements and constraints. In some sections, students may be required to contact the team for further assistance. We are open to suggestions and contributions from students, and we will be happy to include them in this tutorial.

Embedded Tutorials
==================

In this **Embedded Tutorials**, we will guide you through programming **Arduino**, **STM32 controllers**, **ESP32**, and **Raspberry Pi Pico**, sharing the techniques and approaches we commonly use. We will focus more on **STM32 controllers** from the basics, while also providing links for the basics of **Arduino Programming**. We generally use the **Arduino IDE** for programming **ESP32** and **Raspberry Pi Pico**, and **STM32CubeMX** and **STM32CubeProgrammer** for **STM32 controllers**.

.. important::
   After completing this tutorial, you will be able to:

   - Program these controllers.
   - Use them for controlling actuators, communication, interfacing sensors, writing CRC, and more.
   - Accelerate your learning and use this tutorial as a reference for your projects.

.. note::
   We are continuously adding more content to this tutorial. If you contribute, we will be happy to include your content in this tutorial.


.. raw:: html

   <a href="getting_started.html">
      <h2 style="
       text-align: center; 
       color: #fff; 
       font-family: 'Cursive', 'Comic Sans MS', sans-serif; 
       font-weight: bold; 
       margin-top: 20px; 
       padding: 20px; 
       background-color: #2980b9;
       border-radius: 10px; 
       line-height: 1.5;">
       Let's Get Started with <br>
         <span style="
           color: #fff; 
           text-decoration: none; 
           font-size: 1.2em;">
            Embedded Tutorials
         </span>
      </h2>
   </a>


.. raw:: html

   <div class="carousel-container">
       <!-- First Row -->
       <div class="carousel">
           <div class="carousel-track" id="carousel-track-1">
               <div class="carousel-slide"><img src="_static/images/controllers/STM32F407G-DISC1_Blue.jpg" alt="STM32F407G-DISC1"></div>
               <div class="carousel-slide"><img src="_static/images/controllers/arduino_uno.jpg" alt="arduino"></div>
               <div class="carousel-slide"><img src="_static/images/controllers/esp32_wroom.jpg" alt="esp32_wroom"></div>
           </div>
       </div>

       <!-- Second Row -->
       <div class="carousel">
           <div class="carousel-track" id="carousel-track-2">
               <div class="carousel-slide"><img src="_static/images/program_logos/c_logo.png" alt="c_logo"></div>
               <div class="carousel-slide"><img src="_static/images/program_logos/python_logo.png" alt="python_logo"></div>
               <div class="carousel-slide"><img src="_static/images/program_logos/cpp_logo.png" alt="cpp_logo"></div>
           </div>
       </div>
   </div>


   <style>
       .carousel-container {
           display: flex;
           flex-direction: column;
           gap: 20px;
       }

       .carousel {
           position: relative;
           width: 100%;
           overflow: hidden;
           border: 2px solid #ccc;
           border-radius: 10px;
           margin: 0 auto;
       }

       .carousel-track {
           display: flex;
           transition: transform 0.5s ease-in-out;
       }

       .carousel-slide {
           min-width: 100%;
           height: 300px;
           display: flex;
           justify-content: center;
           align-items: center;
           overflow: hidden;
       }

       .carousel-slide img {
           max-width: 100%;
           max-height: 100%;
           object-fit: contain;
           display: block;
       }
   </style>

   <script>
       const track1 = document.querySelector('#carousel-track-1');
       const slides1 = Array.from(track1.children);
       const track2 = document.querySelector('#carousel-track-2');
       const slides2 = Array.from(track2.children);

       // Clone first and last slides for seamless looping
       const firstSlide1 = slides1[0].cloneNode(true);
       const lastSlide1 = slides1[slides1.length - 1].cloneNode(true);
       track1.appendChild(firstSlide1);
       track1.insertBefore(lastSlide1, slides1[0]);

       const firstSlide2 = slides2[0].cloneNode(true);
       const lastSlide2 = slides2[slides2.length - 1].cloneNode(true);
       track2.appendChild(firstSlide2);
       track2.insertBefore(lastSlide2, slides2[0]);

       // Update slide arrays after cloning
       const updatedSlides1 = Array.from(track1.children);
       const updatedSlides2 = Array.from(track2.children);

       // Set initial position to the first "real" slide
       let currentIndex1 = 1;
       let currentIndex2 = 1;
       const slideWidth1 = slides1[0].getBoundingClientRect().width;
       const slideWidth2 = slides2[0].getBoundingClientRect().width;
       track1.style.transform = `translateX(-${currentIndex1 * slideWidth1}px)`;
       track2.style.transform = `translateX(-${currentIndex2 * slideWidth2}px)`;

       function slideImages() {
           // First row slides left
           currentIndex1++;
           track1.style.transition = 'transform 0.5s ease-in-out';
           track1.style.transform = `translateX(-${currentIndex1 * slideWidth1}px)`;

           // Second row slides right
           currentIndex2--;
           track2.style.transition = 'transform 0.5s ease-in-out';
           track2.style.transform = `translateX(-${currentIndex2 * slideWidth2}px)`;

           // Reset position for seamless looping
           setTimeout(() => {
               if (currentIndex1 === updatedSlides1.length - 1) {
                   track1.style.transition = 'none';
                   currentIndex1 = 1;
                   track1.style.transform = `translateX(-${currentIndex1 * slideWidth1}px)`;
               }
               if (currentIndex2 === 0) {
                   track2.style.transition = 'none';
                   currentIndex2 = updatedSlides2.length - 2;
                   track2.style.transform = `translateX(-${currentIndex2 * slideWidth2}px)`;
               }
           }, 500); // Match the transition duration
       }

       setInterval(slideImages, 3000); // Change images every 3 seconds
   </script>
 