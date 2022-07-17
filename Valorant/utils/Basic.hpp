#pragma once

#include <stdio.h>
#include <Windows.h>
#include <thread>
#include <chrono>

#include "./colors/HSV.hpp"
#include "./screen/Screen.hpp"
#include "./Keys.hpp"

struct vec2 { int x; int y; };

struct Settings { //SETTINGS STRUCT
	vec2 size;
	chrono::milliseconds delay;
};

Settings settings; //CREATE SETTINGS USING THE SETTINGS STRUCT