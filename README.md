# ReactionGameWithArcadianLeds
## Objective
The goal of the project is to develop a reaction Game which has the below requirement using Erika -OS.
The hardware used is PSoC 5LP : CY8C5888LTI-LP097 
## Requirements for the game.
* Upon startup, the program will show a welcome message via the serial port.
* After pressing one of the two white buttons, the program will wait for a random time.
After waiting for 1s to 3s a random value (1 or 2) will be displayed on both 7segment displays
* The user has to press the right button in case a ‘1’ is displayed and the left button in
case a ‘2’ is displayed
* In case the correct button is being pressed, the measured reaction time in [ms] will be
shown and the game can be started again by pressing one of the two buttons.
* In case a wrong button is pressed, an error message will be displayed and the game
can be started again by pressing one of the two buttons.
* In case the user does not press a button within 1 s, the message “Too slow” will
appear and the game can be started again by pressing one of the two buttons.
* One game consists out of 10 rounds
* At the end of a game, print the score (i.e. correct number of button pressed), the total
time and the average time
## Requirements for the Arcadian Light
* make the game a bit fancier, we want to add some Arcadian style light effect. The
light effects may not interfere with rest of the functionality.
* We need to devlop a fader Led with the pattern 
![Image description](https://drive.google.com/file/d/12QK-17XQw2EhGz-Rc8hoEii-YXUuyc7G/view?usp=sharing)
* We need to develop a glower with the below table
![Image description](https://drive.google.com/file/d/1dI_KTpqcphNM-YTepk-eMJDEsbM2Dbjw/view?usp=sharing)

## Installation
* PSOC creator version 4.1 by Cypress Semiconductor is used as an IDE.

## About PSoC Creator IDE
* PSoC Creator is an Integrated Design Environment (IDE) that enables concurrent hardware and firmware editing, compiling and debugging of PSoC.
* The Top level design is schematic page in which analog and digital peripherals (Components) are connected as per application requirements.
* After configuring all the peripherals, firmware can be written, compiled, and debugged within PSoC Creator or exported to leading 3rd party IDEs such as IAR Embedded Workbench®, Arm® Microcontroller Development Kit, and Eclipse™.

## Working
* Clone the project into a local folder in your PC.
* Import the project into the PSOC Creator IDE.
* In the Top Level Design there are 3 schematic Pages : HMI, HMI Extension and System 
* The system page has a component which is responsible for OS configuration.
* The HMI , HMI extension are application level requirements.
* We generate the Code, the generated code folder present in the root folder.It has lower level drivers for the peripherals/components.
* There are two other folders in the root asw, bsw : asw for application software and bsw is the wrapper for the generated code for ease of usuage and readablity software.
* The main applictation files for the smart volume controller is present in the asw folder.
