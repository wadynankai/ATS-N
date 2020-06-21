#pragma once

//#define WIPER_FILE
#ifdef WIPER_FILE
#include<string>
#include<fstream>
#endif // WIPER_FILE

class CWiper
{

private:
	float m_speed;
	float m_xMax;//x�̍ő�l
	float m_x;//speedstep�ŕω�������
	float m_y;//�o��
	float m_x1;
	float m_x2;
	float m_y1;
	float m_y2;
	float m_speedStep;//�X�s�[�h�̑�����
	float m_speedMax;//�X�s�[�h�̍ő�l
	bool m_direction, m_direction_pre;//true:����,false:����
public:
	CWiper();
#ifdef WIPER_FILE
	CWiper(wchar_t*);
#endif // WIPER_FILE
	~CWiper();
#ifdef WIPER_FILE
	//�e�L�X�g����ݒ��ǂݍ���
	void loadParam(wchar_t*);
#endif // WIPER_FILE
	// ���C�p�[�𑬂�����
	void increase();
	// ���C�p�[��x������B
	void decrease();
	//�o��
	int output(int);
	bool sound();
};

