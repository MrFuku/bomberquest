#include "GameControl.h"

// イメージおよびサウンドデータを読み込み、各種ハンドルに格納。フォントの設定

GameControl::GameControl(){

	// イメージの読み込み
	
	msgFlame1 = LoadGraph("Images/Menu/frame.jpg");
	msgFlame2 = LoadGraph("Images/Menu/frame2.png");
	msgFlame3 = LoadGraph("Images/Menu/frame3.jpg");
	fukidashiImage = LoadGraph("Images/Menu/fukidasi.png");

	tokenImageTitle = LoadGraph("Images/Menu/Title.png");
	tokenImageMenuOperation = LoadGraph("Images/Menu/tokenImageMenuOperation.png");
	tokenImageBattleOperation = LoadGraph("Images/Menu/tokenImageBattleOperation.png");
	tokenImageBattleRule = LoadGraph("Images/Menu/tokenImageBattleRule.png");
	tokenImageItemDescription = LoadGraph("Images/Menu/tokenImageItemDescription.png");
	tokenImageEnemyDescription = LoadGraph("Images/Menu/tokenImageEnemyDescription.png");
	tokenImageCursor = LoadGraph("Images/Menu/tokenImageCursor.png");
	tokenImageEnter = LoadGraph("Images/Menu/tokenImageEnter.png");
	tokenImageBackSpace = LoadGraph("Images/Menu/tokenImageBackSpace.png");
	tokenImageSpace = LoadGraph("Images/Menu/tokenImageSpace.png");
	tokenImageShift = LoadGraph("Images/Menu/tokenImageShift.png");
	tokenImageBattleRuleDescription = LoadGraph("Images/Menu/tokenImageBattleRuleDescription.png");
	tokenImageSelectChar = LoadGraph("Images/Menu/selectChar.png");
	tokenImageCharName[0] = LoadGraph("Images/Menu/nameYusha.png");
	tokenImageCharName[1] = LoadGraph("Images/Menu/nameElf.png");
	tokenImageCharName[2] = LoadGraph("Images/Menu/nameTama.png");
	tokenImageSelectPlay = LoadGraph("Images/Menu/selectPlay.png");
	tokenImageLevelChoose = LoadGraph("Images/Menu/levelChoose.png");
	tokenImageMyChoose = LoadGraph("Images/Menu/myChoose.png");
	tokenImageSelectLevel = LoadGraph("Images/Menu/tokenImageSelectLevel.png");
	tokenImageLevel[0] = LoadGraph("Images/Menu/tokenImageEasy.png");
	tokenImageLevel[1] = LoadGraph("Images/Menu/tokenImageMidium.png");
	tokenImageLevel[2] = LoadGraph("Images/Menu/tokenImageHard.png");
	tokenImagePlayerStatusH1 = LoadGraph("Images/Menu/tokenImagePlayerStatus.png");
	tokenImagePlayerStatus[0] = LoadGraph("Images/Menu/tokenImageHP.png");
	tokenImagePlayerStatus[1] = LoadGraph("Images/Menu/tokenImageSpeed.png");
	tokenImagePlayerStatus[2] = LoadGraph("Images/Menu/tokenImageAttack.png");
	tokenImagePlayerStatus[3] = LoadGraph("Images/Menu/tokenImageAttackRange.png");
	tokenImagePlayerStatus[4] = LoadGraph("Images/Menu/tokenImageBombType.png");
	tokenImagePlayerStatus[5] = LoadGraph("Images/Menu/tokenImageMaxBomb.png");
	tokenImageSelectEnemyNum = LoadGraph("Images/Menu/tokenImageSelectEnemyNumH1.png");
	tokenImageEnemyName[0] = LoadGraph("Images/Menu/tokenImageGhost.png");
	tokenImageEnemyName[1] = LoadGraph("Images/Menu/tokenImageSkeleton.png");
	tokenImageEnemyName[2] = LoadGraph("Images/Menu/tokenImageWitch.png");
	tokenImageOtherConfig = LoadGraph("Images/Menu/tokenImageOtherConfig.png");
	tokenImageBlockNum = LoadGraph("Images/Menu/tokenImageBlockNum.png");
	tokenImageItemNum = LoadGraph("Images/Menu/tokenImageItemNum.png");

	LoadDivGraph("Images/Menu/pipo-emotion.png", 3, 3, 1, 32, 32, cursorImage);


	// サウンドの読み込み。BGMの再生開始

	titleSound = LoadSoundMem("Sounds/Menu/title.mp3");
	cursorSound = LoadSoundMem("Sounds/Menu/cursor.mp3");
	decisionSound = LoadSoundMem("Sounds/Menu/decision.mp3");
	cancelSound = LoadSoundMem("Sounds/Menu/cancel.mp3");
	PlaySoundMem(titleSound, DX_PLAYTYPE_LOOP);

	// フォントの設定

	ChangeFont("ＭＳ ゴシック");
}


