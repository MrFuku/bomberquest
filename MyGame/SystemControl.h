#pragma once
#include "DxLib.h"
#include "Fps.h"
#include <vector>

static const int FIELD_X = 23;
static const int FIELD_Y = 19;
static const int  MARGIN_TOP = 32 * 2;

static int dy[4] = { -1, 0, 1, 0 };
static int dx[4] = { 0, -1, 0, 1 };

static int key[256];			// キーの入力状態を格納する

static int gameModeNum = 0;		// 現在のゲームモードを示す
const int GAMEMODE_MENU = 0;
const int GAMEMODE_VILLAGE = 1;
const int GAMEMODE_BATTLE = 2;
static int changedModeFlag = 1;	// ゲームモードが変更されたときにフラグを立てる

// キーの入力状態を更新する
int UpdateKey();

// 指定されたキーが連続して押下されているか判定する
bool IsRepeatedKey(int keyCode);

// 指定されたキーの連続入力回数を返す
int GetKeyRepeatNum(int keyCode);

// 指定されたキーが押下された瞬間であるか判定する
bool isPushedKey(int keyCode);
