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
        triggerWidth = 5;
        triggerHeight = 15;
        triggerDelay = 0;
        triggerTension[0] = 15;
        triggerTension[1] = 80;
        triggerBind = 0x0;
        triggerFireKey = 0x0;
        triggerColor = Color::ColorName::Magenta;

        rcsAmount = 5;
        rcsEnabled = false;
        rcsRate = 9;
        rcsBind = 0x0;
        COMPORT = 3;

        Save();
        Load();
        return;
    }

    Settings::triggerWidth = parsei(ini["trigger"]["width"]);
    Settings::triggerHeight = parsei(ini["trigger"]["height"]);
    Settings::triggerDelay = parsei(ini["trigger"]["delay"]);
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

    Settings::loaded = true;
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

    c = data == "PURPLE" ? Color::Magenta : data == "RED" ? Color::Vermelho : Color::Amarelo;
    return c;
}
int Settings::triggerWidth = 5;
int Settings::triggerHeight = 15;
int Settings::triggerDelay = 0;
int Settings::triggerTension[] = { 15,80 };
int Settings::triggerBind = 0x0;
int Settings::triggerFireKey = 0x0;
Color::ColorName Settings::triggerColor = Color::ColorName::Magenta;

int Settings::rcsAmount = 5;
bool Settings::rcsEnabled = false;
float Settings::rcsRate = 9;
int Settings::rcsBind = 0x0;
int Settings::COMPORT = 3;