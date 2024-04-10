#pragma once
#include <string>
#include <imgui.h>
#include <chrono>
#include "Keys.hpp"
#include <WinUser.h>

#ifndef KEYBIND_HPP
#define KEYBIND_HPP

class HotKey
{
private:
    inline static int count = 0;
    int id;
public:
    HotKey()
    {
        count++;
        id = count;
        waiting = false;
    }

    bool waiting;
    void Bind(int* key, const ImVec2& size_arg = ImVec2(0, 0))
    {
        std::string waiting_label = "WAITING";
        std::string label = "##hk";
        label += id;
        waiting_label += label;

        //If not detecting for a keypress, display current key. 
        if (waiting == false)
        {
            std::string s = Keys::KeyNames[*key];
            s += label.c_str();

            if (ImGui::Button(s.c_str(), size_arg))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                waiting = true;
            }
        }
        else if (waiting == true)
        {
            ImGui::Button(waiting_label.c_str(), size_arg);

            for (int k = 0; k < Keys::KeyNames.size(); k++)
            {      
                if ((GetAsyncKeyState(k) & KEYDOWN) && k != VK_LBUTTON) //Never gonna bind to mouse click button;
                {
                    *key = k;
                    if (k == VK_ESCAPE)
                        *key = 0;

                    waiting = false;
                    break;
                }
            }
        }
    }
};
#endif