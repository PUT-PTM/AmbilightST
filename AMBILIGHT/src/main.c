/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
			
#include "ws2812b.h"

int main(void)
{

	WS2812B_SetRGB(0, 0, 255, 0, 0);
	WS2812B_SetRGB(0, 1, 0, 255, 0);
	WS2812B_SetRGB(0, 2, 0, 0, 255);
	WS2812B_SetRGB(0, 3, 255, 0, 0);
	WS2812B_SetRGB(0, 4, 0, 255, 0);
	WS2812B_SetRGB(0, 5, 0, 0, 255);
	WS2812B_SetRGB(0, 6, 0, 255, 0);
	WS2812B_SetRGB(0, 7, 0, 0, 255);
	WS2812B_SetRGB(0, 8, 0, 0, 255);
	WS2812B_SetRGB(0, 9, 255, 0, 0);
	WS2812B_SetRGB(0, 10, 0, 255, 0);
	WS2812B_SetRGB(0, 11, 0, 0, 255);
	WS2812B_SetRGB(0, 12, 255, 0, 0);
	WS2812B_SetRGB(0, 13, 255, 0, 0);
	WS2812B_SetRGB(0, 14, 0, 255, 0);
	WS2812B_SetRGB(0, 15, 0, 0, 255);
	WS2812B_SetRGB(0, 16, 255, 0, 0);
	WS2812B_SetRGB(0, 17, 255, 0, 0);

	while(1)
	{

	}
}
