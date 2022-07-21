#pragma once
#include "../utils/Mouse.hpp"
#include "../settings/Settings.h"
#include "../utils/Keys.hpp"

class RCS {
public:
	static void loop() {
		static bool toggled = false;

		while (Settings::running) 
		{
			if (GetAsyncKeyState(Settings::rcsBind) & KEYPRESS)
			{
				toggled = !toggled;
			}

			if (toggled && (GetAsyncKeyState(VK_LBUTTON) & KEYDOWN) && Settings::rcsEnabled)
			{
				Mouse::Move(0, Settings::rcsAmount);
				this_thread::sleep_for(chrono::milliseconds((long)Settings::rcsRate));
			}
			else
			{
				this_thread::sleep_for(10ms);
			}
		}
	};
};