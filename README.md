# Autonomous-Maze-Solving-Robot-with-OpenThread-Synchronisation

This project implements a distributed multi-robot control system using two Pololu mobile robots and nRF52840 microcontrollers. The goal of the project is to coordinate multiple robots to solve a maze navigation task using wireless communication and embedded control. The system combines embedded systems, wireless networking, and robot coordination.

## System Architecture
The system consists of three main components:
Robot 1
Robot 2
Central control node (nRF52840 dongle connected to a host PC) Each robot is connected to an nRF52840 module via UART, which acts as the communication interface between the robot controller and the wireless network. The robots communicate through a Thread wireless network using the CoAP protocol, enabling synchronized commands and coordination between robots. Main communication layers: Robot Controller ↔ UART ↔ nRF52840 nRF52840 ↔ Thread Network ↔ nRF52840 Dongle Dongle ↔ Robot2

## Key Features
Distributed multi-robot control architecture Wireless robot coordination using Thread / CoAP Low-level communication via UART Embedded firmware developed with Zephyr RTOS Synchronized robot commands through wireless networking Autonomous maze navigation task

Technologies Used
Embedded Systems Zephyr RTOS nRF52840 microcontroller UART communication Networking OpenThread CoAP protocol IEEE 802.15.4 wireless communication Programming C (embedded firmware) Python (host-side scripts) Robotics Pololu mobile robot platform Sensor-based navigation

## Project Motivation

This project explores how distributed communication and synchronization mechanisms can be used to coordinate multiple robots performing autonomous tasks. Multi-robot systems are an important research direction in robotics, especially for applications such as swarm robotics, autonomous vehicles, and distributed sensing systems.

## Future Work

Possible future improvements include: decentralized coordination algorithms cooperative exploration strategies improved maze solving algorithms multi-robot path planning

## Repository Structure

|-- maze-client
|    |--.vscode
|       |--settings.json
|    |--build
|       |--maze-project.uf2
|    |--include
|       |--follow_segment.h
|       |--leds.h
|       |--maze_solve.h
|       |--multi_display.h
|       |--path.h
|       |--sensors.h
|       |--turn.h
|       |--uart_rx.h
|     |--CMakeList.txt
|     |--Follow_segement.c
|     |--leds.c
|     |--main.c
|     |--maze_solve.c
|     |--multi_display.c
|     |--path.c
|     |--pico_sdk_import.cmake
|     |--readme.txt
|     |--sensors.c
|     |--turn.c
|     |--uart_rx.c
|-- maze-server
|    |--.vscode
|       |--settings.json
|    |--build
|       |--maze-project.uf2
|    |--include
|       |--follow_segment.h
|       |--maze_solve.h
|       |--multi_display.h
|       |--path.h
|       |--sensors.h
|       |--turn.h
|       |--uart_rx.h
|     |--CMakeList.txt
|     |--Follow_segement.c
|     |--main.c
|     |--maze_solve.c
|     |--multi_display.c
|     |--path.c
|     |--pico_sdk_import.cmake
|     |--sensors.c
|     |--turn.c
|     |--uart_rx.c
|
|-- README
|-- roboter
## Project Structure

```
maze-project
│
├── maze-client
│   ├── .vscode
│   │   └── settings.json
│   ├── build
│   │   └── maze-project.uf2
│   ├── include
│   │   ├── follow_segment.h
│   │   ├── leds.h
│   │   ├── maze_solve.h
│   │   ├── multi_display.h
│   │   ├── path.h
│   │   ├── sensors.h
│   │   ├── turn.h
│   │   └── uart_rx.h
│   │
│   ├── CMakeLists.txt
│   ├── follow_segment.c
│   ├── leds.c
│   ├── main.c
│   ├── maze_solve.c
│   ├── multi_display.c
│   ├── path.c
│   ├── pico_sdk_import.cmake
│   ├── readme.txt
│   ├── sensors.c
│   ├── turn.c
│   └── uart_rx.c
│
├── maze-server
│   ├── .vscode
│   │   └── settings.json
│   ├── build
│   │   └── maze-project.uf2
│   ├── include
│   │   ├── follow_segment.h
│   │   ├── maze_solve.h
│   │   ├── multi_display.h
│   │   ├── path.h
│   │   ├── sensors.h
│   │   ├── turn.h
│   │   └── uart_rx.h
│   │
│   ├── CMakeLists.txt
│   ├── follow_segment.c
│   ├── main.c
│   ├── maze_solve.c
│   ├── multi_display.c
│   ├── path.c
│   ├── pico_sdk_import.cmake
│   ├── sensors.c
│   ├── turn.c
│   └── uart_rx.c
│
├── README.md
└── robot.png
```
