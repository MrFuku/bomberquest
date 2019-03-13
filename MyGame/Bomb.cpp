#include "Bomb.h"

// Bomb配列のBombインスタンスを描画する
// 爆発までの残り時間によってイメージハンドルを使い分ける
void Bomb::drawBombs(std::vector<Bomb>& bombs) {

	for (Bomb &bomb : bombs) {
		int _x = bomb.x * 32;
		int _y = bomb.y * 32 + MARGIN_TOP;
		int imageId = bomb.time / 20 % 2;
		if (bomb.time <= 200) imageId++;
		if (bomb.time <= 100) imageId += 2;
		if (bomb.time < 5) imageId = 5;
		if (bomb.randomFlag) imageId = 0;
		DrawGraph(_x , _y , bombImage[bomb.bombType][imageId], TRUE);
	}
}

// Bomb配列のBombインスタンスの状態を更新する
void Bomb::bombsUpdate(std::vector<Bomb>& bombs, std::vector<Fire>& fires) {

	for (auto itr = bombs.begin(); itr != bombs.end();) {

		if ((*itr).isIgnition((*itr).getPoint())) {		// 爆弾のある位置に引火フラグが立っていたら即時爆発
			(*itr).time = 0;
		}
		
		if ((*itr).randomFlag) {	// ランダムフラグが立っていれば一定確率でフラグが取り除かれる。それまではカウントしない
			if (GetRand(350) == 0) (*itr).randomFlag = 0;
		}
		else {
			(*itr).time--;
		}
		if ((*itr).time <= 0) {		// 残り時間０で新たなFireインスタンスを生成する
			(*itr).removeTouch((*itr).getPoint());
			Fire::setFire((*itr).x, (*itr).y, (*itr).range, (*itr).attack, (*itr).bombType, fires);
			itr = bombs.erase(itr);
			continue;
		}
		itr++;
	}
}

// Bomb配列に新たなBombインスタンスを格納する
void Bomb::insertBomb(int _x, int _y, int type, int _range, int _attack, bool random, std::vector<Bomb> &bombs){

	Bomb bomb;
	bomb.x = _x;
	bomb.y = _y;
	bomb.setTouch({ _x, _y });
	bomb.bombType = type;
	bomb.range = _range;
	bomb.attack = _attack;
	bomb.time = (random ? 100 : 200);
	bomb.randomFlag = random;
	bombs.push_back(bomb);
	PlaySoundMem(putBombSound, DX_PLAYTYPE_BACK);
}
