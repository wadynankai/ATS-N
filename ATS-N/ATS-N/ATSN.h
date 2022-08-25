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
#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����قƂ�ǎg�p����Ă��Ȃ����������O����
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
//beacon��type(ATS_BEACONDATA.Type)
#define ATSN_BEACON 7//ATS-N(2�_�ԃ^�C�}�[����)
//beacon��data(ATS_BEACONDATA.Optional)
#define BEACON_FREE -1//��ɗL��
#define BEACON_R 0//��~�̂Ƃ��L��
#define BEACON_YY 1//�x���̂Ƃ��L��
#define BEACON_Y 2//���ӂ̂Ƃ��L��
#define BEACON_YG 3//�����̂Ƃ��L��
#define BEACON_R1 5//��~�̂Ƃ�����~
#define BEACON_STOP 6//��ɑ���~

//�M���C���f�b�N�X(ATS_BEACONDATA.Signal)
#define SIGNAL_R 0//��~
#define SIGNAL_YY 1//�x��
#define SIGNAL_Y 2//����
#define SIGNAL_YG 3//����
#define SIGNAL_G 4//�i�s

int g_power;//�}�X�R���̈ʒu
int g_brakehandle;//�u���[�L�n���h���̈ʒu
int g_reverser;//���o�[�T�[�̈ʒu
int g_emrbrake;//���u���[�L
int g_time;//���ݎ���
double g_location;//���݂̈ʒu
bool g_timer_begin;//true�̂Ƃ��n��q�𓥂ނƔ��i�J�E���g�A�b�v���j
bool g_emg_brk_on;//true�̂Ƃ����u���[�L
int g_timercount;//�^�C�}�[(500�܂�)
bool g_pilotlamp;//�˕�
int g_framecount;//�n��q�𓥂�ł���̃t���[���𐔂���(�w�W�����v�΍�)
bool g_reset;//���Z�b�g�{�^�����������u��
bool g_reset_push;//���Z�b�g�{�^���������Ă����true�i�A�ł�h�����߁j
bool g_reset_release;//���Z�b�g�{�^���𗣂����u��

double g_location1 = 0.0;//��ڂ̒n��q�̈ʒu
double g_location2 = 0.0;//��ڂ̒n��q�̈ʒu
int g_time1 = 0;//��ڂ̒n��q��ʉ߂�������
int g_time2 = 0;//��ڂ̒n��q��ʉ߂�������
int g_speedlist[] = { 5,10,15,20,25,30,35,40,50,55,60,65,70,75,80 };

void PassFirstBeacon(double location, int time);
bool PassSecondBeacon(double location, int time);
int g_speed = 0;

#endif //!_ATSN_INCLUDED_