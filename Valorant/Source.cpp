#include <Windows.h>

#include "source/Manager.hpp"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    Manager::Start();
}

int main()
{
    Manager::Start();
}