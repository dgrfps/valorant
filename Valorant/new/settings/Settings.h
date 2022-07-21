#pragma once
#include "ConfigParser.hpp"
#include "../utils/colors/HSV.hpp"

class Settings
{
	public:
		inline static float triggerWidth;
		inline static float triggerHeight;
		inline static float triggerDelay;
		inline static int triggerTension[2];
		inline static int triggerBind;
		inline static int triggerFireKey;
		inline static Color::ColorName triggerColor;

		inline static int rcsAmount;
		inline static bool rcsEnabled;
		inline static float rcsRate;
		inline static int rcsBind;
		inline static int COMPORT;

		static void Save();
		static void Load();

		inline static bool running;

		static double parsed(std::string data);
		static float parsef(std::string data);
		static int  parsei(std::string data);
		static Color::ColorName parsec(std::string data);
};

