#include "Character.h"

int Character::playerImage[3][12];
int Character::enemyImage[3][12];
int Character::questionImage[6];
int Character::magicSound;
int Character::magicEfect[3];


// キャラクターおよび各種イメージ・サウンドを取り込み

void Character::inputImage(){

	LoadDivGraph("Images/Character/hero.png", 12, 3, 4, 32, 32, playerImage[0]);
	LoadDivGraph("Images/Character/elf.png", 12, 3, 4, 32, 32, playerImage[1]);
	LoadDivGraph("Images/Character/cat.png", 12, 3, 4, 32, 32, playerImage[2]);
	LoadDivGraph("Images/Character/mook.png", 12, 3, 4, 32, 32, enemyImage[0]);
	LoadDivGraph("Images/Character/skeleton.png", 12, 3, 4, 32, 32, enemyImage[1]);
	LoadDivGraph("Images/Character/witch.png", 12, 3, 4, 32, 32, enemyImage[2]);
	LoadDivGraph("Images/Character/emotion.png", 6, 6, 1, 32, 32, questionImage);
	magicSound = LoadSoundMem("Sounds/Field/powerup01.mp3");
	int tmp[32];
	LoadDivGraph("Images/Character/magicEfect.png", 24, 6, 4, 48, 48, tmp);
	for (int i = 0; i < 3; i++) magicEfect[i] = tmp[21 + i];
}


// ダメージ処理。ダメージを受けている間は新たなダメージを受けない
// ライフが０、かつダメージタイムが０でリムーブフラグを立てる
// 敵同士の攻撃は無効

void Character::damageUpdate() {

	if (damageTime > 0) {
		damageTime--;
		return;
	}
	if (life <= 0) {
		removeFlag = 1;
		return;
	}
	int damage = getDamagePlayer(getPos());
	if (characterType== PLAYER) damage = max(damage, getDamageEnemy(getPos()));
	if (damage > 0) {
		life = max(0, life - damage);
		damageTime = 180;
		alive = (life > 0);
	}
}


// リムーブフラグが立っているか判定

bool Character::isRemove() { return removeFlag; }


// キャラクターを描画。向きや位置によってイメージハンドルを使い分ける
// ダメージを受けている最中および死亡時は表示を変化させる

void Character::draw() {
	int imageId;
	int _x = (int)x;
	int _y = (int)y;
	
	imageId = (_x % 32 + _y % 32) / 12;
	if (muki == 1) imageId += 3;
	if (muki == 3) imageId += 6;
	if (muki == 0) imageId += 9;
	if (alive == 0) imageId = damageTime / 3 % 12;
	if (damageTime > 0 && damageTime / 3 % 2 || (alive + damageTime == 0)) return;
	DrawGraph(_x, _y + MARGIN_TOP, image[imageId], TRUE);
}


// 歩くフラグ及び生存フラグが立っていた場合向いている方向に進む
// 移動の前後で３２の倍数をまたぐときは、３２の倍数の位置で止まるように処理

void Character::move() {

	if (walkingFlag == 1 && alive == 1) {        //歩くフラグが立っていたら
		if ((int)x % 32 != 0 || (int)y % 32 != 0) {
			int _x = x + dx[muki] * speed;
			int _y = y + dy[muki] * speed;
			if (muki == 0) {
				if (_y / 32 < (int)y / 32) {
					y = _y + 32 - (_y + 32) % 32;
					return;
				}
			}
			else if (muki == 1) {
				if (_x / 32 < (int)x / 32) {
					x = _x + 32 - (_x + 32) % 32;
					return;
				}
			}
			else if (muki == 2) {
				if (_y / 32 > (int)y / 32) {
					y = _y - (_y + 32) % 32;
					return;
				}
			}
			else {
				if (_x / 32 > (int)x / 32) {
					x = _x - (_x + 32) % 32;
					return;
				}
			}
		}
		x += dx[muki] * speed;
		y += dy[muki] * speed;
	}
}


// キャラクターが向いている方向に進めるか判定
// ３２の倍数の位置での使用のみ想定

bool Character::isAbleToGo() {

	if (!isTouch({ (int)x / 32 + dx[muki], (int)y / 32 + dy[muki] })) {
		return true;
	}
	else {
		return (characterType == GHOST && !isWall({ (int)x / 32 + dx[muki], (int)y / 32 + dy[muki] }));
	}
}


// キャラクターの現在位置及び前方１マスが端っこ（外壁のすぐ内側）であるか判定する
bool Character::isEdge() {
	int _x = (int)x / 32;
	int _y = (int)y / 32;
	int nx = _x + dx[muki];
	int ny = _y + dy[muki];
	return (_x == 1 || _x == FIELD_X - 2 || _y == 1 || _y == FIELD_Y - 2) && (nx == 1 || nx == FIELD_X - 2 || ny == 1 || ny == FIELD_Y - 2);
}


// キャラクターのいるマスをペアにして返す。移動中であればより近い方のマスの値とする
std::pair<int, int> Character::getPos() {
	int _x = (int)x;
	int _y = (int)y;
	if (_x % 32 > 15) _x += 32;
	if (_y % 32 > 15) _y += 32;
	return { _x / 32,_y / 32 };
}


// キャラクターのイメージハンドルを返す
int Character::getImageHandle(int isPlayer, int type, int num){
	if (isPlayer) {
		return playerImage[type][num];
	}
	else {
		return enemyImage[type][num];
	}
}
