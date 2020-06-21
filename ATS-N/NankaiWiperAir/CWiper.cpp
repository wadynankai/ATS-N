#include "pch.h"
#include "CWiper.h"


CWiper::CWiper()
{
	m_speed = 0.0f;
	m_xMax = 10000.0f;
	m_x = m_xMax;
	m_y = m_xMax;
	m_x1 = 0.1f;
	m_y1 = 0.025f;
	m_x2 = 0.7f;
	m_y2 = 0.975f;
	m_speedStep = 1000.0f;
	m_speedMax = 50000.0f;
	m_direction = false;
	m_direction_pre = false;
}

#ifdef WIPER_FILE
CWiper::CWiper(wchar_t* g_module_dir)
{
	loadParam(g_module_dir);
}
#endif // WIPER_FILE



CWiper::~CWiper()
{
}

#ifdef WIPER_FILE
void CWiper::loadParam(wchar_t* g_module_dir)
{
	std::wstring filename;
	filename = g_module_dir;
	filename += L"wiper.txt";
	std::ifstream input(filename);
	if (!input.fail())
	{
		std::string data[7];
		int i = 0;
		std::getline(input, data[i]);
		m_xMax = std::stof(data[i]);
		i++;
		std::getline(input, data[i]);
		m_x1 = std::stof(data[i]);
		i++;
		std::getline(input, data[i]);
		m_y1 = std::stof(data[i]);
		i++;
		std::getline(input, data[i]);
		m_x2 = std::stof(data[i]);
		i++;
		std::getline(input, data[i]);
		m_y2 = std::stof(data[i]);
		i++;
		std::getline(input, data[i]);
		m_speedStep = std::stof(data[i]);
		i++;
		std::getline(input, data[i]);
		m_speedMax = std::stof(data[i]);
	}
	input.close();
	/*	std::ofstream out(filename + L"2.csv");
		m_x = -m_xMax;
		while (m_x < m_xMax + 1)
		{
			if (m_x > m_x2 * m_xMax)m_y = (1.0f - m_y2) / (1.0f - m_x2) * (m_x - m_x2 * m_xMax) + m_y2 * m_xMax;
			else if (m_x > m_x1 * m_xMax)m_y = (m_y2 - m_y1) / (m_x2 - m_x1) * (m_x - m_x1 * m_xMax) + m_y1 * m_xMax;
			else if (m_x > -m_x1 * m_xMax)m_y = m_y1 / m_x1 * m_x;
			else if (m_x > -m_x2 * m_xMax) m_y = (m_y2 - m_y1) / (m_x2 - m_x1) * (m_x + m_x1 * m_xMax) - m_y1 * m_xMax;
			else m_y = (1.0f - m_y2) / (1.0f - m_x2) * (m_x + m_x2 * m_xMax) - m_y2 * m_xMax;
			out << m_x << ',' << m_y << std::endl;
			m_x += 1.0f;
		}
		out.close();*/
	m_x = m_xMax;
}
#endif // WIPER_FILE


// ワイパーを速くする
void CWiper::increase()
{
	// TODO: ここに実装コードを追加します.
	m_speed += m_speedStep;
	if (m_speed > m_speedMax)m_speed = m_speedMax;
}


// ワイパーを遅くする。
void CWiper::decrease()
{
	// TODO: ここに実装コードを追加します.
	m_speed -= m_speedStep;
	if (m_speed < 0)m_speed = 0;
}

int CWiper::output(int delta_T)
{
	if (m_direction)m_x += m_speed / 1000.0f * delta_T;
	else m_x -= m_speed / 1000.0f * delta_T;
	if (m_x > m_xMax)
	{
		m_x = m_xMax;
		m_direction = false;
	}
	else if (m_x < -m_xMax)
	{
		m_x = -m_xMax;
		m_direction = true;
	}
	//xをyに変換
	if (m_x > m_x2 * m_xMax)m_y = (1.0f - m_y2) / (1.0f - m_x2) * (m_x - m_x2 * m_xMax) + m_y2 * m_xMax;
	else if (m_x > m_x1 * m_xMax)m_y = (m_y2 - m_y1) / (m_x2 - m_x1) * (m_x - m_x1 * m_xMax) + m_y1 * m_xMax;
	else if (m_x > -m_x1 * m_xMax)m_y = m_y1 / m_x1 * m_x;
	else if (m_x > -m_x2 * m_xMax) m_y = (m_y2 - m_y1) / (m_x2 - m_x1) * (m_x + m_x1 * m_xMax) - m_y1 * m_xMax;
	else m_y = (1.0f - m_y2) / (1.0f - m_x2) * (m_x + m_x2 * m_xMax) - m_y2 * m_xMax;
	return (int)m_y;
}

bool CWiper::sound()
{
	bool ret;
	ret = (m_direction != m_direction_pre);
	m_direction_pre = m_direction;
	return ret && m_speed >= m_xMax * 1.5f;
}
