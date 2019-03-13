#pragma once
#include "Character.h"
#include "Fire.h"

class Enemy : public Character{
protected:
	
	int foldWalkFlag;				// 歩くフラグを折る確率の母数を指定		30/foldWalkFlag
	int standWalkFlag;				// 歩くフラグを立てる確率の母数を指定	30/standWalkFlag
	int throughBlock = 0;			// ブロックを抜けれる
	int chaserFlag = 0;				// 追跡者フラグ
	int viewDist = 0;				// 敵の視認可能距離
	int doubtTime = 0;				// プレイヤーを見つけた時の？状態の残り時間
	int attackFlag = 0;				// 攻撃状態を表すフラグ
	int attackTime = 0;				// 攻撃状態の残り時間
	std::pair<int, int> targetPos;	// プレイヤーを見つけた時にプレイヤーが立っていた位置
public:
	
	// 敵の情報を初期化
	void initEnemy(int initType);

	// 初期化した敵の情報をEnemy配列に格納し返す
	static std::vector<Enemy> initEnemys(const int &mookNum, const int &skeletonNum, const int &witchNum);

	// 乱数処理で歩くフラグと向きフラグを切り替える
	void walkingFlagUpdate();
	
	// プレイヤーのいる地点を目指して最短ルートに向きを変える
	void chasePlayer();

	// 魔法使いの射程圏内にブロックがあるか判定
	bool witchBlockJudge();

	// プレイヤーの存在を察知（?状態）したときの行動を処理
	void doubtFunc();

	// 攻撃状態の処理
	void attackFunc(std::vector<Fire> & fires);

	// 視界にプレイヤーが存在するか判定
	int discoveryPlayer();

	// 敵の状態を更新する
	void enemyUpadate(std::vector<Fire> & fires);

	// 敵のいる位置にダメージ判定をつける
	void addDamage();

	// Enemy配列の敵情報を更新する
	static void enemysUpdate(std::vector<Fire> & fires, std::vector<Enemy> & enemys);

	// Enemy配列のEnemyを描画する
	static void drawEnemys(std::vector<Enemy> & enemys);
};

