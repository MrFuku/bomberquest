#pragma once
#include "Fire.h"

class Bomb :public Fire{
private:
	// �{���^�C�v�O�F�ʏ�e�B�\�������ɔ����B��ђ�
	// �{���^�C�v�P�F�ђʒe�B�\�������ɔ����B�ђ�
	// �{���^�C�v�Q�F�L�͈͒e�B�S�T�x�X���������`��ɔ����B�ђʁB�����̓}���n�b�^���������Z
	int bombType;
	int range;			// �����͈̔�
	bool randomFlag;	// �����_���t���O�B�����̃^�C�~���O�������_���Ō��܂�
	
public:

	// Bomb�z���Bomb�C���X�^���X��`�悷��
	// �����܂ł̎c�莞�Ԃɂ���ăC���[�W�n���h�����g��������
	static void drawBombs(std::vector<Bomb> &bombs);
	
	// Bomb�z���Bomb�C���X�^���X�̏�Ԃ��X�V����
	static void bombsUpdate(std::vector<Bomb> &bombs, std::vector<Fire> &fires);

	// Bomb�z��ɐV����Bomb�C���X�^���X���i�[����
	static void insertBomb(int _x, int _y, int type, int _range, int _attack, bool random, std::vector<Bomb> &bombs);
};

