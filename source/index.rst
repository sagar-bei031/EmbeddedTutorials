.. Embedded Tutorials master file, created by
   sphinx-quickstart on Wed Sep 11 10:27:34 2024.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. important::
   This tutorial is tailored for **students of IOE, Pulchowk Campus**, addressing their specific requirements and constraints.

Embedded Tutorials
==================

.. toctree::
   :titlesonly:
   :maxdepth: 2
   :caption: Contents:
   :hidden:

   getting_started
   stm32_basics_tutorial
   intermediate_tutorial
   highlights


.. raw:: html

   <div class="carousel-container">
       <!-- First Row -->
       <div class="carousel">
           <div class="carousel-track" id="carousel-track-1">
               <div class="carousel-slide"><img src="_static/images/controllers/arduino_uno.jpg" alt="arduino"></div>
               <div class="carousel-slide"><img src="_static/images/controllers/STM32F407G-DISC1_Blue.jpg" alt="STM32F407G-DISC1"></div>
               <div class="carousel-slide"><img src="_static/images/controllers/esp32_wroom.jpg" alt="esp32_wroom"></div>
           </div>
       </div>

       <!-- Second Row -->
       <div class="carousel">
           <div class="carousel-track" id="carousel-track-2">
               <div class="carousel-slide"><img src="_static/images/controllers/arduino_uno.jpg" alt="arduino"></div>
               <div class="carousel-slide"><img src="_static/images/controllers/STM32F407G-DISC1_Blue.jpg" alt="STM32F407G-DISC1"></div>
               <div class="carousel-slide"><img src="_static/images/controllers/esp32_wroom.jpg" alt="esp32_wroom"></div>
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
           width: 80%;
           max-width: 600px;
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
           height: 200px;
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

