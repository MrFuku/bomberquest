#include "SystemControl.h"

// キーの入力状態を更新する
int UpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			key[i]++;     // 加算
		}
		else {              // 押されていなければ
			key[i] = 0;   // 0にする
		}
	}
	return 0;
}

// 指定されたキーが連続して押下されているか判定する
bool IsRepeatedKey(int keyCode) { return (key[keyCode] > 0); }

// 指定されたキーの連続入力回数を返す
int GetKeyRepeatNum(int keyCode) { return key[keyCode]; }

// 指定されたキーが押下された瞬間であるか判定する
bool isPushedKey(int keyCode) {
	if (key[keyCode] == 1) {
		key[keyCode] = 2;
		return true;
	}
	else {
		return false;
	}
}
