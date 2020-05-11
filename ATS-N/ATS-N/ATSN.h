#pragma once
#include "CAtsn.h"
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
CAtsn atsn;