//********************************
//		汎用的処理関数群		**
//********************************


// キャラクターが３人並んだ描画を処理

void GameControl::drawPlayers() {

	DrawRotaGraph(150, 440, 5.5, 0, player.getImageHandle(1, 0, fps.getCount() / 10 % 3), TRUE);
	DrawRotaGraph(370, 440, 5.5, 0, player.getImageHandle(1, 1, fps.getCount() / 10 % 3), TRUE);
	DrawRotaGraph(590, 430, 5.65, 0, player.getImageHandle(1, 2, fps.getCount() / 10 % 3), TRUE);
}


// 左右カーソルの連続入力時間に応じて戻り値が増える

int GameControl::getPushNum(){

	int x = 0;
	if (GetKeyRepeatNum(KEY_INPUT_RIGHT) > 0) x = GetKeyRepeatNum(KEY_INPUT_RIGHT);
	else if (GetKeyRepeatNum(KEY_INPUT_LEFT) > 0) x = -GetKeyRepeatNum(KEY_INPUT_LEFT);

	if (abs(x) > 0) {
		int tmp = abs(x);
		if (tmp < 60) {
			tmp = (tmp % 15 == 1);
		}
		else if (tmp < 120) {
			tmp = (tmp % 7 == 1);
		}
		else if (tmp < 180) {
			tmp = (tmp % 2 == 1);
		}
		else if (tmp < 240) {
			tmp = (tmp % 2 == 1) * 5;
		}
		else {
			tmp = 30;
		}
		x = tmp * (x > 0 ? 1 : -1);
	}
	if (x) {
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	}
	return x;
}


// 上下カーソルの入力に応じて選択している行を変更。指定した最大値を超えると０に戻る

void GameControl::changeSelectNum(int maxNum){

	bool soundFlag = false;
	if (isPushedKey(KEY_INPUT_UP)) currentSelectNum--, soundFlag = true;
	if (isPushedKey(KEY_INPUT_DOWN)) currentSelectNum++, soundFlag = true;;
	currentSelectNum = (currentSelectNum + maxNum) % maxNum;
	if (soundFlag) {
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	}
}


// バックスペースもしくはエンターキーの入力に応じて引数のゲームモードに切り替える。

void GameControl::changeGameMode(GameMode backMode, GameMode nextMode){

	if (isPushedKey(KEY_INPUT_BACK)) {
		currentGameMode = backMode;
		PlaySoundMem(cancelSound, DX_PLAYTYPE_BACK);
		currentSelectNum = 0;
	}
	if (isPushedKey(KEY_INPUT_RETURN)) {
		currentGameMode = nextMode;
		PlaySoundMem(decisionSound, DX_PLAYTYPE_BACK);
		currentSelectNum = 0;
	}
}


// 見出しのトークンイメージとフレームを表示

void GameControl::drawFlame1(int tokenImageFlame1){

	DrawRotaGraph(368, 100, 0.55, 0, msgFlame1, TRUE);
	DrawRotaGraph(368, 100, 0.65, 0, tokenImageFlame1, TRUE);
}


// ゲームの説明画面に遷移する
// 説明画面から戻るときのモードを引数にする

void GameControl::openGameManual(GameMode nowGameMode){

	previousGameMode = nowGameMode;
	currentGameMode = MODE_GAME_MANUAL;
	PlaySoundMem(decisionSound, DX_PLAYTYPE_BACK);
}


// タイトル画面での処理

