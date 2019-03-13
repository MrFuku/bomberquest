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

	int time;				// Fireインスタンスの場合、残り燃焼時間。Bombインスタンスの場合、爆発までの残り時間を表す
	int attack;
	bool attackByPlayer;	// trueであればプレイヤーによる攻撃を示す、falseであれば敵（witch）による攻撃

public:
	
	// 爆発および爆弾の画像、サウンドを取り込む
	static void initFire();

	// インスタンスのxy座標をpairにして返す
	std::pair<int, int> getPoint();

	// Fire配列のFireを描画する
	static void drawFires(std::vector<Fire> &fires);

	// Fire配列のFireの状態を更新する
	static void firesUpdate(std::vector<Fire> &fires);

	// 配列にFireインスタンスを追加する
	static void setFire(int _x, int _y, int _range, int _attack, int bombType, std::vector<Fire> & fires);

	// 魔法使いの攻撃用
	static void setFireWitch(int _x, int _y, int _range, int _muki, int _attack, std::vector<Fire> & fires);

	// 爆弾のイメージハンドルを返す
	static int getBombImage(int type, int num);
};

