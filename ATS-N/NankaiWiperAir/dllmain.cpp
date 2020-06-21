// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "atsplugin.h"
#include "CWiper.h"

/////グローバル変数
ATS_HANDLES g_output;//Elapseの出力
int g_time_pre;//前回の時刻
CWiper g_wiper;//ワイパークラス

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

// Called when this plug-in is loaded
ATS_API void WINAPI Load(void) {
}

// Called when this plug-in is unloaded
ATS_API void WINAPI Dispose(void) {
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
}

// Called every frame
ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vs, int* panel, int* sound) {
	g_output.ConstantSpeed = ATS_CONSTANTSPEED_CONTINUE;
	//画面
	panel[97] = g_wiper.output(vs.Time - g_time_pre);
	//音
	if (g_wiper.sound())sound[111] = ATS_SOUND_PLAY;
	else sound[111] = ATS_SOUND_CONTINUE;
	g_time_pre = vs.Time;//前回の時刻を更新
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
	switch (key)
	{
	case ATS_KEY_J:
		g_wiper.decrease();
		break;
	case ATS_KEY_K:
		g_wiper.increase();
		break;
	}
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
}