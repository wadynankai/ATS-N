// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "stdafx.h"
#include "atsplugin.h"
#include "ATSN.h"

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
	g_emrbrake = spec.BrakeNotches + 1;
}

// Called when the game is started
ATS_API void WINAPI Initialize(int brake) {
	g_time = 0;
	g_timercount = 1000;
	g_framecount = 0;
	g_timer_begin = false;
	g_emg_brk_on = false;
}

// Called every frame
ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vs, int* panel, int* sound) {
	ATS_HANDLES ret;
	int deltaT;//1フレームの時間
	deltaT = vs.Time - g_time;//フレーム時間の計算
	g_time = vs.Time;//時刻の更新
	g_location = vs.Location;//位置の更新
	if (g_timer_begin) {
		g_timercount += deltaT;
		g_framecount++;
	}
	if (g_timercount > 600 || g_timercount < 0)g_timer_begin = false;//0.6秒後にタイマーを切る(誤差を見込んで）

	//ハンドル設定
	ret.Power = g_power;
	ret.ConstantSpeed = ATS_CONSTANTSPEED_CONTINUE;
	if (!g_emg_brk_on)//正常
	{
		ret.Brake = g_brakehandle;
	}
	else//非常ブレーキ
	{
		ret.Brake = g_emrbrake;
	}
	if (g_pilotlamp)ret.Reverser = g_reverser;
	else ret.Reverser = 0;
	if (g_reset)//リセットボタンを押したとき
	{
		sound[24] = ATS_SOUND_PLAY;
		g_reset = false;
	}
	else if (g_reset_release)//リセットボタンを離したとき
	{
		sound[24] = ATS_SOUND_STOP;
		sound[25] = ATS_SOUND_PLAY;
		g_reset_release = false;
	}
	else
	{
		sound[24] = ATS_SOUND_CONTINUE;
		sound[25] = ATS_SOUND_CONTINUE;
	}
	panel[120] = !g_emg_brk_on;//正常
	panel[121] = g_emg_brk_on;//非常

	panel[38] = g_timer_begin;
	panel[39] = (atsn.speed % 100) / 10;
	panel[40] = atsn.speed % 10;
	return ret;
}

// Called when the power is changed
ATS_API void WINAPI SetPower(int power) {
	g_power = power;
}

// Called when the brake is changed
ATS_API void WINAPI SetBrake(int brake) {
	g_brakehandle = brake;
}

// Called when the reverser is changed
ATS_API void WINAPI SetReverser(int pos) {
	g_reverser = pos;
}

// Called when any ATS key is pressed
ATS_API void WINAPI KeyDown(int key) {
	switch (key)
	{
	case ATS_KEY_B2:
		if (!g_reset_push)
		{
			g_reset_push = true;
			g_emg_brk_on = false;
			g_timercount = false;
			g_reset = true;
		}
		break;
	}
}

// Called when any ATS key is released
ATS_API void WINAPI KeyUp(int key) {
	switch (key)
	{
	case ATS_KEY_B2:
		if (g_reset_push)
		{
			g_reset_push = false;
			g_reset_release = true;
		}
		break;
	}
}

// Called when the horn is used
ATS_API void WINAPI HornBlow(int type) {

}

// Called when the door is opened
ATS_API void WINAPI DoorOpen(void) {
	g_pilotlamp = false;
}

// Called when the door is closed
ATS_API void WINAPI DoorClose(void) {
	g_pilotlamp = true;
}

// Called when current signal is changed
ATS_API void WINAPI SetSignal(int signal) {

}

// Called when the beacon data is received
ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA data) {
	switch (data.Type)
	{
	case ATSN_BEACON:
		if (data.Optional == BEACON_FREE || (data.Optional == BEACON_R && data.Signal == SIGNAL_R) || (data.Optional == BEACON_YY && data.Signal == SIGNAL_YY) || (data.Optional == BEACON_Y && data.Signal == SIGNAL_Y) || (data.Optional == BEACON_YG && data.Signal == SIGNAL_YG))
		{
			if (!g_timer_begin)//一個目の地上子を通過
			{
				g_timercount = 0;
				g_framecount = 0;
				atsn.PassFirstBeacon(g_location, g_time);
				g_timer_begin = true;
			}
			else if (g_timercount < 600 && g_framecount && atsn.PassSecondBeacon(g_location, g_time))g_emg_brk_on = true;//二個目の地上子を通過
		}
		else if (data.Optional == BEACON_STOP || (data.Optional == BEACON_R1 && data.Signal == SIGNAL_R))
		{
			g_emg_brk_on = true;
		}
		break;
	}

}