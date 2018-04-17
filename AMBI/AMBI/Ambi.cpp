#include<iostream>
#include<Windows.h>
#include <wtypes.h>

using namespace std;

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
rgb getLeftColor(int&horizontal, int &vertical) //lewa czêœæ ekranu 
{

	int srednia_r = 0;
	int srednia_g = 0;
	int srednia_b = 0;
	HDC dc = GetDC(NULL); //pobieranie ekranu 

	rgb medium;
	for (int i = 0; i < (horizontal / 2); i += 100)
	{
		for (int j = 0; j < ((vertical * 2) / 3); j += 100)
		{

			COLORREF color = GetPixel(dc, i, j);
			srednia_r += GetRValue(color);
			srednia_g += GetGValue(color);
			srednia_b += GetBValue(color);
		}
	}
	ReleaseDC(NULL, dc);

	//liczenie œrednich sk³adowych (RGB) koloru lewej macierzy (800x600) 
	int dzielnik = ((horizontal / 100)*(vertical * 2 / 100)) / 3;
	medium.red = srednia_r / dzielnik;
	medium.green = srednia_g / dzielnik;
	medium.blue = srednia_b / dzielnik;
	return medium;

}

rgb getRightColor(int&horizontal, int &vertical) //prawa czêœæ ekranu 
{

	int srednia_r = 0;
	int srednia_g = 0;
	int srednia_b = 0;
	HDC dc = GetDC(NULL); //pobieranie ekranu 

	rgb medium;
	for (int i = (horizontal / 2); i < horizontal; i += 100)
	{
		for (int j = ((vertical * 2) / 3); j < vertical; j += 100)
		{

			COLORREF color = GetPixel(dc, i, j);
			srednia_r += GetRValue(color);
			srednia_g += GetGValue(color);
			srednia_b += GetBValue(color);
		}
	}
	ReleaseDC(NULL, dc);

	//liczenie œrednich sk³adowych (RGB) koloru prawej macierzy (800x600) 
	int dzielnik = ((horizontal / 100)*(vertical * 2 / 100)) / 3;
	medium.red = srednia_r / dzielnik;
	medium.green = srednia_g / dzielnik;
	medium.blue = srednia_b / dzielnik;
	return medium;

}

rgb getUpColor(int& horizontal, int& vertical)
{
	int srednia_r = 0;
	int srednia_g = 0;
	int srednia_b = 0;
	HDC dc = GetDC(NULL);

	rgb medium;
	for (int i = 0; i < horizontal; i += 100) //uwzglêdniamy co 100 pixel w celu ograniczenia narzutów czasowych zwi¹zanych z liczeniem œredniej z macierzy 
	{
		for (int j = 0; j < (vertical / 3); j += 100)
		{
			COLORREF color = GetPixel(dc, i, j);
			srednia_r += GetRValue(color);
			srednia_g += GetGValue(color);
			srednia_b += GetBValue(color);
		}
	}
	ReleaseDC(NULL, dc);

	//liczenie œrednich sk³adowych (RGB) koloru macierzy górnej (1600x300) 
	int dzielnik = ((horizontal / 100)*(vertical / 100)) / 3;
	medium.red = srednia_r / (dzielnik);
	medium.green = srednia_g / (dzielnik);
	medium.blue = srednia_b / (dzielnik);
	return medium;
}

int main() {

	int horizontal = 0;
	int vertical = 0;
	GetDesktopResolution(horizontal, vertical);
	cout << horizontal << '\n' << vertical << '\n';

	rgb up = getUpColor(horizontal, vertical);
	cout << "UP: " << endl << "Red: " << up.red << endl << "Green: " << up.green << endl << "Blue: " << up.blue << endl << endl;

	rgb left = getLeftColor(horizontal, vertical);
	cout << "LEFT: " << endl << "Red: " << left.red << endl << "Green: " << left.green << endl << "Blue: " << left.blue << endl << endl;

	rgb right = getRightColor(horizontal, vertical);
	cout << "RIGHT: " << endl << "Red: " << right.red << endl << "Green: " << right.green << endl << "Blue: " << right.blue << endl << endl;

	cin.get();
	return 0;
}