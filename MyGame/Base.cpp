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

// 指定位置のビット集合を参照値で返す
int& Base::rGetBit(std::pair<int, int> pos) { return map[pos.second][pos.first]; }

// 指定された範囲のビットが示す整数を返す
int Base::getBitNum(int POS_BIGIN, int POS_END, const int &bit) { return (bit % (1 << POS_END)) >> POS_BIGIN; }

// 指定された範囲のビットを取り除く
void Base::removeBitRange(int POS_BIGIN, int POS_END, int & bit){ bit = (bit % (1 << POS_BIGIN)) | ((bit >> POS_END) << POS_END); }

// すべてのビットを取り除く
void Base::clearBit(std::pair<int, int> pos) { rGetBit(pos) = 0; }

// 進めないことを示すビットが立っているか判定する
bool Base::isTouch(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_TOUCH)) > 0; }

// 進めないことを示すビットを立てる
void Base::setTouch(std::pair<int, int> pos) { rGetBit(pos) |= (1 << BIT_POS_TOUCH); }

// 進めないことを示すビットを取り除く
void Base::removeTouch(std::pair<int, int> pos) { rGetBit(pos) &= ~(1 << BIT_POS_TOUCH); }

// 壁を示すビットが立っているか判定する
bool Base::isWall(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_WALL)) > 0; }

// 壁を示すビットと進めないことを示すビットを立てる
void Base::setWall(std::pair<int, int> pos){ rGetBit(pos) |= (1 << BIT_POS_WALL) | (1 << BIT_POS_TOUCH); }

// ブロックを示すビットが立っているか判定する
bool Base::isBlock(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_BLOCK)) > 0; }

// ブロックを示すビットと進めないことを示すビットを立てる
void Base::setBlock(std::pair<int, int> pos) { rGetBit(pos) |= (1 << BIT_POS_BLOCK) | 1 << BIT_POS_TOUCH; }

// ブロックを示すビットと進めないことを示すビットを取り除く
void Base::removeBlock(std::pair<int, int> pos) { rGetBit(pos) &= ~((1 << BIT_POS_BLOCK) | (1 << BIT_POS_TOUCH) | (1<<BIT_POS_BLOCK_BLOKEN_FLAG)); }

// ブロックの破壊フラグを示すビットを立てる
void Base::setBlockBlokenFlag(std::pair<int, int> pos) { rGetBit(pos) |= (1 << BIT_POS_BLOCK_BLOKEN_FLAG); }

// ブロックの破壊フラグを示すビットが立っているか判定する
bool Base::isBlokenBlock(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_BLOCK_BLOKEN_FLAG)) > 0; }

// すべてのダメージと引火フラグを取り除く
void Base::removeDamage(std::pair<int, int> pos) { removeBitRange(BIT_POS_DAMAGE_PLAYER_BIGIN,BIT_POS_DAMAGE_ENEMY_END,rGetBit(pos)); }

// 引火フラグが立っているか判定する
bool Base::isIgnition(std::pair<int, int> pos) { return (rGetBit(pos) & (1 << BIT_POS_IGNITION_FLAG)) > 0; }

// プレイヤーによるダメージを返す
int Base::getDamagePlayer(std::pair<int, int> pos) { return getBitNum(BIT_POS_DAMAGE_PLAYER_BIGIN, BIT_POS_DAMAGE_PLAYER_END, rGetBit(pos)); }

// プレイヤーによるダメージを示すビットを立てる
void Base::setDamagePlayer(std::pair<int, int> pos,int damage) {
	damage = max(getDamagePlayer(pos), damage);
	removeBitRange(BIT_POS_DAMAGE_PLAYER_BIGIN, BIT_POS_DAMAGE_PLAYER_END, rGetBit(pos));
	rGetBit(pos) |= (damage << BIT_POS_DAMAGE_PLAYER_BIGIN) | (1 << BIT_POS_IGNITION_FLAG);
}

// 敵によるダメージを返す
int Base::getDamageEnemy(std::pair<int, int> pos) { return getBitNum(BIT_POS_DAMAGE_ENEMY_BIGIN, BIT_POS_DAMAGE_ENEMY_END, rGetBit(pos)); }

// 敵によるダメージを示すビットを立てる
void Base::setDamageEnemy(std::pair<int, int> pos, int damage, bool isIgnision) {
	damage = max(getDamageEnemy(pos), damage);
	removeBitRange(BIT_POS_DAMAGE_ENEMY_BIGIN, BIT_POS_DAMAGE_ENEMY_END, rGetBit(pos));
	rGetBit(pos) |= (damage << BIT_POS_DAMAGE_ENEMY_BIGIN) | (isIgnision << BIT_POS_IGNITION_FLAG);
}

// アイテムを示すビットを取り除く
void Base::removeItem(std::pair<int, int> pos) { removeBitRange(BIT_POS_ITEM_BIGIN, BIT_POS_ITEM_END, rGetBit(pos)); }

void Base::setItem(std::pair<int, int> pos, int itemNum){
	removeItem(pos);
	rGetBit(pos) |= ((1 + itemNum) << BIT_POS_ITEM_BIGIN);
}

// アイテムの番号を取り出す。なければ-1を返す。
int Base::getItem(std::pair<int, int> pos) { return getBitNum(BIT_POS_ITEM_BIGIN, BIT_POS_ITEM_END, rGetBit(pos)) - 1;}
