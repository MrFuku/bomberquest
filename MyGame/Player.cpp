#include "Player.h"

void Player::initPlayer(const int & initType, const int & initLife, const double & initSpeed, const int & initAttack, int & initBombType, int & initBombRange, int & initBombMaxNum){
	for (int i = 0; i < 12; i++) {
		image[i] = playerImage[initType][i];
	}
	characterType = PLAYER;
	x = 32;
	y = 32;
	muki = 2;
	life = initLife;
	alive = 1;
	removeFlag = 0;
	speed = initSpeed;
	attack = initAttack;
	bombType = initBombType;
	bombRange = initBombRange;
	bombMaxNum = initBombMaxNum;
	bombRandom = 0;
	pickUpItemSound = LoadSoundMem("Sounds/Menu/heal02.mp3");
}

// Bomb配列に新たなBombインスタンスを追加する
void Player::setBomb(std::vector<Bomb>& bombs){
	if (bombs.size() >= bombMaxNum || !IsRepeatedKey(KEY_INPUT_SPACE) || alive == 0) return;
	int _x = plyPos.first;
	int _y = plyPos.second;
	if (isTouch({ _x, _y })) return;
	Bomb::insertBomb( _x, _y, bombType, bombRange, attack, bombRandom, bombs);
}

// キー入力に応じて歩くフラグと向きフラグを切り替える
bool Player::walkingFlagUpdate() {
	int _x = (int)x;
	int _y = (int)y;
	
	if (_x % 32 == 0 && _y % 32 == 0) {         //座標が32で割り切れたら入力可能
		walkingFlag = 1;         //歩くフラグを立てる。
		if (IsRepeatedKey(KEY_INPUT_UP))  //上ボタンが押されたら
			muki = 0;         //上向きフラグを立てる
		else if (IsRepeatedKey(KEY_INPUT_LEFT))  //左ボタンが押されたら
			muki = 1;         //左向きフラグを立てる
		else if (IsRepeatedKey(KEY_INPUT_DOWN))  //下ボタンが押されたら
			muki = 2;         //下向きフラグを立てる
		else if (IsRepeatedKey(KEY_INPUT_RIGHT))  //右ボタンが押されたら
			muki = 3;         //右向きフラグを立てる
		else                                    //何のボタンも押されてなかったら
			walkingFlag = 0; //歩かないフラグを立てる
		if (walkingFlag && !isAbleToGo()) {
			walkingFlag = 0;
		}
		return walkingFlag;
	}
	return 0;
}

void Player::pickUpItem(){
	int itemNum = getItem(plyPos);
	if (itemNum != -1) {
		if (itemNum == 0) {			// 攻撃力アップ効果。
			attack = min(attack + 10, 10000);
		}
		else if (itemNum == 1) {	// 設置爆弾数増加。
			bombMaxNum = min(bombMaxNum + 1, 50);
		}
		else if (itemNum == 2) {	// 爆弾タイプ１に変更。貫通型
			bombType = 1;
		}
		else if (itemNum == 3) {	// 爆弾タイプ２に変更。広範囲型
			bombType = 2;
		}
		else if (itemNum == 4) {	// 体力増加および爆発時間ランダム状態解除
			life += 100;
			bombRandom = 0;
		}
		else if (itemNum == 5) {	// 爆発時間ランダム状態化
			bombRandom = 1;
		}
		else if (itemNum == 6) {	// 移動速度上昇
			speed = min(speed + 0.5, 20);
		}
		else if (itemNum == 7) {	// 爆発範囲の増加
			bombRange = min(bombRange + 1, 20);
		}

		PlaySoundMem(pickUpItemSound, DX_PLAYTYPE_BACK);
		removeItem(plyPos);
	}
}

// プレイヤー情報を更新する
void Player::playerUpdate(std::vector<Bomb> &bombs) {

	setBomb(bombs);
	walkingFlagUpdate();
	move();
	pickUpItem();
	damageUpdate();
	plyPos = getPos();
}

void Player::drowStatus(){

	DrawFormatString(10, 10, GetColor(255, 255, 255), "ＨＰ　 %d", life);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "攻撃力 %d", attack);
	DrawFormatString(160, 10, GetColor(255, 255, 255), "最大爆弾数 %d", bombMaxNum);
	DrawFormatString(160, 40, GetColor(255, 255, 255), "爆発範囲   %d", bombRange);
	if (bombRandom) {
		DrawFormatString(310, 10, GetColor(255, 255, 255), "爆発時間ランダム状態");
	}
}
