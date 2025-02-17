#include "ATSN.h"

// Called when this plug-in is loaded
ATS_API void WINAPI Load(void) {
	g_atsPower = true;
	g_nfb_push = false;
	g_nfb_on = false;
	g_nfb_off = false;
	g_reset = false;
	g_reset_push = false;
	g_reset_release = false;
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
	ret.Reverser = g_reverser;
	if (g_reset)//リセットボタンを押したとき
	{
		sound[24] = ATS_SOUND_PLAY;
		sound[25] = ATS_SOUND_STOP;
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

	if (g_nfb_on)//ATS電源を入れた時
	{
		sound[37] = ATS_SOUND_PLAY;
		sound[38] = ATS_SOUND_STOP;
		g_nfb_on = false;
	}
	else if (g_nfb_off)
	{
		sound[37] = ATS_SOUND_STOP;
		sound[38] = ATS_SOUND_PLAY;
		g_nfb_off = false;
	}
	else
	{
		sound[37] = ATS_SOUND_CONTINUE;
		sound[38] = ATS_SOUND_CONTINUE;
	}
	
	if (g_atsPower)
	{
		panel[120] = !g_emg_brk_on;//正常
		panel[121] = g_emg_brk_on;//非常
	}
	else
	{
		panel[120] = 0;//消灯
		panel[121] = 0;//消灯
	}

//	panel[38] = g_timer_begin;
//	panel[39] = (atsn.speed % 100) / 10;
//	panel[40] = atsn.speed % 10;
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
		if (!g_reset_push && !g_nfb_push)
		{
			if ((GetKeyState(VK_SHIFT) & 0x80) && !(GetKeyState(VK_CONTROL) & 0x80))//Shiftを押しているとき
			{
				g_nfb_push = true;
				g_atsPower = !g_atsPower;
				if (g_atsPower)
				{
					g_emg_brk_on = true;//電源が「入」の時は非常に入る
					g_nfb_on = true;
				}
				else g_nfb_off = true;
			}
			else if (!(GetKeyState(VK_SHIFT) & 0x80) && !(GetKeyState(VK_CONTROL) & 0x80))//Shiftを押していないとき
			{
				g_reset_push = true;
				g_emg_brk_on = false;
				g_timercount = false;
				g_reset = true;
			}
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
		if (g_nfb_push)g_nfb_push = false;
		break;
	}
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
	if (g_atsPower)
	{
		switch (data.Type)
		{
		case ATSN_BEACON:
			if (data.Optional == BEACON_FREE || (data.Optional == BEACON_R && data.Signal == SIGNAL_R) || (data.Optional == BEACON_YY && data.Signal == SIGNAL_YY) || (data.Optional == BEACON_Y && data.Signal == SIGNAL_Y) || (data.Optional == BEACON_YG && data.Signal == SIGNAL_YG))
			{
				if (!g_timer_begin)//一個目の地上子を通過
				{
					g_timercount = 0;
					g_framecount = 0;
					PassFirstBeacon(g_location, g_time);
					g_timer_begin = true;
				}
				else if (g_timercount < 600 && g_framecount && PassSecondBeacon(g_location, g_time))g_emg_brk_on = true;//二個目の地上子を通過
			}
			else if (data.Optional == BEACON_STOP || (data.Optional == BEACON_R1 && data.Signal == SIGNAL_R))
			{
				g_emg_brk_on = true;
			}
			break;
		}
	}
}

void PassFirstBeacon(double location, int time)
{
	g_location1 = location;//位置の代入
	g_time1 = time;//時刻の代入
}

bool PassSecondBeacon(double location, int time)
{
	double aveSpeed;//平均速度[km/h]
	double distance;//2つのビーコンの距離
	double min_difference = DBL_MAX;//差の最小値（はじめは大きくしておく）
	size_t n = _countof(g_speedlist);//最も差が小さい制限速度のインデックス
	g_location2 = location;//位置の代入
	g_time2 = time;//時刻の代入
	distance = fabs(g_location2 - g_location1);
	aveSpeed = (g_location2 - g_location1) / ((double)(g_time2 - g_time1)) * 3600.0;
	for (size_t i = 0; i < _countof(g_speedlist); ++i)//差が最も小さいi=nを探す。
	{
		double distanceOfSpeed = (double)(g_speedlist[i]) / 7.2;//speedlist[i]のときの地上子の正しい距離
		double difference = fabs(distance - distanceOfSpeed);//差
		if (difference < min_difference)//最小値よりも小さい場合
		{
			min_difference = difference;//最小値を更新
			n = i;
		}
	}
	g_speed = g_speedlist[n];

	return (aveSpeed > g_speedlist[n] + 1);//速度超過のときにtrue
}