#pragma once
#include "atsplugin.h"
class CAtsn
{
private:
	double m_location1 = 0.0;//一個目の地上子の位置
	double m_location2 = 0.0;//二個目の地上子の位置
	int m_time1 = 0;//一個目の地上子を通過した時刻
	int m_time2 = 0;//二個目の地上子を通過した時刻
	int m_speedlist[8] = { 5,10,15,20,25,30,55,80 };
public:
	CAtsn();
	~CAtsn();
	void PassFirstBeacon(double location, int time);
	bool PassSecondBeacon(double location, int time);
	int speed = 0;
};

