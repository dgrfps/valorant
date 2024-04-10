#pragma once

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

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

		static double parsed(const std::string& data);
		static float parsef(const std::string& data);
		static int  parsei(const std::string& data);
		static Color::ColorName parsec(const std::string& data);
};
#endif