# EMBEDDED SYSTEMS - SHAPE THE WORLD
A two-module embedded systems MOOC based on an ARM Cortex-M4F microcontroller from the University of Texas at Austin through [**edX**](https://courses.edx.org/).

Date: April - Jully 2017

This 16-week class is split into two 8-week classes : 
- **UT.6.10x Embedded Systems - Shape The World: [Microcontroller Input/Output](https://www.edx.org/course/embedded-systems-shape-world-utaustinx-ut-6-10x)** includes Modules 1 to 10. \
  [**Certificate**](https://courses.edx.org/certificates/206f7b85de4c4ae3b04a4c7d53ae55fc) available.
- **UT.6.20x Embedded Systems - Shape The World: [Multi-Threaded Interfacing](https://www.edx.org/course/embedded-systems-shape-world-multi-utaustinx-ut-6-20x)** includes Modules 11 to 16. \
  [Certificate](https://courses.edx.org/certificates/5fa99726743b447d9b7b25044b0fedef) available.

You can find a **[syllabus](syllabus.md)** of these 2 courses.

Every lab is given as an existant project with a grading system TExaS that remotely permits to evaluate my work (and push the grade on edX MOOC). \
As a consequence, for each lab assignment, I completed an existant project given by the teaching staff with the requirements.

My contributions include:
- gloabal declarations (essentially for ports) and/or declarations in header files. 
- functions defintion if already declared by teachers.
- functions implementation otherwise.

In most of the cases, there are all these alternatives (except with the two first introduction labs).

## Common Files

There are some file types which will appear in every lab assignment.

`***.uvproj` `***.uvgui` `***.uvopt` - uVision files (open `***.uvproj` to get the full project) \
`***.axf` `TExaS.h` `texas.o` - autograder files \
`tm4c123gh6pm.h` - useful address definitions for launchpad \
`startup.s` - assembly startup file

## Requirements

**[Kiel uVsion 4](https://www.keil.com/demo/eval/armv4.htm)** - All the code/debug were done on this IDE. \
**[Stellaris/Tiva LaunchPad](http://www.ti.com/tool/ek-tm4c123gxl)** - Everything is meant to work on a EK-TM4C123G launchpad. \
**[Electronic Components](http://edx-org-utaustinx.s3.amazonaws.com/UT601x/worldwide.html)** - Some labs requires a set of extra electronic parts.
