#pragma once
#include "Character.h"
#include "Fire.h"

class Enemy : public Character{
protected:
	
	int foldWalkFlag;				// �����t���O��܂�m���̕ꐔ���w��		30/foldWalkFlag
	int standWalkFlag;				// �����t���O�𗧂Ă�m���̕ꐔ���w��	30/standWalkFlag
	int throughBlock = 0;			// �u���b�N�𔲂����
	int chaserFlag = 0;				// �ǐՎ҃t���O
	int viewDist = 0;				// �G�̎��F�\����
	int doubtTime = 0;				// �v���C���[�����������́H��Ԃ̎c�莞��
	int attackFlag = 0;				// �U����Ԃ�\���t���O
	int attackTime = 0;				// �U����Ԃ̎c�莞��
	std::pair<int, int> targetPos;	// �v���C���[�����������Ƀv���C���[�������Ă����ʒu
public:
	
	// �G�̏���������
	void initEnemy(int initType);

	// �����������G�̏���Enemy�z��Ɋi�[���Ԃ�
	static std::vector<Enemy> initEnemys(const int &mookNum, const int &skeletonNum, const int &witchNum);

	// ���������ŕ����t���O�ƌ����t���O��؂�ւ���
	void walkingFlagUpdate();
	
	// �v���C���[�̂���n�_��ڎw���čŒZ���[�g�Ɍ�����ς���
	void chasePlayer();

	// ���@�g���̎˒������Ƀu���b�N�����邩����
	bool witchBlockJudge();

	// �v���C���[�̑��݂��@�m�i?��ԁj�����Ƃ��̍s��������
	void doubtFunc();

	// �U����Ԃ̏���
	void attackFunc(std::vector<Fire> & fires);

	// ���E�Ƀv���C���[�����݂��邩����
	int discoveryPlayer();

	// �G�̏�Ԃ��X�V����
	void enemyUpadate(std::vector<Fire> & fires);

	// �G�̂���ʒu�Ƀ_���[�W���������
	void addDamage();

	// Enemy�z��̓G�����X�V����
	static void enemysUpdate(std::vector<Fire> & fires, std::vector<Enemy> & enemys);

	// Enemy�z���Enemy��`�悷��
	static void drawEnemys(std::vector<Enemy> & enemys);
};

