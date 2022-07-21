#include <Windows.h>

void StartThreads();

int main()
{
#ifdef _DEBUG
    ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // DEBUG

    StartThreads();
}