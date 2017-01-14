#include "../D2MultiResPatcher/detourshelper.h"

int main()
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	DetourCreateProcessWithDllA(nullptr
		, "Game.exe -window", nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi
		, "D2MultiResPatcher.dll", &CreateProcessA);
	return 0;
}
