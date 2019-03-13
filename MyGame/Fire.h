#pragma once
#include "Base.h"
class Fire : public Base{
protected:
	static int fireImage[6];
	static int bombImage[4][6];
	static int fireSound;
	static int putBombSound;

	int x;
	int y;

	int time;				// Fire�C���X�^���X�̏ꍇ�A�c��R�Ď��ԁBBomb�C���X�^���X�̏ꍇ�A�����܂ł̎c�莞�Ԃ�\��
	int attack;
	bool attackByPlayer;	// true�ł���΃v���C���[�ɂ��U���������Afalse�ł���ΓG�iwitch�j�ɂ��U��

public:
	
	// ��������є��e�̉摜�A�T�E���h����荞��
	static void initFire();

	// �C���X�^���X��xy���W��pair�ɂ��ĕԂ�
	std::pair<int, int> getPoint();

	// Fire�z���Fire��`�悷��
	static void drawFires(std::vector<Fire> &fires);

	// Fire�z���Fire�̏�Ԃ��X�V����
	static void firesUpdate(std::vector<Fire> &fires);

	// �z���Fire�C���X�^���X��ǉ�����
	static void setFire(int _x, int _y, int _range, int _attack, int bombType, std::vector<Fire> & fires);

	// ���@�g���̍U���p
	static void setFireWitch(int _x, int _y, int _range, int _muki, int _attack, std::vector<Fire> & fires);

	// ���e�̃C���[�W�n���h����Ԃ�
	static int getBombImage(int type, int num);
};

