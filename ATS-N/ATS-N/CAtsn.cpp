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
	m_location1 = location;//�ʒu�̑��
	m_time1 = time;//�����̑��
}

bool CAtsn::PassSecondBeacon(double location, int time)
{
	double aveSpeed;//���ϑ��x[km/h]
	double distance;//2�̃r�[�R���̋���
	double min_difference = DBL_MAX;//���̍ŏ��l�i�͂��߂͑傫�����Ă����j
	size_t n = m_speedlist.size();//�ł������������������x�̃C���f�b�N�X
	m_location2 = location;//�ʒu�̑��
	m_time2 = time;//�����̑��
	distance = fabs(m_location2 - m_location1);
	aveSpeed = (m_location2 - m_location1) / (static_cast<double>(m_time2 - m_time1)) * 3600.0;
	for (size_t i = 0; const auto& a:m_speedlist)//�����ł�������i=n��T���B
	{
		double distanceOfSpeed = (double)(a / 7.2);//speedlist[i]�̂Ƃ��̒n��q�̐���������
		double difference = fabs(distance - distanceOfSpeed);//��
		if (difference < min_difference)//�ŏ��l�����������ꍇ
		{
			min_difference = difference;//�ŏ��l���X�V
			n = i;
		}
		i++;
	}
	speed = m_speedlist.at(n);

	return (aveSpeed > m_speedlist.at(n));//���x���߂̂Ƃ���true
}