void GameControl::modeTitle(){

	DrawFormatString(230, 235 - fps.getCount() / 30 % 2 * 3, GetColor(255, 255, 255), "Enterキーを押してゲームをはじめる");
	DrawFormatString(260, 265 - fps.getCount() / 30 % 2 * 3, GetColor(255, 255, 255), "Escキーでゲームをやめる");
	DrawFormatString(233, 295 - fps.getCount() / 30 % 2 * 3, GetColor(255, 255, 255), "スペースキーでゲームの説明をみる");
	DrawRotaGraph(565, 140, 1.3, 0, tokenImageTitle, TRUE);
	DrawRotaGraph(675, 130, 2.7, 0, Fire::getBombImage(0, fps.getCount() / 15 % 2 + 1), TRUE);
	drawPlayers();
	changeGameMode(MODE_TITLE, MODE_SELECT_CHAR);
	if (isPushedKey(KEY_INPUT_SPACE)) {
		openGameManual(MODE_TITLE);
	}
}


// ゲームの説明画面を処理
// 全５ページを横一列に同時に描画し、位置をスライドさせることでページを切り替える

int modeGameManualNowPage = 0;
int modeGameManualNowPageAxis = 0;
void GameControl::modeGameManual() {

	// 画面遷移はスライドで演出する
	if (modeGameManualNowPage * 736 > modeGameManualNowPageAxis) modeGameManualNowPageAxis+=46;
	if (modeGameManualNowPage * 736 < modeGameManualNowPageAxis) modeGameManualNowPageAxis-=46;

	// 見出し部分の表示
	int imageHandle[] = { tokenImageMenuOperation ,tokenImageBattleOperation,tokenImageBattleRule, tokenImageItemDescription,tokenImageEnemyDescription };
	for (int i = 0; i < 5; i++) {
		DrawRotaGraph(368 + 736 * i - modeGameManualNowPageAxis, 100, 0.55, 0, msgFlame1, TRUE);
		DrawRotaGraph(368 + 736 * i - modeGameManualNowPageAxis, 100, 0.65, 0, imageHandle[i], TRUE);
		DrawRotaGraph(368 + 736 * i - modeGameManualNowPageAxis, 350, 0.55, 0, msgFlame3, TRUE);
	}
	
	// １ページ目　メニューの操作
	DrawRotaGraph(270 + 736 * 0 - modeGameManualNowPageAxis, 270 + 80 * 0, 0.55, 0, tokenImageCursor, TRUE);
	DrawRotaGraph(270 + 736 * 0 - modeGameManualNowPageAxis, 270 + 80 * 1, 0.55, 0, tokenImageEnter, TRUE);
	DrawRotaGraph(270 + 736 * 0 - modeGameManualNowPageAxis, 270 + 80 * 2, 0.55, 0, tokenImageBackSpace, TRUE);
	DrawFormatString(400 + 736 * 0 - modeGameManualNowPageAxis, 257 + 80 * 0, GetColor(50, 50, 50), "カーソルの移動・数値の変更");
	DrawFormatString(400 + 736 * 0 - modeGameManualNowPageAxis, 257 + 80 * 1, GetColor(50, 50, 50), "決定");
	DrawFormatString(400 + 736 * 0 - modeGameManualNowPageAxis, 257 + 80 * 2, GetColor(50, 50, 50), "戻る・キャンセル");

	// ２ページ目　戦いの操作
	DrawRotaGraph(270 + 736 * 1 - modeGameManualNowPageAxis, 270 + 80 * 0, 0.55, 0, tokenImageCursor, TRUE);
	DrawRotaGraph(270 + 736 * 1 - modeGameManualNowPageAxis, 270 + 80 * 1, 0.55, 0, tokenImageSpace, TRUE);
	DrawRotaGraph(270 + 736 * 1 - modeGameManualNowPageAxis, 270 + 80 * 2, 0.55, 0, tokenImageShift, TRUE);
	DrawFormatString(400 + 736 * 1 - modeGameManualNowPageAxis, 257 + 80 * 0, GetColor(50, 50, 50), "プレイヤーの移動");
	DrawFormatString(400 + 736 * 1 - modeGameManualNowPageAxis, 257 + 80 * 1, GetColor(50, 50, 50), "爆弾をおく");
	DrawFormatString(400 + 736 * 1 - modeGameManualNowPageAxis, 257 + 80 * 2, GetColor(50, 50, 50), "メニュー画面の表示");

	// ３ページ目　戦いの説明
	DrawRotaGraph(375 + 736 * 2 - modeGameManualNowPageAxis, 180 + 80 * 2, 0.65, 0, tokenImageBattleRuleDescription, TRUE);

	// ４ページ目　アイテムの説明
	for (int i = 0; i < 4; i++) {
		DrawRotaGraph(100 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * i, 1.5, 0, field.getItemImage(i), TRUE);
		DrawRotaGraph(410 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * i, 1.5, 0, field.getItemImage(i+4), TRUE);
	}
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 232 + 80 * 0, GetColor(50, 50, 50), "攻撃力がアップします");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 232 + 80 * 1, GetColor(50, 50, 50), "爆弾をおける数が増えます");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 220 + 80 * 2, GetColor(50, 50, 50), "爆発がブロックを貫通する");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * 2, GetColor(50, 50, 50), "ようになります");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 220 + 80 * 3, GetColor(50, 50, 50), "爆発がとても広い範囲に");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * 3, GetColor(50, 50, 50), "広がるようになります");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 220 + 80 * 0, GetColor(50, 50, 50), "体力が増えます");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * 0, GetColor(50, 50, 50), "爆弾の爆発時間が元に戻ります");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 220 + 80 * 1, GetColor(50, 50, 50), "爆弾の爆発時間がランダムに");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * 1, GetColor(50, 50, 50), "なります");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 232 + 80 * 2, GetColor(50, 50, 50), "移動速度があがります");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 232 + 80 * 3, GetColor(50, 50, 50), "爆発の範囲が広くなります");

	// ５ページ目　敵の説明
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(125 + 736 * 4 - modeGameManualNowPageAxis, 260 + 90 * i, 1.5, 0, player.getImageHandle(0, i, fps.getCount() / 10 % 3), TRUE);
		DrawRotaGraph(270 + 736 * 4 - modeGameManualNowPageAxis, 260 + 90 * i, 1, 0, tokenImageEnemyName[i], TRUE);
	}
	DrawFormatString(340 + 736 * 4 - modeGameManualNowPageAxis, 255 + 90 * 0, GetColor(50, 50, 50), "ブロックや爆弾をすり抜けて移動します");
	DrawFormatString(340 + 736 * 4 - modeGameManualNowPageAxis, 255 + 90 * 1, GetColor(50, 50, 50), "プレイヤーを見つけると追いかけてきます");
	DrawFormatString(340 + 736 * 4 - modeGameManualNowPageAxis, 240 + 90 * 2, GetColor(50, 50, 50), "炎の魔法を使って、プレイヤーや");
	DrawFormatString(340 + 736 * 4 - modeGameManualNowPageAxis, 260 + 90 * 2, GetColor(50, 50, 50), "ブロックを攻撃します");


	// ページ遷移が可能であることを示す矢印の描画
	if (modeGameManualNowPage > 0) {
		DrawRotaGraph(50, 340, 1.2, 3.141592654*0.5, cursorImage[fps.getCount() / 20 % 3], TRUE);
	}
	if (modeGameManualNowPage < 4) {
		DrawRotaGraph(686, 340, 1.2, 3.141592654*1.5, cursorImage[fps.getCount() / 20 % 3], TRUE);
	}
	
	// 左右カーソルの入力に応じてページを切り替え
	if (isPushedKey(KEY_INPUT_LEFT)) {
		modeGameManualNowPage = max(0, modeGameManualNowPage - 1);
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	}
	if (isPushedKey(KEY_INPUT_RIGHT)) {
		modeGameManualNowPage = min(4, modeGameManualNowPage + 1);
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	}

	// ゲーム説明を終了して遷移元のモードに戻る
	if (isPushedKey(KEY_INPUT_BACK)) {
		currentGameMode = previousGameMode;
		modeGameManualNowPage = 0;
		modeGameManualNowPageAxis = 0;
		PlaySoundMem(cancelSound, DX_PLAYTYPE_BACK);
	}
}


