#include "./utils/Basic.hpp"
#include "features/Rebase.hpp"

#include "./utils/ConfigParser.hpp"
#include "./utils/colors/color.hpp"

#include "./utils/HWID.hpp"
void config()
{
    mINI::INIFile file("config.ini");
    mINI::INIStructure ini;
    
    if (!file.read(ini))
    {
        ini["trigger"]["width"] = "2";
        ini["trigger"]["height"] = "15";
        ini["trigger"]["delay"] = "3";

        file.generate(ini);
    }

    int w = std::stoi(ini["trigger"]["width"]);
    int h = std::stoi(ini["trigger"]["height"]);

    settings.size = { w, h };
    settings.delay = std::chrono::milliseconds(std::stoi(ini["trigger"]["delay"]));

    if (ini["trigger"]["hide"] == "true") ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void CHECK();

int loop()
{
    while (1)
    {
        CHECK();

        if (GetAsyncKeyState(VK_DELETE)) exit(0);
    }
}

int main()
{
    HWID hwid;
    std::string s = hwid.checkHwid();

    config();

    std::cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~" << std::endl;
    std::cout << " " << dye::light_red(s) << " @1.0.0" << std::endl;
    std::cout << " " << std::endl;
    std::cout << " Width: " << dye::light_aqua(settings.size.x) << std::endl;
    std::cout << " Height: " << dye::light_aqua(settings.size.y) << std::endl;
    std::cout << " Delay: " << dye::light_aqua(settings.delay) << std::endl;
    std::cout << " " << std::endl;

    std::cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~" << std::endl;


    thread rb(Rebase::loop);
    thread l(loop);

    l.join();
    rb.join();

    return 0;
}