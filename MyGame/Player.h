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

	// プレイヤー情報の初期化
	void initPlayer(const int &initType, const int &initLife, const double &initSpeed, const int &initAttack, int &initBombType, int &initBombRange, int &initBombMaxNum);

	// Bomb配列に新たなBombインスタンスを追加する
	void setBomb(std::vector<Bomb> &bombs);

	// キー入力に応じて歩くフラグと向きフラグを切り替える
	bool walkingFlagUpdate();

	void pickUpItem();
	
	// プレイヤー情報を更新する
	void playerUpdate(std::vector<Bomb> &bombs);

	// プレイヤーのステータスを描画する
	void drowStatus();
	
};