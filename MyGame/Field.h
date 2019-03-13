#pragma once
#include "Base.h"
class Field :public Base
{
	// イメージ・サウンドハンドル
	int floorImage;
	int wallImage;
	int blockImage;
	int itemImage[8];

	// プレイヤーまでの最短距離を描画するかの判定フラグ
	bool drawDistFlag = 0;

	// アイテムの出現率
	int itemRate;

	// distMap更新時の再帰処理関数
	void dfs(int x, int y, int cnt);

public:

	// フィールド情報の初期化
	void initField(int initBlockNum, int initItemRate);

	// 画像を読み込む
	void inputImage();

	// フィールド情報を更新する
	void fieldUpdate();

	// フィールド情報を描画する
	void drawField();

	// 各地点におけるプレイヤーまでの最短距離を更新する
	void distMapUpdate(std::pair<int, int> plrPos);

	// 各地点におけるプレイヤーまでの最短距離をマップ上に表示する
	void drawDistMap();

	// 配列の引数の位置にあるアイテムイメージハンドルを返す
	int getItemImage(int num);
};

