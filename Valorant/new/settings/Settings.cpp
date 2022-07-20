#include "Settings.h"
#include "ConfigParser.hpp"

#include <chrono>

void Settings::Save()
{
    mINI::INIFile file("config.ini");
    mINI::INIStructure ini;

    ini["trigger"]["width"] = std::to_string(Settings::triggerWidth);
    ini["trigger"]["height"] = std::to_string(Settings::triggerHeight);
    ini["trigger"]["delay"] = std::to_string(Settings::triggerDelay);

    ini["rcs"]["rate"] = std::to_string(Settings::rcsRate);
    ini["rcs"]["amount"] = std::to_string(Settings::rcsAmount);
    ini["rcs"]["enabled"] = Settings::rcsEnabled ? "true" : "false";

    file.generate(ini);
    
}

void Settings::Load()
{
    mINI::INIFile file("config.ini");
    mINI::INIStructure ini;

    if (!file.read(ini))
    {
        ini["trigger"]["width"] = "5";
        ini["trigger"]["height"] = "15";
        ini["trigger"]["delay"] = "0";

        ini["rcs"]["rate"] = "1";
        ini["rcs"]["amount"] = "5";
        ini["rcs"]["enabled"] = "true";

        file.generate(ini);
    }

    Settings::triggerWidth = parsef(ini["trigger"]["width"]);
    Settings::triggerHeight = parsef(ini["trigger"]["height"]);
    Settings::triggerDelay = parsef(ini["trigger"]["delay"]);

    Settings::rcsEnabled = ini["rcs"]["enabled"] == "true";
    Settings::rcsRate = parsef(ini["rcs"]["rate"]);
    Settings::rcsAmount = parsei(ini["rcs"]["amount"]);

}

double Settings::parsed(std::string data)
{
    double d;
    
    try
    {
        d = std::stod(data);
    }
    catch(const std::invalid_argument&)
    {
        d = 0;
    }

    return d;
}
float Settings::parsef(std::string data)
{
    float d;

    try
    {
        d = std::stof(data);
    }
    catch (const std::invalid_argument&)
    {
        d = 0;
    }

    return d;
}
int  Settings::parsei(std::string data)
{
    int d;

    try
    {
        d = std::stoi(data);
    }
    catch (const std::invalid_argument&)
    {
        d = 0;
    }

    return d;
}