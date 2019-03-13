#pragma once
#include "Base.h"
class Field :public Base
{
	// �C���[�W�E�T�E���h�n���h��
	int floorImage;
	int wallImage;
	int blockImage;
	int itemImage[8];

	// �v���C���[�܂ł̍ŒZ������`�悷�邩�̔���t���O
	bool drawDistFlag = 0;

	// �A�C�e���̏o����
	int itemRate;

	// distMap�X�V���̍ċA�����֐�
	void dfs(int x, int y, int cnt);

public:

	// �t�B�[���h���̏�����
	void initField(int initBlockNum, int initItemRate);

	// �摜��ǂݍ���
	void inputImage();

	// �t�B�[���h�����X�V����
	void fieldUpdate();

	// �t�B�[���h����`�悷��
	void drawField();

	// �e�n�_�ɂ�����v���C���[�܂ł̍ŒZ�������X�V����
	void distMapUpdate(std::pair<int, int> plrPos);

	// �e�n�_�ɂ�����v���C���[�܂ł̍ŒZ�������}�b�v��ɕ\������
	void drawDistMap();

	// �z��̈����̈ʒu�ɂ���A�C�e���C���[�W�n���h����Ԃ�
	int getItemImage(int num);
};

