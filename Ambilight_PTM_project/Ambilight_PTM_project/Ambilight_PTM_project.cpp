
#include <iostream>
#include <wtypes.h>
#include <Winuser.h>
#include <Windows.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <functional>
#include <string>
#include <inttypes.h>
#include <iterator>
#include <algorithm>

#include"SerialClass.h"



int horizontal = 0;
int vertical = 0;
Serial VCP = Serial();
int segment = 1; //number of circle


struct rgb
{
	int red;
	int green;
	int blue;

	rgb()
	{
		red = 0;
		green = 0;
		blue = 0;
	}
};

rgb left, up, right;
std::string buffer, r, g, b;



void GetDesktopResolution(int& horizontal, int& vertical) 
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}


rgb getLeftColor(int&horizontal, int &vertical, BYTE *bitPointer) //left part of the screen
{

	int srednia_r = 0;
	int srednia_g = 0;
	int srednia_b = 0;
	int dzielnik = 0;

	rgb medium;

	int h = (horizontal * 4) / 2;
	int v = ((vertical) / 3);

	for (int i = 0; i < h; i += 4)
	{
		//for (int j = v; j < vertical; j++)
		for (int j = 0; j < ((vertical * 2) / 3); j++)
		{

			dzielnik++;
			srednia_r += (int)bitPointer[j * horizontal * 4 + i + 2];//GetRValue(color);
			srednia_g += (int)bitPointer[j * horizontal * 4 + i + 1];//GetGValue(color);
			srednia_b += (int)bitPointer[j * horizontal * 4 + i + 0];//GetBValue(color);

		}
	}
	
	medium.red = srednia_r / dzielnik;
	medium.green = srednia_g / dzielnik;
	medium.blue = srednia_b / dzielnik;
	return medium;

}

rgb getRightColor(int&horizontal, int &vertical, BYTE *bitPointer) //right part of the screen 
{

	int srednia_r = 0;
	int srednia_g = 0;
	int srednia_b = 0;
	int dzielnik = 0;

	rgb medium;

	int h = ((horizontal * 4) / 2);
	int v = ((vertical * 1) / 3);

	for (int i = h; i < horizontal * 4; i += 4)
	{
		
		for (int j = 0; j < ((vertical * 2) / 3); j++)
		{
			
			dzielnik++;
			srednia_r += (int)bitPointer[j * horizontal * 4 + i + 2];//GetRValue(color);
			srednia_g += (int)bitPointer[j * horizontal * 4 + i + 1];//GetGValue(color);
			srednia_b += (int)bitPointer[j * horizontal * 4 + i + 0];//GetBValue(color);
		}
	}

	
	medium.red = srednia_r / dzielnik;
	medium.green = srednia_g / dzielnik;
	medium.blue = srednia_b / dzielnik;
	return medium;

}

rgb getUpColor(int& horizontal, int& vertical, BYTE *bitPointer)
{
	int srednia_r = 0;
	int srednia_g = 0;
	int srednia_b = 0;
	int dzielnik = 0;

	rgb medium;
	int v = ((vertical * 2) / 3);

	for (int i = 0; i < horizontal * 4; i += 4) //  4 colours per pixel (Red,Green,Blue,Alpha)
	{
		for (int j = v; j < vertical; j++)
		{
			dzielnik++;
			srednia_r += (int)bitPointer[j * horizontal * 4 + i + 2];//GetRValue(color);
			srednia_g += (int)bitPointer[j * horizontal * 4 + i + 1];//GetGValue(color);
			srednia_b += (int)bitPointer[j * horizontal * 4 + i + 0];//GetBValue(color);
		}
	}

	
	medium.red = srednia_r / (dzielnik);
	medium.green = srednia_g / (dzielnik);
	medium.blue = srednia_b / (dzielnik);
	return medium;
}

void make_full(std::string &d) // np. 50 -> 050 // 1 -> 001
{
	std::string buf;

	while (d.length() < 3)
	{
		buf = d;
		d = "0" + buf;
	}
}

