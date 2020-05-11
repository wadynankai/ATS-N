#include "stdafx.h"
#include "CAtsn.h"

CAtsn::CAtsn()
{
}

CAtsn::~CAtsn()
{
}

void CAtsn::PassFirstBeacon(double location, int time)
{
	m_location1 = location;//位置の代入
	m_time1 = time;//時刻の代入
}

bool CAtsn::PassSecondBeacon(double location, int time)
{
	double aveSpeed;//平均速度[km/h]
	double distance;//2つのビーコンの距離
	double min_difference = DBL_MAX;//差の最小値（はじめは大きくしておく）
	int n = _countof(m_speedlist);//最も差が小さい制限速度のインデックス
	m_location2 = location;//位置の代入
	m_time2 = time;//時刻の代入
	distance = fabs(m_location2 - m_location1);
	aveSpeed = (m_location2 - m_location1) / ((double)(m_time2 - m_time1)) * 3600.0;
	for (int i = 0; i < _countof(m_speedlist); i++)//差が最も小さいi=nを探す。
	{
		double distanceOfSpeed = (double)(m_speedlist[i] / 7.2);//speedlist[i]のときの地上子の正しい距離
		double difference = fabs(distance - distanceOfSpeed);//差
		if (difference < min_difference)//最小値よりも小さい場合
		{
			min_difference = difference;//最小値を更新
			n = i;
		}
	}
	speed = m_speedlist[n];

	return (aveSpeed > m_speedlist[n]);//速度超過のときにtrue
}
