# FreeRTOS_ATmega32

## What is this Repo for?

This Repo contains FreeRTOS files and basic module drivers to implement projects using FreeRTOS OS 

## How do set-up work? 

This Repo mainly contains 4 branches (main, SimpleTasks_Schedualing, BinarySemaphorm, MutixSemaphorm and Queue). 

> #### main branch
  containts the FreeRTOS, basic module drivers (ADC, UART, KEYPAD, LEDS), You can take them and use them directly in your project. 

> #### SimpleTasks_Scheduling branch
  contains simple application on using the FreeRTOS to simply scheduel 3 Tasks with different Priorities.
  
  ![SimpleTasks](https://github.com/SeifAhmed25/FreeRTOS_ATmega32/assets/64741466/0c58ad42-116d-43ca-a6d6-9a36faa57e45)

> #### BinarySemaphorm branch
  contains simple application on using the FreeRTOS to schedule 3 Tasks with different priorities one of them depending on an event (Button to be pressed).
  
  ![Task1, Task2, Task3 Binary Semaphorm](https://github.com/SeifAhmed25/FreeRTOS_ATmega32/assets/64741466/1fe3cc52-9eb0-4cac-a87c-75299a153163)

> #### MutixSemaphorm branch
  contains simple application on using the FreeRTOS to Schedule 2 Tasks with different priorities, both uses the same resouce (UART Module). 
  
  ![Task1 and Task2 Mutix Semaphorm](https://github.com/SeifAhmed25/FreeRTOS_ATmega32/assets/64741466/df843675-3783-4ee8-83b5-aa8008e6f08f)

> #### Queue branch
  contains simple application on using the FreeRTOS to scheduale 2 Tasks one of them is sending data to Data Queue and the other reads those data from queue
  
  ![Task to read string from queue](https://github.com/SeifAhmed25/FreeRTOS_ATmega32/assets/64741466/50456258-fbb2-4e44-b01d-26ca1ef8e27d)
  ![Task to receive string ](https://github.com/SeifAhmed25/FreeRTOS_ATmega32/assets/64741466/e3dfe132-3cc6-4618-ac7f-9711c9008db0)

## Hardware and Software Tools 

### MCU ATmega32 Microcontroller (16MHz Clock Frequency)

Note that Clock Frequency must be defined in the Configuration file of the FreeRTOS. 

### DockLight Software (very usefull here) 

You can use DockLight Software to check on sent/received data via UART Module using a serial USB/TTL Converter, make sure of using the same Baudrate configuration between Docklight and the ATmega32.  

### All applcations on all branches (except main branch) was implemented using Microchip Atmel Studio 

You can use them the application direct if you are using the same IDE or you can use the Drivers/FreeRTOS files and use them in a different IDE, but you mast take into consideration adding your relative paths to your enviroment. 
