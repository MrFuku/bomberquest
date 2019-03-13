#include "Enemy.h"

#define createEnemys(type, num) for (int i = 0; i < num; i++) {Enemy e;e.initEnemy(type);enemys.push_back(e);}
#define transImage(type) for (int i = 0; i < 12; i++) {image[i]=enemyImage[type][i];}

int eraseBlock = 0;

// 敵の情報を初期化

void Enemy::initEnemy(int initType){

	// 初期位置を決める。プレイヤーの近く及び衝突判定のある位置にはおかない。
	do {
		x = GetRand(FIELD_X - 2);
		y = GetRand(FIELD_Y - 2);
		x += 1;
		y += 1;
	} while ((x < 6 && y < 6) || isTouch({ x, y }));

	// 敵に隣接するブロックがあれば一定確率で取り除く。ただし合計３０個まで。
	for (int i = 0; i < 4; i++) {
		if (eraseBlock<30&&isBlock({ x + dx[i], y + dy[i] }) && GetRand(3) != 0) {
			removeBlock({ x + dx[i], y + dy[i] });
			eraseBlock++;
		}
	}

	if (initType == 0) {		// GHOSTの設定
		characterType = GHOST;
		throughBlock = 1;
		life = 20;
		foldWalkFlag = 60;
		standWalkFlag=200;
	}
	else if(initType == 1) {	// SKELETONの設定
		characterType = SKELETON;
		chaserFlag = 1;
		viewDist = 5;
		life = 40;
		foldWalkFlag = 200;
		standWalkFlag = 2000;
	}
	else {						// WITCHの設定
		characterType = WITCH;
		viewDist = 5;
		life = 30;
		foldWalkFlag = 100;
		standWalkFlag = 1000;
	}

	transImage(initType);		// マクロでイメージを取り込む
	x *= 32;					// 位置をビットに変換
	y *= 32;
	attack = 5;
	speed = 1;
}


// 初期化した敵の情報をEnemy配列に格納し返す

std::vector<Enemy> Enemy::initEnemys(const int & mookNum, const int & skeletonNum, const int & witchNum){

	eraseBlock = 0;
	std::vector<Enemy> enemys;
	createEnemys(0, mookNum);
	createEnemys(1, skeletonNum);
	createEnemys(2, witchNum);
	return enemys;
}

// 乱数処理で歩くフラグと向きフラグを切り替える

void Enemy::walkingFlagUpdate() {

	if (doubtTime) return;							// ？状態のとき歩くフラグはここで操作しない
	if (attackTime&&characterType == WITCH) return;	// WITCHが攻撃状態のときは歩くフラグを立てない
	
	// ３２で割れる位置にいない場合はフラグを操作しない
	if ((int)x % 32 != 0 || (int)y % 32 != 0 ) {
		return;
	}
	if (walkingFlag == 0) {
		// 歩くフラグが折れていたら、一定確率でフラグを立てる
		if (GetRand(standWalkFlag) < 30) {
			walkingFlag = 1;
			muki = GetRand(3);
		}
	}
	else {
		// 歩くフラグが立っていたら、一定確率でフラグを折る
		if (GetRand(foldWalkFlag) <= 30) {
			walkingFlag = 0;
		}
		else {
			if (!isAbleToGo()||isEdge()) {
				muki = GetRand(3);
			}
		}
	}

	// 障害物判定
	if (walkingFlag) walkingFlag = isAbleToGo();

	// SKELETONが攻撃状態のときはプレイヤー追跡関数を呼び出す
	if (attackTime&&characterType == SKELETON) chasePlayer();
}


// プレイヤーのいる地点を目指して最短ルートに向きを変える

void Enemy::chasePlayer() {
	if ((int)x % 32 != 0 || (int)y % 32 != 0) return;
	int mn = 1e9;
	int _x = (int)x / 32;
	int _y = (int)y / 32;
	for (int i = 0; i < 4; i++) {
		int tmp = distMap[_y + dy[i]][_x + dx[i]];
		if (tmp == 1e9) continue;
		if (mn == tmp && GetRand(2) == 1) muki = i;
		if (mn > tmp) {
			mn = tmp;
			muki = i;
		}
	}
	walkingFlag = isAbleToGo();
}


// 魔法使いの射程圏内にブロックがあるか判定

bool Enemy::witchBlockJudge(){
	if (characterType != WITCH || attackTime || doubtTime || (int)x % 32 != 0 || (int)y % 32 != 0) return 0;
	if (GetRand(700) != 0) return 0;
	int _x = (int)x / 32;
	int _y = (int)y / 32;
	for (int i = 0; i < viewDist; i++) {
		_x += dx[muki];
		_y += dy[muki];
		if (isWall({ _x,_y })) return 0;
		if (isBlock({ _x,_y })) {
			attackFlag = 1;
			attackTime = 70;
			walkingFlag = 0;
			return 1;
		}
	}
	return 0;
}


// プレイヤーの存在を察知（?状態）したときの行動を処理

