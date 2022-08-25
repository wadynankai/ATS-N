#ifndef _ATSN_INCLUDED_
#define _ATSN_INCLUDED_

#ifndef _WIN32_WINNT
#include <winsdkver.h>
#define _WIN32_WINNT _WIN32_WINNT_WIN10
//#define _WIN32_WINNT _WIN32_WINNT_WINBLUE
//#define _WIN32_WINNT _WIN32_WINNT_WIN8
//#define _WIN32_WINNT _WIN32_WINNT_WIN7
#endif //_WIN32_WINNT
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include "atsplugin.h"
//beaconのtype(ATS_BEACONDATA.Type)
#define ATSN_BEACON 7//ATS-N(2点間タイマー方式)
//beaconのdata(ATS_BEACONDATA.Optional)
#define BEACON_FREE -1//常に有効
#define BEACON_R 0//停止のとき有効
#define BEACON_YY 1//警戒のとき有効
#define BEACON_Y 2//注意のとき有効
#define BEACON_YG 3//減速のとき有効
#define BEACON_R1 5//停止のとき即停止
#define BEACON_STOP 6//常に即停止

//信号インデックス(ATS_BEACONDATA.Signal)
#define SIGNAL_R 0//停止
#define SIGNAL_YY 1//警戒
#define SIGNAL_Y 2//注意
#define SIGNAL_YG 3//減速
#define SIGNAL_G 4//進行

int g_power;//マスコンの位置
int g_brakehandle;//ブレーキハンドルの位置
int g_reverser;//レバーサーの位置
int g_emrbrake;//非常ブレーキ
int g_time;//現在時刻
double g_location;//現在の位置
bool g_timer_begin;//trueのとき地上子を踏むと非常（カウントアップ中）
bool g_emg_brk_on;//trueのとき非常ブレーキ
int g_timercount;//タイマー(500まで)
bool g_pilotlamp;//戸閉灯
int g_framecount;//地上子を踏んでからのフレームを数える(駅ジャンプ対策)
bool g_reset;//リセットボタンを押した瞬間
bool g_reset_push;//リセットボタンを押している間true（連打を防ぐため）
bool g_reset_release;//リセットボタンを離した瞬間

double g_location1 = 0.0;//一個目の地上子の位置
double g_location2 = 0.0;//二個目の地上子の位置
int g_time1 = 0;//一個目の地上子を通過した時刻
int g_time2 = 0;//二個目の地上子を通過した時刻
int g_speedlist[] = { 5,10,15,20,25,30,35,40,50,55,60,65,70,75,80 };

void PassFirstBeacon(double location, int time);
bool PassSecondBeacon(double location, int time);
int g_speed = 0;

#endif //!_ATSN_INCLUDED_