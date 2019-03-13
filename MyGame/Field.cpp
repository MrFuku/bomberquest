#include "Field.h"


// フィールド情報の初期化

void Field::initField(int initBlockNum, int initItemRate) {

	for (int y = 0; y < FIELD_Y; y++) {
		for (int x = 0; x < FIELD_X; x++) {
			clearBit({ x,y });
			if (x == 0 || y == 0 || x == FIELD_X - 1 || y == FIELD_Y - 1 || (x % 2 == 0 && y % 2 == 0)) {
				setWall({ x,y });
			}
		}
	}

	for (int i = 0; i < initBlockNum; i++) {
		int x, y;
		do {
			x = GetRand(FIELD_X - 2);
			y = GetRand(FIELD_Y - 2);
			x++, y++;
		} while (isTouch({ x, y }) || (x + y < 4));
		setBlock({ x, y });
	}
	itemRate = initItemRate;
}


// 画像を読み込む

void Field::inputImage() {
	
	int tmpImage[100];

	// 床のイメージを取り込み
	LoadDivGraph("Images/Field/FieldImage2.png", 5, 1, 5, 16, 16, tmpImage);
	floorImage = tmpImage[4];

	// 壁のイメージを取り込み
	LoadDivGraph("Images/Field/FieldImage1.png", 18, 6, 3, 16, 16, tmpImage);
	wallImage = tmpImage[13];

	// ブロックのイメージを取り込み
	blockImage = tmpImage[0];

	// アイテムのイメージを取り込み
	itemImage[0] = LoadGraph("Images/Items/attackUp.png");
	itemImage[1] = LoadGraph("Images/Items/bombNumUp.png");
	itemImage[2] = LoadGraph("Images/Items/bombType1.png");
	itemImage[3] = LoadGraph("Images/Items/bombType2.jpg");
	itemImage[4] = LoadGraph("Images/Items/heal.png");
	itemImage[5] = LoadGraph("Images/Items/randomBomb.png");
	itemImage[6] = LoadGraph("Images/Items/speedUp.png");
	itemImage[7] = LoadGraph("Images/Items/fireRangeUp.png");
}

// フィールド情報を更新する

void Field::fieldUpdate() {

	for (int y = 0; y < FIELD_Y; y++) {
		for (int x = 0; x < FIELD_X; x++) {

			// 引火フラグ（爆発がある状態）を検知したとき
			if (isIgnition({ x,y })) {
				if (isBlock({ x,y })) {
					setBlockBlokenFlag({ x,y });	// ブロックに破壊判定を加える
				}
				removeItem({ x,y });				// アイテムは取り除く
			}
			// 引火フラグがない状態
			else {
				if (isBlokenBlock({ x,y })) {		// ブロックに破壊判定があればブロック取り除く
					removeBlock({ x,y });
					if (GetRand(100) < itemRate) {	// 一定の確率でアイテムが発生する
						int itemNum = GetRand(7);
						setItem({ x,y }, itemNum);
					}
				}
			}
			removeDamage({ x, y });
		}
	}
}


// フィールド情報を描画する

void Field::drawField() {
	
	for (int y = 0; y < FIELD_Y; y++) {
		for (int x = 0; x < FIELD_X; x++) {

			int _x = x * 32 + 16;
			int _y = y * 32 + 16 + MARGIN_TOP;

			if (isWall({ x, y })) {			// 壁を描画
				DrawRotaGraph(_x, _y, 2.0, 0.0, wallImage, TRUE);
				continue;
			}
			else {							// 床を描画
				DrawRotaGraph(_x, _y, 2.0, 0.0, floorImage, TRUE);
			}

			if (isBlock({ x, y })) {		// ブロックを描画
				DrawRotaGraph(_x, _y, 2.0, 0.0, blockImage, TRUE);
				continue;
			}

			int itemNum = getItem({ x,y });	// アイテムを描画
			if (itemNum != -1) {
				DrawRotaGraph(_x, _y, 0.9, 0.0, itemImage[itemNum], TRUE);
			}
		}
	}
}


// distMap更新時の再帰処理関数

void Field::dfs(int x, int y, int cnt){

	if ((isTouch({ x,y }) && cnt > 0) || distMap[y][x] <= cnt) return;
	distMap[y][x] = cnt;
	for (int i = 0; i < 4; i++) dfs(x + dx[i], y + dy[i], cnt + 1);
}


// 各地点における、プレイヤーまでの最短距離を更新する

void Field::distMapUpdate(std::pair<int, int> plrPos){
	
	for (int i = 0; i < FIELD_Y; i++) {
		for (int j = 0; j < FIELD_X; j++) {
			distMap[i][j] = 1e9;
		}
	}
	dfs(plrPos.first, plrPos.second, 0);
}


// 各地点におけるプレイヤーまでの最短距離をマップ上に表示する

void Field::drawDistMap(){

	if (isPushedKey(KEY_INPUT_1)) drawDistFlag ^= 1;
	if (!drawDistFlag) return;
	
	for (int y = 0; y < FIELD_Y; y++) {
		for (int x = 0; x < FIELD_X; x++) {
			if (distMap[y][x] != 1e9) {
				DrawFormatString(x * 32 + 2, y * 32 + 64 + 9, GetColor(50, 50, 50), "% d", distMap[y][x]);
			}
		}
	}
}

int Field::getItemImage(int num) { return itemImage[num];}