void Enemy::doubtFunc() {

	if (attackFlag || alive == 0) return;

	// ？状態でないときの行動
	if (doubtTime == 0) {

		int _muki = discoveryPlayer();
		if (_muki == -1 || abs(muki - muki) == 2) return;

		if (characterType == WITCH) {		// WITCH
			muki = _muki;
			doubtTime = 60;
			walkingFlag = 0;
		}
		else if(characterType ==SKELETON) {	// SKELETON
			targetPos = plyPos;
			muki = _muki;
			doubtTime = 120;
			walkingFlag = 0;
		}
	}

	// ？状態のときの行動
	else {

		if (characterType == WITCH) {			// WITCH
			walkingFlag = 0;
			if (--doubtTime < 10) {
				int _muki = discoveryPlayer();
				if (muki == _muki) {
					doubtTime = 0;
					attackFlag = 1;
					attackTime = 100;
				}
			}
		}
		else if (characterType == SKELETON) {	// SKELETON
			if (doubtTime > 60) {
				doubtTime--;
				return;
			}
			else {
				if ((int)x % 32 == 0 && (int)y % 32 == 0) {
					int _x = (int)x / 32;
					int _y = (int)y / 32;
					int targetDist = abs(targetPos.first - _x) + abs(targetPos.second - _y);
					if (targetDist) {
						int _muki = discoveryPlayer();
						if (_muki != -1) {
							attackFlag = 1;
							attackTime = 1010;
							muki = _muki;
							doubtTime = 0;
							return;
						}
						for (int i = 1; i <= targetDist; i++) {
							if (isTouch({ _x + dx[muki] * i,_y + dy[muki] * i })) {
								doubtTime = 0;
								walkingFlag = 0;
								return;
							}
						}
						walkingFlag = 1;
					}
					else {
						walkingFlag = 0;
						doubtTime--;
						int _muki = discoveryPlayer();
						if (_muki != -1) {
							attackFlag = 1;
							attackTime = 1010;
							doubtTime = 0;
						}
					}
				}
			}
		}
	}
}


// 攻撃状態の処理

void Enemy::attackFunc(std::vector<Fire> & fires) {
	if (!attackTime) return;
	attackTime--;

	if (characterType == WITCH) {
		walkingFlag = 0;
		if (attackTime == 99) {
			PlaySoundMem(magicSound, DX_PLAYTYPE_BACK);
		}
		if (attackTime == 30) {
			Fire::setFireWitch((int)x / 32 + dx[muki], (int)y / 32 + dy[muki], viewDist - 1, muki, attack, fires);
		}
		if (attackTime == 0) {
			int _muki = discoveryPlayer();
			if (muki == _muki) {
				attackTime = 70;
			}
			else {
				attackFlag = 0;
			}
		}
	}
	else if (characterType == SKELETON) {
		if (attackTime == 1009) {
			PlaySoundMem(magicSound, DX_PLAYTYPE_BACK);
		}
		if (discoveryPlayer() != -1) {
			attackTime = max(attackTime, 500);
		}
		if (attackTime == 0) {
			attackFlag = 0;
		}
	}
}


// 視界にプレイヤーが存在するか判定
// 存在するならその方向（向き）を、いなければ-1を返す

int Enemy::discoveryPlayer(){

	int _x = (int)x;
	int _y = (int)y;
	if (_x % 32 != 0 || _y % 32 != 0) return -1;
	_x /= 32;
	_y /= 32;
	int _muki;
	int directDist = abs(plyPos.first - _x) + abs(plyPos.second - _y);
	int shortDist = distMap[_y][_x];
	if (directDist < shortDist || viewDist < shortDist) return -1;
	else {
		int _muki = -1;
		if (plyPos.first == _x) {
			if (plyPos.second < _y) _muki = 0;
			else return _muki = 2;
		}
		if (plyPos.second == _y) {
			if (plyPos.first < _x) _muki = 1;
			else _muki = 3;
		}
		if (_muki != -1) {
			if (abs(muki - _muki) == 2) _muki = -1;
		}
		return _muki;
	}
}


// 敵の状態を更新する

void Enemy::enemyUpadate(std::vector<Fire> & fires) {
	
	if (alive) {
		witchBlockJudge();
		walkingFlagUpdate();
		doubtFunc();
		attackFunc(fires);
		addDamage();
		move();
		if (characterType == SKELETON) {
			speed = ((doubtTime || attackTime) ? 1 : 0.7);
		}
	}
	else {
		doubtTime = 0;
		attackFlag = 0;
		attackTime = 0;
		walkingFlag = 0;
	}
	damageUpdate();
}


// 敵のいる位置にダメージ判定をつける

void Enemy::addDamage() {
	setDamageEnemy(getPos(), attack, false);
}


// Enemy配列の敵情報を更新する

void Enemy::enemysUpdate(std::vector<Fire> & fires, std::vector<Enemy> & enemys){
	for (auto itr = enemys.begin(); itr != enemys.end();) {
		(*itr).enemyUpadate(fires);
		if ((*itr).isRemove()) {
			itr = enemys.erase(itr);
			continue;
		}
		itr++;
	}
}


// Enemy配列のEnemyを描画する

void Enemy::drawEnemys(std::vector<Enemy>& enemys){

	for (Enemy &enemy : enemys) {

		enemy.draw();

		// ？マークの描画
		if (enemy.doubtTime) {
			DrawRotaGraph(enemy.x + 17, enemy.y - 5 + MARGIN_TOP, 0.6, 0.0, questionImage[enemy.doubtTime / 10 % 3 + 3], TRUE);
		}

		
		if (enemy.attackTime) {

			// ！マークの描画
			if (enemy.attackTime > 70) {
				DrawRotaGraph(enemy.x + 17, enemy.y - 5 + MARGIN_TOP, 0.6, 0.0, questionImage[enemy.attackTime / 10 % 3], TRUE);
				
			}

			// WITCHが攻撃するときのエフェクトを描画
			else if(enemy.characterType==WITCH) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 210);
				DrawRotaGraph(enemy.x + 17, enemy.y + 15 + MARGIN_TOP, 0.6, 0.0, magicEfect[enemy.attackTime / 5 % 3], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			
		}
	}
}
