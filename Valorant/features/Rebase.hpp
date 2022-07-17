#pragma once

#include "../utils/Basic.hpp"

class Rebase {
public:
	static void loop() {
		Screen::getSize();
		int x = Screen::width / 2;
		int y = Screen::height / 2;

		RGBTRIPLE rgbTriple;
		HDC hdc = GetDC(NULL);

		int targetX = 0, targetY = 0;
		bool enabled = false;

		while (1) {
			vec2 SIZE = settings.size;

			if (!enabled && (GetAsyncKeyState(VK_XBUTTON1) && KEYUP))
			{
				Beep(349, 200);
				this_thread::sleep_for(25ms);
				Beep(349, 200);
				enabled = true;
			}
			else if (enabled && (GetAsyncKeyState(VK_XBUTTON1) && KEYUP))
			{
				Beep(349, 200);
				enabled = false;
			}

			if ((enabled || (GetAsyncKeyState(VK_XBUTTON2) && KEYDOWN)) && !(GetAsyncKeyState(VK_LBUTTON) && isDown)) {
				for(int _y = 0; _y < SIZE.y; _y++)
					for (int _x = 0; _x < SIZE.x; _x++)
					{
						targetY = (_y < SIZE.y / 2) ? (((SIZE.y / 2) - _y) * -1) : ((SIZE.y / 2) - _y);
						targetX = (_x < SIZE.x / 2) ? (((SIZE.x / 2) - _x) * -1) : ((SIZE.x / 2) - _x);

						COLORREF color = GetPixel(hdc, x + targetX, y + targetY);
						rgbTriple.rgbtRed = GetRValue(color);
						rgbTriple.rgbtGreen = GetGValue(color);
						rgbTriple.rgbtBlue = GetBValue(color);

						Color::HSV rgbToHue = toHSV((float)rgbTriple.rgbtRed, (float)rgbTriple.rgbtGreen, (float)rgbTriple.rgbtBlue);
						Color::ColorName name = Categorize(rgbToHue);

						if (name == Color::Magenta)
						{
							if (rgbToHue.s * 100 <= 80 && rgbToHue.s * 100 > 15)
							{
								if ((enabled || (GetAsyncKeyState(VK_XBUTTON2) && KEYDOWN)) && !(GetAsyncKeyState(VK_LBUTTON) && isDown)) {
									this_thread::sleep_for(settings.delay);
									keybd_event(VK_K, 0, KEYDOWN, 0);
									this_thread::sleep_for(10ms);
									keybd_event(VK_K, 0, KEYUP, 0);
									break;
								}
							}
						}
					}
			}
			else
			{
				this_thread::sleep_for(10ms);
			}
		}
	};
};