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
	float m_xMax;//xの最大値
	float m_x;//speedstepで変化させる
	float m_y;//出力
	float m_x1;
	float m_x2;
	float m_y1;
	float m_y2;
	float m_speedStep;//スピードの増加率
	float m_speedMax;//スピードの最大値
	bool m_direction, m_direction_pre;//true:増加,false:減少
public:
	CWiper();
#ifdef WIPER_FILE
	CWiper(wchar_t*);
#endif // WIPER_FILE
	~CWiper();
#ifdef WIPER_FILE
	//テキストから設定を読み込む
	void loadParam(wchar_t*);
#endif // WIPER_FILE
	// ワイパーを速くする
	void increase();
	// ワイパーを遅くする。
	void decrease();
	//出力
	int output(int);
	bool sound();
};

