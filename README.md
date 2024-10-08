# INAF Cosmic Rays Detector

<it> _The Cosmic Rays Detector is a project based in an INAF prototype._ </it>

<div align="center">




https://github.com/user-attachments/assets/698930dd-47ed-4191-8b07-490820b2f595





</div>

**Used Materials**

<pre>
  
- x2 Geiger Tubes
- Arduino UNO
- x1 LCD Display
- 3D Printed case
- Logic Gates
  
</pre>

<p align="center">

  <!--<img src="https://github.com/Marcolbr2001/6502_Computer/assets/66978947/97c4f9f9-d9a5-4a7c-9f70-d55d0c68c5f6" width="350" alt="accessibility text">-->
</p>

## Inside the Detector

INAF had supplied a prototype cosmic ray detector using two Geiger tubes placed in parallel.

![Geiger2](https://github.com/user-attachments/assets/c1eafa36-ae07-474a-81b6-512d50eea5cf)

To insulate the walls, two lead shields were placed on the sides so that the particles could pass through only first in one tube and then in the other, at each detection therefore, through an AND logic gate installed in the circuit, it was possible to discriminate between environmental particles and cosmic rays coming from above.

## Functioning

![Geiger](https://github.com/user-attachments/assets/dd59a804-b091-49b4-8562-e0e31adaddfa)

Through an Arduino UNO microcontroller, data were collected and plotted into different graphs by calculating average values in centi-becquerel to study different environments.
<br><br>
Cosmic Rays, as can be seen from the video, are detected by a higher "beep" sound, however, in this particular video conditions, the detector is not positioned well and doesn't reveal real cosmic rays radiation.

