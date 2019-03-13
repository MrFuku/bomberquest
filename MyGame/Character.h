#pragma once
#include "Base.h"
class Character :public Base{

protected:
	
	enum CharacterType { PLAYER, GHOST, SKELETON, WITCH };

	// キャラクターおよび各種エフェクト用ハンドル
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

	// キャラクターおよび各種イメージ・サウンドを取り込み
	void inputImage();

	// ダメージ処理
	void damageUpdate();

	// リムーブフラグが立っているか判定
	bool isRemove();

	// キャラクターを描画
	void draw();

	// 歩くフラグ及び生存フラグが立っていた場合の歩行処理
	void move();

	// キャラクターが向いている方向に進めるか判定
	bool isAbleToGo();

	// キャラクターの現在位置及び前方１マスが端っこ（外壁のすぐ内側）であるか判定する
	bool isEdge();

	// キャラクターのいるマスをペアにして返す。移動中であればより近い方のマスの値とする
	std::pair<int, int> getPos();

	// キャラクターイメージのハンドルを返す
	int getImageHandle(int isPlayer, int type, int num);

};