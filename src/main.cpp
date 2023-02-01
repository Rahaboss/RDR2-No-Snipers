#include "pch.h"

static FILE* s_File{};
DWORD WINAPI MainThread(LPVOID lpThreadParameter)
{
	AllocConsole();
	freopen_s(&s_File, "CONOUT$", "w", stdout);
	assert(s_File);

	printf("RDR2.exe: 0x%llX\n", g_BaseAddress);
	
	while (g_Running)
	{
		// To quit press left control and end
		if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) && (GetAsyncKeyState(VK_END) & 0x8000))
			g_Running = false;

		std::this_thread::sleep_for(25ms);
	}
	
	fclose(s_File);
	FreeConsole();

	CloseHandle(g_MainThread);
	FreeLibraryAndExitThread(g_Module, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		g_Module = hModule;
		g_GameModule = GetModuleHandle(NULL);
		g_BaseAddress = reinterpret_cast<uintptr_t>(g_GameModule);
		g_MainThread = CreateThread(NULL, 0, MainThread, NULL, 0, NULL);

		if (!g_MainThread)
			return FALSE;
	}

	return TRUE;
}
