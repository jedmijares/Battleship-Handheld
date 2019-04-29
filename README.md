# Battleship Handheld

This project was created as the final project for EE 287 (Intro to Embedded Systems).

## Compiling

Battleship was written and built with Keil uVision5.

## Description and Operation

If you are not familiar with the board game Battleship, you can read about it [here.](https://en.wikipedia.org/wiki/Battleship_(game))

We implemented the game on a Texas Intrument Tiva C Series Launchpad (EK-TM4C123GXL). When booted up, a short credit message is displayed on a Nokia 5110 screen. The user may press any button to proceed to the game board. The time at which they press the button is used as a seed for a randomization function, and we use this function to randomly place a length 2, length 3, and length 4 ship on an 8x8 grid. Next, the player will use the D-pad to navigate and the select button to fire at the selected square. The game will display an X for each square with a targeted ship and a 0 for each targeted empty square. The game is completed when the player has sunken each ship. At this point, a win screen is displayed, showing the number of shots the player had to fire to complete the game. They player can hit any button to reset the game and play again.

## Explanation of Design Choices

We were attracted to using the Nokia 5110 screen, as Dr. Valvano had provided a library for it as part of his online Embedded Systems course, which we referred to often throughout this semester. We settled upon implementing Battleship after discovering that the Nokia screen flickered a lot when sprites were quickly moved across it.

We used an 8x8 grid for the board as it fit nicely on the Nokia's 48x84 pixel screen. This left enough space for 6 rows of 4 characters, which we used to display the number of shots fired, the number of successful hits, and which ships had been successfully sunk. In software, the board is a 2 dimensional array of _Square_ structs, which keep track of whether a tile has been shot and an ID for the ship that resides there (or lack thereof).

The PCB features several extraneous components. These include a terminal block for breaking out UART pins, an extra unused button, and several rows of jumper pins. These serve no purpose in the current design, but were added in case we decided to implement a feature that would require them.

## Parts List

* TM4C123G LaunchPad Evaluation Kit
* Nokia 5110 Screen Breakout Board
* Piezo Buzzer
* 10kR Resistor (5)
* Pushbutton Switch (5)

### Optional Components

* 330R Resistor (may be used to enable the backlight)
* 4-pin terminal block (breaks out the UART pins, which currently are not used)
* 10kR Resistor (for extra button that currently serves no purpose)
* Pushbutton Switch (extra button that currently serves no purpose)

## Block Diagram

[Code Block Diagram](https://github.com/jedmijares/EE-287-Final-Project/blob/master/Media/Code%20Block%20Diagram.pdf)

## Explanation of Major Components

The Tiva board is crucial to the project, and controls all the other components and handles the processing for the game itself.

The Tiva communicates with the Nokia 5110 screen serially and uses it to communicate all visual output.

A piezo buzzer is also implemented. Whenever a button is pressed, the SysTick timer is used to oscillate the buzzer pin for a specified number of milliseconds.

The PCB was designed in Autodesk EAGLE. Relevant design files are in the EAGLE folder.