// キャラクターの選択画面を処理

void GameControl::modeSelectChar(){

	drawFlame1(tokenImageSelectChar);
	drawPlayers();
	DrawRotaGraph(210 + initPlayerType * 220, 310 - fps.getCount() / 30 % 2 * 3, 0.25, 0, fukidashiImage, TRUE);
	DrawRotaGraph(210 + initPlayerType * 220, 300 - fps.getCount() / 30 % 2 * 3, 0.6, 0, tokenImageCharName[initPlayerType], TRUE);
	
	if (isPushedKey(KEY_INPUT_LEFT)) initPlayerType = (initPlayerType + 2) % 3, PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	if (isPushedKey(KEY_INPUT_RIGHT)) initPlayerType = (initPlayerType + 1) % 3, PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	changeGameMode(MODE_TITLE, MODE_SELECT_PLAY);
}


// 遊び方選択画面を処理

void GameControl::modeSelectPlay(){

	drawFlame1(tokenImageSelectPlay);
	if (isPushedKey(KEY_INPUT_LEFT) || isPushedKey(KEY_INPUT_RIGHT)) {
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
		currentSelectNum ^= 1;
	}

	if (currentSelectNum == 0) {
		DrawRotaGraph(200, 400 + fps.getCount() / 15 % 2 * 4, 0.6 + 0.05, 0, msgFlame2, TRUE);
		DrawRotaGraph(200, 400 + fps.getCount() / 15 % 2 * 4, 0.8 + 0.05, 0, tokenImageLevelChoose, TRUE);
		DrawRotaGraph(540, 400, 0.6, 0, msgFlame2, TRUE);
		DrawRotaGraph(540, 400, 0.8, 0, tokenImageMyChoose, TRUE);
	}
	else {
		DrawRotaGraph(200, 400, 0.6, 0, msgFlame2, TRUE);
		DrawRotaGraph(200, 400, 0.8, 0, tokenImageLevelChoose, TRUE);
		DrawRotaGraph(540, 400 + fps.getCount() / 15 % 2 * 4, 0.6 + 0.05, 0, msgFlame2, TRUE);
		DrawRotaGraph(540, 400 + fps.getCount() / 15 % 2 * 4, 0.8 + 0.05, 0, tokenImageMyChoose, TRUE);
	}

	if (currentSelectNum==0) {
		changeGameMode(MODE_SELECT_CHAR, MODE_SELECT_LEVEL);
	}
	else {
		changeGameMode(MODE_SELECT_CHAR, MODE_CUSTOM_PLAYER);
	}
	if (currentGameMode != MODE_SELECT_PLAY) {
		initSelectLevel = -1;
		modeInitBattle();
	}
}


