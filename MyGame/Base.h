#pragma once
#include "SystemControl.h"

class Base {
private:
	// �}�b�v��̊e������r�b�g�W���ŕێ�����񎟌��z��
	static int map[FIELD_Y][FIELD_X];

	// �w��ʒu�̃r�b�g�W�����Q�ƒl�ŕԂ�
	int& rGetBit(std::pair<int, int> pos);

protected:
	static int distMap[FIELD_Y][FIELD_X];	// �e�ʒu�ɂ�����v���C���[�܂ł̍ŒZ����
	static std::pair<int, int> plyPos;		// �v���C���[�̈ʒu

	static const int BIT_POS_TOUCH;					// �i�߂Ȃ����Ƃ������r�b�g�̈ʒu
	static const int BIT_POS_WALL;					// �ǂ����邱�Ƃ������r�b�g�̈ʒu
	static const int BIT_POS_BLOCK;					// �u���b�N�����邱�Ƃ������r�b�g�̈ʒu
	static const int BIT_POS_BLOCK_BLOKEN_FLAG;		// �u���b�N�ɑ΂���j�󔻒�������r�b�g�̈ʒu
	static const int BIT_POS_DAMAGE_PLAYER_BIGIN;	// �v���C���[�ɂ��_���[�W�������r�b�g�̎n�_
	static const int BIT_POS_DAMAGE_PLAYER_END;		// �v���C���[�ɂ��_���[�W�������r�b�g�̏I�_
	static const int BIT_POS_IGNITION_FLAG;			// ���΃t���O�������r�b�g�̈ʒu
	static const int BIT_POS_DAMAGE_ENEMY_BIGIN;	// �G�ɂ��_���[�W�������r�b�g�̎n�_
	static const int BIT_POS_DAMAGE_ENEMY_END;		// �G�ɂ��_���[�W�������r�b�g�̏I�_
	static const int BIT_POS_ITEM_BIGIN;			// �A�C�e���ԍ��������r�b�g�̎n�_
	static const int BIT_POS_ITEM_END;				// �A�C�e���ԍ��������r�b�g�̏I�_

public:

	// �w�肳�ꂽ�͈͂̃r�b�g������������Ԃ�
	int getBitNum(int POS_BIGIN, int POS_END, const int &bit);

	// �w�肳�ꂽ�͈͂̃r�b�g����菜��
	void removeBitRange(int POS_BIGIN, int POS_END, int &bit);

	// ���ׂẴr�b�g����菜��
	void clearBit(std::pair<int, int> pos);
	
	// �i�߂Ȃ����Ƃ������r�b�g�������Ă��邩���肷��
	bool isTouch(std::pair<int, int> pos);

	// �i�߂Ȃ����Ƃ������r�b�g�𗧂Ă�
	void setTouch(std::pair<int, int> pos);

	// �i�߂Ȃ����Ƃ������r�b�g����菜��
	void removeTouch(std::pair<int, int> pos);

	// �ǂ������r�b�g�������Ă��邩���肷��
	bool isWall(std::pair<int, int> pos);

	// �ǂ������r�b�g�Ɛi�߂Ȃ����Ƃ������r�b�g�𗧂Ă�
	void setWall(std::pair<int, int> pos);

	// �u���b�N�������r�b�g�������Ă��邩���肷��
	bool isBlock(std::pair<int, int> pos);

	// �u���b�N�������r�b�g�Ɛi�߂Ȃ����Ƃ������r�b�g�𗧂Ă�
	void setBlock(std::pair<int, int> pos);

	// �u���b�N�������r�b�g�Ɛi�߂Ȃ����Ƃ������r�b�g����菜��
	void removeBlock(std::pair<int, int> pos);

	// �u���b�N�̔j��t���O�������r�b�g�𗧂Ă�
	void setBlockBlokenFlag(std::pair<int, int> pos);

	// �u���b�N�̔j��t���O�������r�b�g�������Ă��邩���肷��
	bool isBlokenBlock(std::pair<int, int> pos);

	// ���ׂẴ_���[�W�ƈ��΃t���O����菜��
	void removeDamage(std::pair<int, int> pos);

	// ���΃t���O�������Ă��邩���肷��
	bool isIgnition(std::pair<int, int> pos);

	// �v���C���[�ɂ��_���[�W��Ԃ�
	int getDamagePlayer(std::pair<int, int> pos);

	// �v���C���[�ɂ��_���[�W�������r�b�g�𗧂Ă�
	void setDamagePlayer(std::pair<int, int> pos, int damage);

	// �G�ɂ��_���[�W��Ԃ�
	int getDamageEnemy(std::pair<int, int> pos);

	// �G�ɂ��_���[�W�������r�b�g�𗧂Ă�
	void setDamageEnemy(std::pair<int, int> pos, int damage, bool isIgnision);

	// �A�C�e���������r�b�g����菜��
	void removeItem(std::pair<int, int> pos);

	// �A�C�e���������r�b�g�𗧂Ă�
	void setItem(std::pair<int, int> pos, int itemNum);

	// �A�C�e���̔ԍ������o���B�Ȃ����-1��Ԃ��B
	int getItem(std::pair<int, int> pos);
};

