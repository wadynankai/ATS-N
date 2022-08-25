// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include <windows.h>
#include <stdio.h>
#include "atsplugin.h"

wchar_t g_module_dir[MAX_PATH] = { 0 };
ATS_HANDLES g_output = { 0,0,0,0 };
FILE* g_Csv = NULL;
errno_t g_err = INT_MAX;
float g_buffer[10] = { 0 };
size_t g_index = 0;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        wchar_t fullpath[MAX_PATH];
        wchar_t drive[MAX_PATH],
            dir[MAX_PATH];

        GetModuleFileNameW(hModule, fullpath, MAX_PATH);
        _wsplitpath_s(fullpath, drive, MAX_PATH, dir, MAX_PATH, 0, 0, 0, 0);
        wcscpy_s(g_module_dir,MAX_PATH, drive);
        wcscat_s(g_module_dir, MAX_PATH, dir);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// Called when this plug-in is loaded
ATS_API void WINAPI Load(void) {
    wchar_t filename[MAX_PATH];
    wcscpy_s(filename, MAX_PATH, g_module_dir);
    wcscat_s(filename, MAX_PATH, L"DistanceLogger.csv");
    _wfopen_s(&g_Csv,filename,L"w");
}

// Called when this plug-in is unloaded
ATS_API void WINAPI Dispose(void) {
    if (!g_err)fclose(g_Csv);
}

// Returns the version numbers of ATS plug-in
ATS_API int WINAPI GetPluginVersion(void) {
	return ATS_VERSION;
}

// Called when the train is loaded
ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC spec) {
}

// Called when the game is started
ATS_API void WINAPI Initialize(int brake) {
    g_index = 0;
}

// Called every frame
ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vs, int* panel, int* sound) {
	g_output.ConstantSpeed = ATS_CONSTANTSPEED_CONTINUE;
	return g_output;
}

// Called when the power is changed
ATS_API void WINAPI SetPower(int power) {
	g_output.Power = power;
}

// Called when the brake is changed
ATS_API void WINAPI SetBrake(int brake) {
	g_output.Brake = brake;
}

// Called when the reverser is changed
ATS_API void WINAPI SetReverser(int pos) {
	g_output.Reverser = pos;
}

// Called when any ATS key is pressed
ATS_API void WINAPI KeyDown(int key) {
}

// Called when any ATS key is released
ATS_API void WINAPI KeyUp(int key) {
}

// Called when the horn is used
ATS_API void WINAPI HornBlow(int type) {
}

// Called when the door is opened
ATS_API void WINAPI DoorOpen(void) {
}

// Called when the door is closed
ATS_API void WINAPI DoorClose(void) {
}

// Called when current signal is changed
ATS_API void WINAPI SetSignal(int signal) {
}

// Called when the beacon data is received
ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA data) {
    switch (data.Type)
    {
    case 7:
        if (g_index < 10)
        {
            g_buffer[g_index] = data.Distance;
            if (g_index < 9)++g_index;
        }
        if (data.Optional == -1)
        {
            for (size_t i = 0; i < g_index; ++i)
            {
                if (g_index - i - 1 >= 0 && g_index - i - 1 < g_index)
                    fprintf_s(g_Csv, "%6f\n", g_buffer[g_index - i - 1] - g_buffer[g_index]);
            }
            g_index = 0;
            fprintf_s(g_Csv, "\n");
        }
        break;
    }
}