#pragma once
#include "Fire.h"

class Bomb :public Fire{
private:
	// ボムタイプ０：通常弾。十字方向に爆発。非貫通
	// ボムタイプ１：貫通弾。十字方向に爆発。貫通
	// ボムタイプ２：広範囲弾。４５度傾いた正方形状に爆発。貫通。距離はマンハッタン距離換算
	int bombType;
	int range;			// 爆発の範囲
	bool randomFlag;	// ランダムフラグ。爆発のタイミングがランダムで決まる
	
public:

	// Bomb配列のBombインスタンスを描画する
	// 爆発までの残り時間によってイメージハンドルを使い分ける
	static void drawBombs(std::vector<Bomb> &bombs);
	
	// Bomb配列のBombインスタンスの状態を更新する
	static void bombsUpdate(std::vector<Bomb> &bombs, std::vector<Fire> &fires);

	// Bomb配列に新たなBombインスタンスを格納する
	static void insertBomb(int _x, int _y, int type, int _range, int _attack, bool random, std::vector<Bomb> &bombs);
};