// 難易度選択画面を処理

void GameControl::modeSelectLevel(){

	changeSelectNum(3);
	initSelectLevel = currentSelectNum;
	drawFlame1(tokenImageSelectLevel);
	DrawRotaGraph(360, 400, 0.6 + 0.05, 0, msgFlame2, TRUE);
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(360, 335 + i * 55, 0.6 + (i == currentSelectNum)*0.05, 0, tokenImageLevel[i], TRUE);
	}
	DrawRotaGraph(270 + (currentSelectNum == 1 ? 15 : 0) + (currentSelectNum == 2 ? -13 : 0), 335 + currentSelectNum * 55, 1.2, 0, Fire::getBombImage(initBombType, fps.getCount() / 15 % 2 + 1), TRUE);
	
	previousGameMode = MODE_SELECT_LEVEL;
	changeGameMode(MODE_SELECT_PLAY, MODE_COMFIRMATION);
}


// バトル開始前の確認画面を処理

void GameControl::modeConfirmation() {

	changeSelectNum(2);
	DrawRotaGraph(360, 350, 0.6 + 0.05, 0, msgFlame2, TRUE);
	DrawFormatString(270, 270, GetColor(180, 0, 0), "設定した内容でゲームを");
	DrawFormatString(270, 290, GetColor(180, 0, 0), "はじめてもよろしいですか？");
	DrawFormatString(340, 340, GetColor(0 + (currentSelectNum != 0) * 180, 0 + (currentSelectNum != 0) * 180, 0 + (currentSelectNum != 0) * 180), "はい");
	DrawFormatString(335, 380, GetColor(0 + (currentSelectNum != 1) * 180, 0 + (currentSelectNum != 1) * 180, 0 + (currentSelectNum != 1) * 180), "いいえ");

	if (currentSelectNum == 0) {
		changeGameMode(previousGameMode, MODE_INIT_BATTLE);
	}
	else {
		changeGameMode(previousGameMode, previousGameMode);
	}
}


// 設定内容をもとにバトルを初期化

