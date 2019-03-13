#include "SystemControl.h"

// �L�[�̓��͏�Ԃ��X�V����
int UpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

// �w�肳�ꂽ�L�[���A�����ĉ�������Ă��邩���肷��
bool IsRepeatedKey(int keyCode) { return (key[keyCode] > 0); }

// �w�肳�ꂽ�L�[�̘A�����͉񐔂�Ԃ�
int GetKeyRepeatNum(int keyCode) { return key[keyCode]; }

// �w�肳�ꂽ�L�[���������ꂽ�u�Ԃł��邩���肷��
bool isPushedKey(int keyCode) {
	if (key[keyCode] == 1) {
		key[keyCode] = 2;
		return true;
	}
	else {
		return false;
	}
}
