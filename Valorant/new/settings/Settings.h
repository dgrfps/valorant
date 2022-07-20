#pragma once
#include "ConfigParser.hpp"

class Settings
{
	public:
		inline static float triggerWidth;
		inline static float triggerHeight;
		inline static float triggerDelay;

		inline static int rcsAmount;
		inline static bool rcsEnabled;
		inline static float rcsRate;

		static void Save();
		static void Load();

		inline static bool running;

		static double parsed(std::string data);
		static float parsef(std::string data);
		static int  parsei(std::string data);
};

