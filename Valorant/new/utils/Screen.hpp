#pragma once

#include <Windows.h>
#include <thread>
#include <chrono>
#include "vec2.h"

class Screen
{
	public:
		static vec2<int> getSize()
		{
			int x, y;

			do {
				RECT desktop;

				const HWND hDesktop = GetDesktopWindow();
				GetWindowRect(hDesktop, &desktop);

				x = desktop.right;
				y = desktop.bottom;

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			} while (x == 0 || y == 0);

			return { x, y };
		}
};