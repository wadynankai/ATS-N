#pragma once
#include "CAtsn.h"
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
CAtsn atsn;