void GameControl::modeInitBattle() {

	if (initSelectLevel != 3) {
		if (initSelectLevel == 0 || initSelectLevel == -1) {
			initPlayerLife = 100;
			initPlayerSpeed = 2;
			initPlayerAttackPower = 20;
			initPlayerAttackRange = initBombMaxNum = 3;
			initEnemyNum_Ghost = initEnemyNum_Skeleton = initEnemyNum_Witch = 3;
		}
		else if (initSelectLevel == 1) {
			initPlayerLife = 60;
			initPlayerSpeed = 1.6;
			initPlayerAttackPower = 15;
			initPlayerAttackRange = initBombMaxNum = 2;
			initEnemyNum_Ghost = initEnemyNum_Skeleton = initEnemyNum_Witch = 4;
		}
		else if (initSelectLevel == 2) {
			initPlayerLife = 40;
			initPlayerSpeed = 1.2;
			initPlayerAttackPower = 10;
			initPlayerAttackRange = initBombMaxNum = 1;
			initEnemyNum_Ghost = initEnemyNum_Skeleton = initEnemyNum_Witch = 5;
		}
		initBlockNum = 160;
		initItemRate = 30;
		initBombType = 0;
		
	}

	if (initSelectLevel != -1) {
		field.initField(initBlockNum, initItemRate);
		player.initPlayer(initPlayerType, initPlayerLife, initPlayerSpeed, initPlayerAttackPower, initBombType, initPlayerAttackRange, initBombMaxNum);
		enemys = Enemy::initEnemys(initEnemyNum_Ghost, initEnemyNum_Skeleton, initEnemyNum_Witch);
		bombs.clear();
		fires.clear();
		currentGameMode = MODE_PLAY_BATTLE;
	}
}


// バトルモードのメイン処理関数

int modeBattleMenuFlag = 0;
void GameControl::modePlayBattle() {

	// バトルの描画フェーズ
	drawBattle();
	
	if (modeBattleMenuFlag == 1) {	
		// バトルメニューフェーズ
		battleMenu();
	}
	else {
		// バトル状況の更新フェーズ
		updateBattle();
	}


	if (currentSelectNum < 3) {
		if (isPushedKey(KEY_INPUT_LSHIFT) || isPushedKey(KEY_INPUT_RSHIFT) || (modeBattleMenuFlag &&isPushedKey(KEY_INPUT_BACK))) {
			modeBattleMenuFlag ^= 1;
			currentSelectNum = 0;
			PlaySoundMem(decisionSound, DX_PLAYTYPE_BACK);
		}
	}

	if (enemys.size() == 0 || player.isRemove()) {
		DrawRotaGraph(360, 350, 0.6 + 0.05, 0, msgFlame2, TRUE);
		if (enemys.size() == 0) {
			DrawFormatString(310, 340, GetColor(180, 0, 0), "勝ちました");
		}
		else {
			DrawFormatString(310, 340, GetColor(180, 0, 0), "負けました");
		}
		ScreenFlip();
		Sleep(3000);
		currentGameMode = MODE_TITLE;
	}
}

void GameControl::drawBattle(){

	field.drawField();
	field.drawDistMap();
	Fire::drawFires(fires);
	Bomb::drawBombs(bombs);
	Enemy::drawEnemys(enemys);
	player.draw();
	player.drowStatus();
}

void GameControl::updateBattle(){

	field.fieldUpdate();
	Fire::firesUpdate(fires);
	Bomb::bombsUpdate(bombs, fires);
	Enemy::enemysUpdate(fires, enemys);
	player.playerUpdate(bombs);
	if (--distMapUpdateCount <= 0) {
		field.distMapUpdate(player.getPos());
		distMapUpdateCount = 10;
	}
}

