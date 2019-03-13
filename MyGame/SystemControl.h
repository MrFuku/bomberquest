#pragma once
#include "DxLib.h"
#include "Fps.h"
#include <vector>

static const int FIELD_X = 23;
static const int FIELD_Y = 19;
static const int  MARGIN_TOP = 32 * 2;

static int dy[4] = { -1, 0, 1, 0 };
static int dx[4] = { 0, -1, 0, 1 };

static int key[256];			// �L�[�̓��͏�Ԃ��i�[����

static int gameModeNum = 0;		// ���݂̃Q�[�����[�h������
const int GAMEMODE_MENU = 0;
const int GAMEMODE_VILLAGE = 1;
const int GAMEMODE_BATTLE = 2;
static int changedModeFlag = 1;	// �Q�[�����[�h���ύX���ꂽ�Ƃ��Ƀt���O�𗧂Ă�

// �L�[�̓��͏�Ԃ��X�V����
int UpdateKey();

// �w�肳�ꂽ�L�[���A�����ĉ�������Ă��邩���肷��
bool IsRepeatedKey(int keyCode);

// �w�肳�ꂽ�L�[�̘A�����͉񐔂�Ԃ�
int GetKeyRepeatNum(int keyCode);

// �w�肳�ꂽ�L�[���������ꂽ�u�Ԃł��邩���肷��
bool isPushedKey(int keyCode);
