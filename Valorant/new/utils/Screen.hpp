#pragma once

#include <Windows.h>
#include <thread>
#include <chrono>

#include "./Math.hpp"

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

				std::this_thread::sleep_for(std::chrono::milliseconds(15));
			} while (x == 0 || y == 0);

			return vec2{ x,y };
		}
};