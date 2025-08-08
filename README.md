# Hand_Gesture_Controlled_Bot

A Hand Gesture Controlled Robot uses advanced motion-sensing technology to interpret hand gestures and translate them into movement commands for the robot. By utilizing sensors like accelerometers, this system provides an intuitive and contactless way to control a robot's movement.

## Overview
This project focuses on creating a robot that responds to hand gestures detected by an accelerometer. The gesture data is processed and sent wirelessly to the robot using nRF24 modules. The robot's microcontroller decodes the received signals and moves accordingly, enabling seamless interaction without physical controllers.

## Key Features
- Gesture-Based Control: Uses hand movements to direct the robot.
- Wireless Communication: Transfers data between the gesture controller and the robot.
- Compact Design: Powered by Arduino Nano and lightweight components.
- Scalable: Can be adapted for various robotic applications.

## Hardware Requirements
- Arduino Nano
- nRF24 Wireless Module
- ADXL345 Accelerometer
- Motor Driver Module
- DC Motors
- Power Supply

## Software Requirements
- Arduino IDE

## Working Principle
- **Gesture Recognition**: The accelerometer detects changes in hand orientation and motion along the X, Y, and Z axes.
These readings represent specific gestures, such as moving forward, backward, or turning.
- **Data Transmission**:The transmitter unit sends the processed gesture data wirelessly to the robot using the nRF24 module.
- **Signal Interpretation**:The robot’s microcontroller interprets the received data and converts it into movement commands.
- **Bot Movement**:The robot executes actions like moving forward, backward, left, or right based on the commands.

## Connections
- **Nano-nRF24**
 ![nrf](https://github.com/user-attachments/assets/f73c6d5b-2127-43ca-b812-1812544bdc8c)
- **Transmitter**
 ![new t2](https://github.com/user-attachments/assets/7f817e12-d2ef-4b5e-9628-272f1373f8e4)
- **Receiver**
 ![new r](https://github.com/user-attachments/assets/7066f170-27da-4406-9984-7900ca1f41ef)


