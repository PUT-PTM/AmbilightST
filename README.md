## Overview
Ambilight is a backgroundlight system, mounted on the display. We wrote our own software application to control and monitor the computer display. With the ambilight, it's possible to generate light in real-time that simulates the color palette on the computer display.

## Description
The first library which we used is STM32F4xx WS2812B library by Manik. The library is based on DMA, which transfers LED colour data directly into ODR register of the GPIO. Half of the GPIO peripheral is used (pins 0 to 7). Data is bursted via DMA on TIM1 Update trigger. The second library which we used is Virtual COM Port (VCP) for STM32F4 from a website: https://stm32f4-discovery.net/2014/08/library-24-virtual-com-port-vcp-stm32f4xx/
This library provides Virtual COM port on USB OTG. This means, that you don’t need external USB->UART converter (like FTDI) to communicate with computer. STM32F4xx will be seen to computer like COM port.  
In the Visual Studio we used Windows API to read colors from the screen. In our application we use a bitmap. This solution was used to make the reaction to change colors faster.
For Serial Communication we use library for Arduino (with some changes): 
https://playground.arduino.cc/Interfacing/CPPWindows

## Tools
3x diodes WS2812B.
STM32F4xx,
Impulse Power Supply 3,3V,
USB 2.0/3.0,
MicroUSB,
1 resistor 100 Ω,

## How to run
It’s easy. We connect the power supply and both USB cables to the computer.
Then you have to find out the COM number corresponding to your serial port, Open Device Manager by right clicking on **My Computer** icon and selecting **Manage → Device Manager**. Under Ports(COM & LPT) you can see the parallel and serial ports (COM) detected by your system. You will see your STM as **“USB Serial Port (COM *number*)”**. In Visual Studio project in Serial() constructor you have to change port number for corresponding one. 

*Serial::Serial()
{
	//We're not yet connected
	this->connected = false;

	std::string port = **"COM4"**;
	std::wstring stemp = s2ws(port);
	LPCWSTR portName = stemp.c_str();
(...)
}*

After we enable in the Visual Studio an application that supports reading and calculating pixel values ​​for an image on the screen. And the result is a light that changes depending on the colors on the screen.

## How to compile
You just have to run the project in a console of Visual Studio 2017.

## Future improvements
We are thinking about using in the future LED strips that will create a frame around the monitor.

## Attributions
###### Virtual COM Port
https://stm32f4-discovery.net/2014/08/library-24-virtual-com-port-vcp-stm32f4xx/

###### Library WS2812B
https://github.com/Tomasz-Mankowski/STM32F4xx-WS2812B-lib

###### Serial Communication
https://playground.arduino.cc/Interfacing/CPPWindows

## License
MIT

###### Credits
Agata Błachowiak
Sandra Bocian
Olga Kryspin

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor: Tomasz Mańkowski
