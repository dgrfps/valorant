#include "Screen.hpp"

#include <iostream>
#include "wtypes.h"

using namespace std;

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void Screen::getSize() {
	while (Screen::width == 0)
	{
		GetDesktopResolution(width, height);
	}
}

int Screen::height = 0;
int Screen::width = 0;