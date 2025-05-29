#include <windows.h>
#include <dinput.h>
#include <fstream>

std::ofstream logFile;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        logFile.open("ffb_log.txt", std::ios::app);
        logFile << "[INIT] FFB Injector Loaded\n";
    }
    return TRUE;
}

HRESULT WINAPI Hooked_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riid, LPVOID* ppvOut, LPUNKNOWN punkOuter) {
    logFile << "[HOOK] DirectInput8Create called\n";
    typedef HRESULT(WINAPI* DICREATE)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
    static DICREATE real = (DICREATE)GetProcAddress(LoadLibraryA("C:\\Windows\\System32\\version.dll"), "DirectInput8Create");
    return real(hinst, dwVersion, riid, ppvOut, punkOuter);
}

extern "C" {
    __declspec(dllexport) HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riid, LPVOID* ppvOut, LPUNKNOWN punkOuter) {
        return Hooked_DirectInput8Create(hinst, dwVersion, riid, ppvOut, punkOuter);
    }
}
