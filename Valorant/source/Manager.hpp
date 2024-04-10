#pragma once

#ifndef Manager_HPP
#define  Manager_HPP

#include <thread>

#include "./render/Graphics.hpp"
#include "features/Trigger.hpp"

class Manager {
public:
	static void Start()
	{
		Settings::Load();
		Settings::running = true;

		std::thread trigger(Trigger::loop);
		trigger.detach();

		Render::Create(); //Freezes this (main) thread.
	}
};

#endif // !Manager_HPP
