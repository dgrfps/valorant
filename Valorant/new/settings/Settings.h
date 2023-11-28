#pragma once
#include "ConfigParser.hpp"
#include "../utils/colors/HSV.hpp"

class Settings
{
	public:
		static int triggerWidth;
		static int triggerHeight;
		static int triggerDelay;
		static int triggerTension[2];
		static int triggerBind;
		static int triggerFireKey;
		static Color::ColorName triggerColor;

		static void Save();
		static void Load();

		inline static bool running = false;
		inline static bool loaded = false;

		static double parsed(std::string data);
		static float parsef(std::string data);
		static int  parsei(std::string data);
		static Color::ColorName parsec(std::string data);
};