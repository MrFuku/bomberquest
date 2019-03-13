#pragma once
#include "Character.h"
#include "Bomb.h"

class Player : public Character {
private:
	int bombType;
	int bombRange;
	int bombMaxNum;
	bool bombRandom;
	int pickUpItemSound;
public:

	// �v���C���[���̏�����
	void initPlayer(const int &initType, const int &initLife, const double &initSpeed, const int &initAttack, int &initBombType, int &initBombRange, int &initBombMaxNum);

	// Bomb�z��ɐV����Bomb�C���X�^���X��ǉ�����
	void setBomb(std::vector<Bomb> &bombs);

	// �L�[���͂ɉ����ĕ����t���O�ƌ����t���O��؂�ւ���
	bool walkingFlagUpdate();

	void pickUpItem();
	
	// �v���C���[�����X�V����
	void playerUpdate(std::vector<Bomb> &bombs);

	// �v���C���[�̃X�e�[�^�X��`�悷��
	void drowStatus();
	
};