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
    ini["trigger"]["tension_min"] = std::to_string(Settings::triggerTension[0]);
    ini["trigger"]["tension_max"] = std::to_string(Settings::triggerTension[1]);
    ini["trigger"]["bind"] = std::to_string(Settings::triggerBind);
    ini["trigger"]["fireKey"] = std::to_string(Settings::triggerFireKey);
    ini["trigger"]["color"] = Color::toString(Settings::triggerColor);

    ini["rcs"]["rate"] = std::to_string(Settings::rcsRate);
    ini["rcs"]["amount"] = std::to_string(Settings::rcsAmount);
    ini["rcs"]["enabled"] = Settings::rcsEnabled ? "true" : "false";
    ini["rcs"]["bind"] = std::to_string(Settings::rcsBind);
    ini["rcs"]["comport"] = std::to_string(Settings::COMPORT);

    file.generate(ini);
 
}

void Settings::Load()
{
    mINI::INIFile file("config.ini");
    mINI::INIStructure ini;

    if (!file.read(ini))
    {
        Save();
    }

    Settings::triggerWidth = parsef(ini["trigger"]["width"]);
    Settings::triggerHeight = parsef(ini["trigger"]["height"]);
    Settings::triggerDelay = parsef(ini["trigger"]["delay"]);
    Settings::triggerTension[0] = parsei(ini["trigger"]["tension_min"]);
    Settings::triggerTension[1] = parsei(ini["trigger"]["tension_max"]);
    Settings::triggerBind = parsei(ini["trigger"]["bind"]);
    Settings::triggerFireKey = parsei(ini["trigger"]["fireKey"]);
    Settings::triggerColor = parsec(ini["trigger"]["color"]);

    Settings::rcsEnabled = ini["rcs"]["enabled"] == "true";
    Settings::rcsRate = parsef(ini["rcs"]["rate"]);
    Settings::rcsAmount = parsei(ini["rcs"]["amount"]);
    Settings::rcsBind = parsei(ini["rcs"]["bind"]);
    Settings::COMPORT = parsei(ini["rcs"]["comport"]);

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
Color::ColorName Settings::parsec(std::string data)
{
    Color::ColorName c;

    c = data == "Purple" ? Color::Magenta : data == "Red" ? Color::Verde : Color::Amarelo;
    return c;
}