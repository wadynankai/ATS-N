#pragma once
#include <array>
class CAtsn
{
private:
	double m_location1 = 0.0;//��ڂ̒n��q�̈ʒu
	double m_location2 = 0.0;//��ڂ̒n��q�̈ʒu
	int m_time1 = 0;//��ڂ̒n��q��ʉ߂�������
	int m_time2 = 0;//��ڂ̒n��q��ʉ߂�������
	std::array<int, 8> m_speedlist = { 5,10,15,20,25,30,55,80 };
public:
	CAtsn();
	~CAtsn();
	void PassFirstBeacon(double location, int time);
	bool PassSecondBeacon(double location, int time);
	int speed = 0;
};

