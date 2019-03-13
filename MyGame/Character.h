#pragma once
#include "Base.h"
class Character :public Base{

protected:
	
	enum CharacterType { PLAYER, GHOST, SKELETON, WITCH };

	// �L�����N�^�[����ъe��G�t�F�N�g�p�n���h��
	static int playerImage[3][12];
	static int enemyImage[3][12];
	static int questionImage[6];
	static int magicSound;
	static int magicEfect[3];

	int characterType;
	double x;
	double y;
	double speed;
	int attack;
	int life;
	int damageTime = 0;
	bool alive = 1;
	bool removeFlag = 0;
	int muki = 0;
	int walkingFlag = 0;
	int image[12];
	
public:

	// �L�����N�^�[����ъe��C���[�W�E�T�E���h����荞��
	void inputImage();

	// �_���[�W����
	void damageUpdate();

	// �����[�u�t���O�������Ă��邩����
	bool isRemove();

	// �L�����N�^�[��`��
	void draw();

	// �����t���O�y�ѐ����t���O�������Ă����ꍇ�̕��s����
	void move();

	// �L�����N�^�[�������Ă�������ɐi�߂邩����
	bool isAbleToGo();

	// �L�����N�^�[�̌��݈ʒu�y�ёO���P�}�X���[�����i�O�ǂ̂��������j�ł��邩���肷��
	bool isEdge();

	// �L�����N�^�[�̂���}�X���y�A�ɂ��ĕԂ��B�ړ����ł���΂��߂����̃}�X�̒l�Ƃ���
	std::pair<int, int> getPos();

	// �L�����N�^�[�C���[�W�̃n���h����Ԃ�
	int getImageHandle(int isPlayer, int type, int num);

};