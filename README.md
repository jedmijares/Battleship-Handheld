# EE 287 Final Project

This project was created as the final project for EE 287 (Intro to Embedded Systems).

## Building

Battleship was written and may be built with Keil uVision5.

## Description and Operation

We implemented _Battleship_ on a Texas Intrument Tiva C Series Launchpad (EK-TM4C123GXL). When booted up, a short credit message is displayed on a Nokia 5110 screen. The user may press any button to proceed to the game board. Here, they will use the D-pad to navigate and the select button to fire at the selected square. The game will display an **X** for each square with a targeted ship and a **0** for each targeted empty square. The game is completed when the player has sunken each ship.

## Explanation of Design Choices

We used an 8x8 grid for the board as it fit nicely on the Nokia's 48x84 pixel screen. This left enough space for 6 rows of 4 characters, which we used to display the number of shots fired, the number of successful hits, and which ships had been successfully sunk. In software, the board is a 2 dimensional array of _Square_ structs, which keep track of whether a tile has been shot and an ID for the ship that resides there (or lack thereof).

## Parts List

* TM4C123G LaunchPad™ Evaluation Kit
* Nokia 5110 Screen Breakout Board
* Piezo Buzzer
* 10kR Resistor (6)
* Pushbutton Switch (6)
