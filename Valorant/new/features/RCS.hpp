#pragma once
#include "../utils/Mouse.hpp"
#include "../settings/Settings.h"
#include "../utils/Keys.hpp"

class RCS {
public:
	static void loop() {
		while (Settings::running) 
		{
			if (GetAsyncKeyState(VK_LBUTTON) && KEYDOWN && Settings::rcsEnabled) 
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