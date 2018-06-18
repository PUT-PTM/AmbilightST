#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "ws2812b.h"

#include "tm_stm32f4_usb_vcp.h"
#include "tm_stm32f4_disco.h"
#include "defines.h"

#define USE_USB_OTG_FS

int RGB_array[3][3];


//calculating RGB values
void calc_RGB(char* buf, int* output)
{


	output[0] = (buf[2] - '0')*100 + (buf[3] - '0')*10 + (buf[4] - '0'); // r
	output[1] = (buf[6] - '0')*100 + (buf[7] - '0')*10 + (buf[8] - '0'); // g
	output[2] = (buf[10] - '0')*100 + (buf[11] - '0')*10 + (buf[12] - '0'); // b

}

//updating diodes state (const value: 3)
void set_AL_LED(int input[][3], int offset)
{
	int i_offset = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
			WS2812B_SetRGB(0, j + i_offset, input[i][0], input[i][1], input[i][2]);
		i_offset += offset;
	}
}

int main(void)
{
	/* System Init */
	SystemInit();
	WS2812B_Init();

	/* Initialize LED's. Make sure to check settings for your board in tm_stm32f4_disco.h file */
	TM_DISCO_LedInit();

	/* Initialize USB VCP */
	TM_USB_VCP_Init();

	char rBuf[15] = { 0 }; // sending buffer
	char sBuf[3] = "ACK"; // receiving buffer

	while (1)
	{
		if (TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED) //checking connection
		{
			TM_DISCO_LedOff(LED_RED);
			TM_DISCO_LedOn(LED_GREEN);

			if (TM_USB_VCP_Gets(&rBuf, 15) > 0) //receiving data
		    {
				TM_USB_VCP_Send(&sBuf[0], 3); // sending 'ACK'

				switch (rBuf[0]) // number of circle
				{
					case '1':
						calc_RGB(rBuf, RGB_array[1]);
						break;

					case '2':
						calc_RGB(rBuf, RGB_array[2]);
						break;

					case '3':
						calc_RGB(rBuf, RGB_array[0]);
						break;
				}
		    }
		}
		else
		{
			TM_DISCO_LedOn(LED_RED);
			TM_DISCO_LedOff(LED_GREEN);
		}

		set_AL_LED(RGB_array, 8);
	}
}
