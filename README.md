# Wireless-Air-Mouse

## Aim of the Project
The aim of the project is to design an Air Mouse which does not require a surface and works on the hand motion. To achieve this aim, the following objectives are fulfilled.
1. To develop a hardware interfacing module that works as a wireless air mouse.<br/>
2. To add some keyboard functions to air mouse which can be customized by user.<br/>
3. To design our module on a printed circuit board (PCB).

## Technical Approch
Firstly, for our project to work we need a sensor that can detect the rotational movement in all directions. For this we have selected MPU-6050 module which consists of accelerometer sensor, gyroscope sensor and temperature sensor. But we use gyroscope sensor as it can detect the rotational movement in all directions. The data that we get from the MPU sensor should be processed. So, for that we have chosen Arduino Uno as our processing unit as it supports the I2C communication. After processing the data, we need to transmit the data to the receiver which can be done in two ways either wired or wireless. We have chosen wireless medium because of its advantages over wired medium. <br/>

For the purpose of transmission and reception we need to choose a transmitter and receiver. For this we have various techniques and technologies such as Bluetooth, Zigbee, RF module etc. But we have chosen RF Module as it doesn’t need line of sight between the transmitter and receiver. Finally, there should be a processing unit at the receiver also so we choose Arduino Leonardo as it can establish micro USB to USB communication between PC and itself. By using the RF transmitter and receiver, the problem is that we cannot concurrently transmit multiple values as there is only single channel available so, we are processing all the values at a time and concatenating all the values into a string and transmitting through a single channel. We found a library called Wire.h where it provides the functions for the transmission of data from MPU-6050 to Arduino Uno through I2C interface communication protocol. For wireless transmission between RF transmitter and RF receiver we used a library called VirtualWire.h.
