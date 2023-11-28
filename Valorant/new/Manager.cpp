#include <thread>

#include "./render/Graphics.hpp"
#include "features/Trigger.hpp"


void StartThreads()
{
	Settings::Load();
	Settings::running = true;

	do { this_thread::sleep_for(5ms);}  //USELESS?
		while (Settings::loaded == false);

	std::thread trigger(Trigger::loop);
	trigger.detach();

	Render::Create(); //Moving to the main thread.
}