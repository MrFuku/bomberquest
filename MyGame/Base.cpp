#include "Base.h"

int Base::map[FIELD_Y][FIELD_X];
int Base::distMap[FIELD_Y][FIELD_X];
std::pair<int, int> Base::plyPos;

const int Base::BIT_POS_TOUCH = 0;
const int Base::BIT_POS_WALL = 1;
const int Base::BIT_POS_BLOCK = 2;
const int Base::BIT_POS_BLOCK_BLOKEN_FLAG = 3;
const int Base::BIT_POS_DAMAGE_PLAYER_BIGIN = 4;
const int Base::BIT_POS_DAMAGE_PLAYER_END = 18;
const int Base::BIT_POS_IGNITION_FLAG = 18;
const int Base::BIT_POS_DAMAGE_ENEMY_BIGIN = 19;
const int Base::BIT_POS_DAMAGE_ENEMY_END = 24;
const int Base::BIT_POS_ITEM_BIGIN = 24;
const int Base::BIT_POS_ITEM_END = 28;

// �w��ʒu�̃r�b�g�W�����Q�ƒl�ŕԂ�
int& Base::rGetBit(std::pair<int, int> pos) { return map[pos.second][pos.first]; }

// �w�肳�ꂽ�͈͂̃r�b�g������������Ԃ�
int Base::getBitNum(int POS_BIGIN, int POS_END, const int &bit) { return (bit % (1 << POS_END)) >> POS_BIGIN; }

// �w�肳�ꂽ�͈͂̃r�b�g����菜��
void Base::removeBitRange(int POS_BIGIN, int POS_END, int & bit){ bit = (bit % (1 << POS_BIGIN)) | ((bit >> POS_END) << POS_END); }

// ���ׂẴr�b�g����菜��
void Base::clearBit(std::pair<int, int> pos) { rGetBit(pos) = 0; }

// �i�߂Ȃ����Ƃ������r�b�g�������Ă��邩���肷��
bool Base::isTouch(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_TOUCH)) > 0; }

// �i�߂Ȃ����Ƃ������r�b�g�𗧂Ă�
void Base::setTouch(std::pair<int, int> pos) { rGetBit(pos) |= (1 << BIT_POS_TOUCH); }

// �i�߂Ȃ����Ƃ������r�b�g����菜��
void Base::removeTouch(std::pair<int, int> pos) { rGetBit(pos) &= ~(1 << BIT_POS_TOUCH); }

// �ǂ������r�b�g�������Ă��邩���肷��
bool Base::isWall(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_WALL)) > 0; }

// �ǂ������r�b�g�Ɛi�߂Ȃ����Ƃ������r�b�g�𗧂Ă�
void Base::setWall(std::pair<int, int> pos){ rGetBit(pos) |= (1 << BIT_POS_WALL) | (1 << BIT_POS_TOUCH); }

// �u���b�N�������r�b�g�������Ă��邩���肷��
bool Base::isBlock(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_BLOCK)) > 0; }

// �u���b�N�������r�b�g�Ɛi�߂Ȃ����Ƃ������r�b�g�𗧂Ă�
void Base::setBlock(std::pair<int, int> pos) { rGetBit(pos) |= (1 << BIT_POS_BLOCK) | 1 << BIT_POS_TOUCH; }

// �u���b�N�������r�b�g�Ɛi�߂Ȃ����Ƃ������r�b�g����菜��
void Base::removeBlock(std::pair<int, int> pos) { rGetBit(pos) &= ~((1 << BIT_POS_BLOCK) | (1 << BIT_POS_TOUCH) | (1<<BIT_POS_BLOCK_BLOKEN_FLAG)); }

// �u���b�N�̔j��t���O�������r�b�g�𗧂Ă�
void Base::setBlockBlokenFlag(std::pair<int, int> pos) { rGetBit(pos) |= (1 << BIT_POS_BLOCK_BLOKEN_FLAG); }

// �u���b�N�̔j��t���O�������r�b�g�������Ă��邩���肷��
bool Base::isBlokenBlock(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_BLOCK_BLOKEN_FLAG)) > 0; }

// ���ׂẴ_���[�W�ƈ��΃t���O����菜��
void Base::removeDamage(std::pair<int, int> pos) { removeBitRange(BIT_POS_DAMAGE_PLAYER_BIGIN,BIT_POS_DAMAGE_ENEMY_END,rGetBit(pos)); }

// ���΃t���O�������Ă��邩���肷��
bool Base::isIgnition(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_IGNITION_FLAG)) > 0; }

// �v���C���[�ɂ��_���[�W��Ԃ�
int Base::getDamagePlayer(std::pair<int, int> pos) { return getBitNum(BIT_POS_DAMAGE_PLAYER_BIGIN, BIT_POS_DAMAGE_PLAYER_END, rGetBit(pos)); }

// �v���C���[�ɂ��_���[�W�������r�b�g�𗧂Ă�
void Base::setDamagePlayer(std::pair<int, int> pos,int damage) {
	damage = max(getDamagePlayer(pos), damage);
	removeBitRange(BIT_POS_DAMAGE_PLAYER_BIGIN, BIT_POS_DAMAGE_PLAYER_END, rGetBit(pos));
	rGetBit(pos) |= (damage << BIT_POS_DAMAGE_PLAYER_BIGIN) | (1 << BIT_POS_IGNITION_FLAG);
}

// �G�ɂ��_���[�W��Ԃ�
int Base::getDamageEnemy(std::pair<int, int> pos) { return getBitNum(BIT_POS_DAMAGE_ENEMY_BIGIN, BIT_POS_DAMAGE_ENEMY_END, rGetBit(pos)); }

// �G�ɂ��_���[�W�������r�b�g�𗧂Ă�
void Base::setDamageEnemy(std::pair<int, int> pos, int damage, bool isIgnision) {
	damage = max(getDamageEnemy(pos), damage);
	removeBitRange(BIT_POS_DAMAGE_ENEMY_BIGIN, BIT_POS_DAMAGE_ENEMY_END, rGetBit(pos));
	rGetBit(pos) |= (damage << BIT_POS_DAMAGE_ENEMY_BIGIN) | (isIgnision << BIT_POS_IGNITION_FLAG);
}

// �A�C�e���������r�b�g����菜��
void Base::removeItem(std::pair<int, int> pos) { removeBitRange(BIT_POS_ITEM_BIGIN, BIT_POS_ITEM_END, rGetBit(pos)); }

void Base::setItem(std::pair<int, int> pos, int itemNum){
	removeItem(pos);
	rGetBit(pos) |= ((1 + itemNum) << BIT_POS_ITEM_BIGIN);
}

// �A�C�e���̔ԍ������o���B�Ȃ����-1��Ԃ��B
int Base::getItem(std::pair<int, int> pos) { return getBitNum(BIT_POS_ITEM_BIGIN, BIT_POS_ITEM_END, rGetBit(pos)) - 1;}