void GameControl::battleMenu(){

	if (currentSelectNum < 3) {
		changeSelectNum(3);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 210);
	DrawRotaGraph(360, 350, 0.6 + 0.05, 0, msgFlame2, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (currentSelectNum < 3) {
		DrawFormatString(300, 300, GetColor(0 + (currentSelectNum != 0) * 180, 0 + (currentSelectNum != 0) * 180, 0 + (currentSelectNum != 0) * 180), "ゲームをつづける");
		DrawFormatString(300, 350, GetColor(0 + (currentSelectNum != 1) * 180, 0 + (currentSelectNum != 1) * 180, 0 + (currentSelectNum != 1) * 180), "ゲームの説明をみる");
		DrawFormatString(300, 400, GetColor(0 + (currentSelectNum != 2) * 180, 0 + (currentSelectNum != 2) * 180, 0 + (currentSelectNum != 2) * 180), "ゲームをやめる");
	}

	if (currentSelectNum < 3) {

		if (currentSelectNum == 0) {
			if (isPushedKey(KEY_INPUT_RETURN)) {
				modeBattleMenuFlag ^= 1;
				currentSelectNum = 0;
				PlaySoundMem(decisionSound, DX_PLAYTYPE_BACK);
			}

		}
		else if (currentSelectNum == 1) {
			if (isPushedKey(KEY_INPUT_RETURN)) {
				openGameManual(MODE_PLAY_BATTLE);
			}

		}
		else if (currentSelectNum == 2) {
			if (isPushedKey(KEY_INPUT_RETURN)) {
				currentSelectNum = 3;
			}
		}
	}
	else {
		DrawFormatString(270, 270, GetColor(180, 0, 0), "本当にゲームをやめますか？");
		DrawFormatString(330, 330, GetColor(0 + (currentSelectNum != 3) * 180, 0 + (currentSelectNum != 3) * 180, 0 + (currentSelectNum != 3) * 180), "いいえ");
		DrawFormatString(340, 380, GetColor(0 + (currentSelectNum != 4) * 180, 0 + (currentSelectNum != 4) * 180, 0 + (currentSelectNum != 4) * 180), "はい");
		if (isPushedKey(KEY_INPUT_BACK)) {
			currentSelectNum = 2;
			PlaySoundMem(decisionSound, DX_PLAYTYPE_BACK);
		}
		if (currentSelectNum == 3) {
			if (isPushedKey(KEY_INPUT_RETURN)) {
				currentSelectNum = 2;
				PlaySoundMem(decisionSound, DX_PLAYTYPE_BACK);
			}
			if (isPushedKey(KEY_INPUT_DOWN)) {
				currentSelectNum = 4;
				PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
			}
		}
		else if (currentSelectNum == 4) {
			if (isPushedKey(KEY_INPUT_RETURN)) {
				currentGameMode = MODE_TITLE;
				currentSelectNum = 0;
				modeBattleMenuFlag = 0;
				PlaySoundMem(decisionSound, DX_PLAYTYPE_BACK);
			}
			if (isPushedKey(KEY_INPUT_UP)) {
				currentSelectNum = 3;
				PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
			}
		}
	}
}


// ゲーム処理のメインコントロール関数

bool GameControl::mainControl(){
	
	field.inputImage();
	player.inputImage();	
	Fire::initFire();

	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && UpdateKey() == 0) {
		
		// ゲームモードに応じて処理を分岐
		switch (currentGameMode)
		{
		case MODE_TITLE:			// タイトル画面の処理
			modeTitle();
			break;

		case MODE_GAME_MANUAL:		// ゲーム説明モード
			modeGameManual();
			break;

		case MODE_SELECT_CHAR:		// キャラクター選択画面用モード
			modeSelectChar();
			break;

		case MODE_SELECT_PLAY:		// 遊び方選択画面用モード
			modeSelectPlay();
			break;

		case MODE_SELECT_LEVEL:		// 難易度選択画面用モード
			modeSelectLevel();
			break;

		case MODE_CUSTOM_PLAYER:	// プレイヤー情報の設定モード
			modeCustomPlayer();
			break;

		case MODE_CUSTOM_ENEMY:		// 敵情報の設定モード
			modeCustomEnemy();
			break;

		case MODE_CUSTOM_OTHER:		// その他情報の設定モード
			modeCustomOther();
			break;

		case MODE_COMFIRMATION:		// その他情報の設定モード
			modeConfirmation();
			break;

		case MODE_INIT_BATTLE:		// バトルの初期化モード
			modeInitBattle();
			break;

		case MODE_PLAY_BATTLE:		// バトル処理用モード
			modePlayBattle();
			break;

		case MODE_EXIT:				// ゲームの終了モード
			return true;
			break;

		default:
			return true;
			break;
		}

		fps.Control();	// FPSを調整

		if (isPushedKey(KEY_INPUT_ESCAPE)) {
			currentGameMode = MODE_EXIT;
		}
	}
	return true;
}