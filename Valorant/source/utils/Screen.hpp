#pragma once

#ifndef SCREEN_HPP
#define SCREEN_HPP

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

			RECT desktop;

			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);

			x = desktop.right;
			y = desktop.bottom;

			return { x, y };
		}
};
#endif