#pragma once
#ifndef KEYS_HPP
#define KEYS_HPP

#define KEYUP 0x2
#define KEYPRESS 0x1
#define KEYDOWN 0x8000

#include <string>
#include <vector>

class Keys
{ 
    public:
        static const std::vector<std::string> KeyNames;
        static int toInt(const std::string& key);        
};

#endif