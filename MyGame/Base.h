#pragma once
#include "SystemControl.h"

class Base {
private:
	// マップ上の各種情報をビット集合で保持する二次元配列
	static int map[FIELD_Y][FIELD_X];

	// 指定位置のビット集合を参照値で返す
	int& rGetBit(std::pair<int, int> pos);

protected:
	static int distMap[FIELD_Y][FIELD_X];	// 各位置におけるプレイヤーまでの最短距離
	static std::pair<int, int> plyPos;		// プレイヤーの位置

	static const int BIT_POS_TOUCH;					// 進めないことを示すビットの位置
	static const int BIT_POS_WALL;					// 壁があることを示すビットの位置
	static const int BIT_POS_BLOCK;					// ブロックがあることを示すビットの位置
	static const int BIT_POS_BLOCK_BLOKEN_FLAG;		// ブロックに対する破壊判定を示すビットの位置
	static const int BIT_POS_DAMAGE_PLAYER_BIGIN;	// プレイヤーによるダメージを示すビットの始点
	static const int BIT_POS_DAMAGE_PLAYER_END;		// プレイヤーによるダメージを示すビットの終点
	static const int BIT_POS_IGNITION_FLAG;			// 引火フラグを示すビットの位置
	static const int BIT_POS_DAMAGE_ENEMY_BIGIN;	// 敵によるダメージを示すビットの始点
	static const int BIT_POS_DAMAGE_ENEMY_END;		// 敵によるダメージを示すビットの終点
	static const int BIT_POS_ITEM_BIGIN;			// アイテム番号を示すビットの始点
	static const int BIT_POS_ITEM_END;				// アイテム番号を示すビットの終点

public:

	// 指定された範囲のビットが示す整数を返す
	int getBitNum(int POS_BIGIN, int POS_END, const int &bit);

	// 指定された範囲のビットを取り除く
	void removeBitRange(int POS_BIGIN, int POS_END, int &bit);

	// すべてのビットを取り除く
	void clearBit(std::pair<int, int> pos);
	
	// 進めないことを示すビットが立っているか判定する
	bool isTouch(std::pair<int, int> pos);

	// 進めないことを示すビットを立てる
	void setTouch(std::pair<int, int> pos);

	// 進めないことを示すビットを取り除く
	void removeTouch(std::pair<int, int> pos);

	// 壁を示すビットが立っているか判定する
	bool isWall(std::pair<int, int> pos);

	// 壁を示すビットと進めないことを示すビットを立てる
	void setWall(std::pair<int, int> pos);

	// ブロックを示すビットが立っているか判定する
	bool isBlock(std::pair<int, int> pos);

	// ブロックを示すビットと進めないことを示すビットを立てる
	void setBlock(std::pair<int, int> pos);

	// ブロックを示すビットと進めないことを示すビットを取り除く
	void removeBlock(std::pair<int, int> pos);

	// ブロックの破壊フラグを示すビットを立てる
	void setBlockBlokenFlag(std::pair<int, int> pos);

	// ブロックの破壊フラグを示すビットが立っているか判定する
	bool isBlokenBlock(std::pair<int, int> pos);

	// すべてのダメージと引火フラグを取り除く
	void removeDamage(std::pair<int, int> pos);

	// 引火フラグが立っているか判定する
	bool isIgnition(std::pair<int, int> pos);

	// プレイヤーによるダメージを返す
	int getDamagePlayer(std::pair<int, int> pos);

	// プレイヤーによるダメージを示すビットを立てる
	void setDamagePlayer(std::pair<int, int> pos, int damage);

	// 敵によるダメージを返す
	int getDamageEnemy(std::pair<int, int> pos);

	// 敵によるダメージを示すビットを立てる
	void setDamageEnemy(std::pair<int, int> pos, int damage, bool isIgnision);

	// アイテムを示すビットを取り除く
	void removeItem(std::pair<int, int> pos);

	// アイテムを示すビットを立てる
	void setItem(std::pair<int, int> pos, int itemNum);

	// アイテムの番号を取り出す。なければ-1を返す。
	int getItem(std::pair<int, int> pos);
};