std::string make_table(char &desktop_area, BYTE *dc)
{
	switch (desktop_area)
	{
	case 'L':

		left = getLeftColor(horizontal, vertical, dc);
		r = std::to_string(left.red);
		make_full(r);
		g = std::to_string(left.green);
		make_full(g);
		b = std::to_string(left.blue);
		make_full(b);

		buffer = "1=" + r + "," + g + "," + b + ";";
		return buffer;


	case 'U':

		up = getUpColor(horizontal, vertical, dc);
		r = std::to_string(up.red);
		make_full(r);
		g = std::to_string(up.green);
		make_full(g);
		b = std::to_string(up.blue);
		make_full(b);

		buffer = "2=" + r + "," + g + "," + b + ";";
		return buffer;


	case 'R':

		right = getRightColor(horizontal, vertical, dc);
		r = std::to_string(right.red);
		make_full(r);
		g = std::to_string(right.green);
		make_full(g);
		b = std::to_string(right.blue);
		make_full(b);

		buffer = "3=" + r + "," + g + "," + b + ";";
		return buffer;


	default:
		buffer = "error";
		return buffer;
	}
}


void sending_colors(BYTE* bitPointer)
{
	std::string data;
	char buffer;
	const char *buf = &buffer; //pointer to buffer

	int counter = 0;
	char L, U, R; //	rgb L, U, R; // RGB of Left, Up and Right desktop area
	L = 'L';
	U = 'U';
	R = 'R';

	char recvBuff[3];


	data = make_table(L, bitPointer);
	VCP.WriteData(data.c_str(), 14); //sending data (e.g 1=001,255,100;)
	std::cout << data << " | ";

	while (VCP.ReadData(recvBuff, 3) == -1); //waiting for 'ACK'
	//

	data = make_table(U, bitPointer);
	VCP.WriteData(data.c_str(), 14);
	std::cout << data << " | ";

	while (VCP.ReadData(recvBuff, 3) == -1);
	//

	data = make_table(R, bitPointer);
	VCP.WriteData(data.c_str(), 14);
	std::cout << data << std::endl;

	while (VCP.ReadData(recvBuff, 3) == -1);

}


// https://stackoverflow.com/questions/10515646/get-pixel-color-fastest-way

void processScreen()
{
	HDC hdc, hdcTemp;
	RECT rect;
	BYTE* bitPointer;


	while (true)
	{
		hdc = GetDC(HWND_DESKTOP);
		HWND hWND_Desktop = GetDesktopWindow();
		GetWindowRect(hWND_Desktop, &rect);
		int MAX_WIDTH = rect.right;
		int MAX_HEIGHT = rect.bottom;

		hdcTemp = CreateCompatibleDC(hdc);
		BITMAPINFO bitmap;
		bitmap.bmiHeader.biSize = sizeof(bitmap.bmiHeader);
		bitmap.bmiHeader.biWidth = MAX_WIDTH;
		bitmap.bmiHeader.biHeight = MAX_HEIGHT;
		bitmap.bmiHeader.biPlanes = 1;
		bitmap.bmiHeader.biBitCount = 32;
		bitmap.bmiHeader.biCompression = BI_RGB;
		bitmap.bmiHeader.biSizeImage = MAX_WIDTH * 4 * MAX_HEIGHT;
		bitmap.bmiHeader.biClrUsed = 0;
		bitmap.bmiHeader.biClrImportant = 0;
		HBITMAP hBitmap2 = CreateDIBSection(hdcTemp, &bitmap, DIB_RGB_COLORS, (void**)(&bitPointer), NULL, NULL);
		SelectObject(hdcTemp, hBitmap2);
		BitBlt(hdcTemp, 0, 0, MAX_WIDTH, MAX_HEIGHT, hdc, 0, 0, SRCCOPY);

		// processing
		sending_colors(bitPointer);

		DeleteDC(hdcTemp);
		DeleteObject(hBitmap2);
		ReleaseDC(NULL, hdc);
	}
}

int main()
{
	std::cout << "Is connected? " << VCP.IsConnected(); //checking connection
	GetDesktopResolution(horizontal, vertical);

	processScreen();

	return 0;
}





