#pragma once

#include <Windows.h>
#include <thread>

#include "../utils/Screen.hpp"
#include "../utils/Keys.hpp"
#include "../settings/Settings.h"
#include "../utils/colors/HSV.hpp"

class Trigger {
public:
	static void loop() {
		int x = Screen::getSize().x / 2;
		int y = Screen::getSize().y / 2;

		RGBTRIPLE rgbTriple;
		HDC hdc = GetDC(NULL);

		int targetX = 0, targetY = 0;
		while (Settings::running)
		{
			if ((GetAsyncKeyState(Settings::triggerBind) & KEYDOWN) && !(GetAsyncKeyState(VK_LBUTTON) & KEYDOWN)) {
				for(int _y = 0; _y < Settings::triggerHeight; _y++)
					for (int _x = 0; _x < Settings::triggerWidth; _x++)
					{
						targetY = (_y < Settings::triggerHeight / 2) ? (((Settings::triggerHeight / 2) - _y) * -1) : ((Settings::triggerHeight / 2) - _y);
						targetX = (_x < Settings::triggerWidth / 2) ? (((Settings::triggerWidth / 2) - _x) * -1) : ((Settings::triggerWidth / 2) - _x);

						COLORREF color = GetPixel(hdc, x + targetX, y + targetY);
						rgbTriple.rgbtRed = GetRValue(color);
						rgbTriple.rgbtGreen = GetGValue(color);
						rgbTriple.rgbtBlue = GetBValue(color);

						Color::HSV rgbToHue = Color::toHSV((float)rgbTriple.rgbtRed, (float)rgbTriple.rgbtGreen, (float)rgbTriple.rgbtBlue);
						Color::ColorName name = Color::Categorize(rgbToHue);

						if (name == Settings::triggerColor)
						{
							if (rgbToHue.s * 100 <= Settings::triggerTension[1] && rgbToHue.s * 100 > Settings::triggerTension[0])
							{
								if ((GetAsyncKeyState(Settings::triggerBind) && KEYDOWN) && !(GetAsyncKeyState(VK_LBUTTON) && KEYDOWN)) {
									std::this_thread::sleep_for(chrono::milliseconds(static_cast<long>(Settings::triggerDelay)));

									keybd_event(Settings::triggerFireKey, 0, KEYPRESS, 0);
									this_thread::sleep_for(10ms);
									keybd_event(Settings::triggerFireKey, 0, KEYUP, 0);

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