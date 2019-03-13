#pragma once
#include "SystemControl.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"

class GameControl{
private:

	// ゲーム処理制御用情報
	enum GameMode
	{
		MODE_TITLE,			// ゲームタイトル用モード
		MODE_GAME_MANUAL,	// ゲーム説明モード
		MODE_SELECT_CHAR,	// キャラクター選択画面用モード
		MODE_SELECT_PLAY,	// 遊び方選択画面用モード
		MODE_SELECT_LEVEL,	// 難易度選択画面用モード
		MODE_CUSTOM_PLAYER,	// プレイヤー情報の設定モード
		MODE_CUSTOM_ENEMY,	// 敵情報の設定モード
		MODE_CUSTOM_OTHER,	// その他情報の設定モード
		MODE_COMFIRMATION,	// バトル開始前の最終確認モード
		MODE_INIT_BATTLE,	// バトルの初期化モード
		MODE_PLAY_BATTLE,	// バトル処理用モード
		MODE_EXIT			// ゲームの終了モード
	};

	GameMode currentGameMode = MODE_TITLE;	// 現在のゲームモードを格納
	GameMode previousGameMode;				// 直前のゲームモードを格納。ゲーム説明モードから戻るときに使用
	int currentSelectNum = 0;				// 設定画面で現在選択中の位置を示す
	int distMapUpdateCount = 0;				// プレイヤーまでの最短距離を計測する間隔を測るカウンター
	Fps fps;								// FPS調整用クラス

	// イメージハンドル
	int msgFlame1;
	int msgFlame2;
	int msgFlame3;
	int fukidashiImage;
	
	int tokenImageTitle;
	int tokenImageMenuOperation;
	int tokenImageBattleOperation;
	int tokenImageBattleRule;
	int tokenImageItemDescription;
	int tokenImageEnemyDescription;
	int tokenImageCursor;
	int tokenImageEnter;
	int tokenImageBackSpace;
	int tokenImageSpace;
	int tokenImageShift;
	int tokenImageBattleRuleDescription;
	int tokenImageSelectChar;
	int tokenImageSelectPlay;
	int tokenImageCharName[3];
	int tokenImageLevelChoose;
	int tokenImageMyChoose;
	int tokenImageSelectLevel;
	int tokenImageLevel[3];
	int tokenImagePlayerStatusH1;
	int tokenImagePlayerStatus[7];
	int tokenImageSelectEnemyNum;
	int tokenImageEnemyName[3];
	int tokenImageOtherConfig;
	int tokenImageBlockNum;
	int tokenImageItemNum;

	int cursorImage[3];

	// サウンドハンドル用
	int titleSound;
	int cursorSound;
	int decisionSound;
	int cancelSound;

	// バトルの初期ステータス設定用変数
	int initPlayerType = 0;
	int initPlayerLife = 15000;
	double initPlayerSpeed = 2;
	int initPlayerAttackPower = 10;
	int initPlayerAttackRange = 10;
	int initBombType = 0;
	int initBombMaxNum = 10;
	int initEnemyNum_Ghost = 3;
	int initEnemyNum_Skeleton = 3;
	int initEnemyNum_Witch = 3;
	int initBlockNum = 120;
	int initItemRate = 0;
	int initSelectLevel;

	// バトル状況に関する情報
	Field field;					// フィールド情報（障害物・ブロック・ダメージ・アイテム等の判定）を管理するクラス	
	Player player;					// プレイヤー情報を管理するクラス
	std::vector<Enemy> enemys;		// 敵情報を管理するインスタンス配列
	std::vector<Fire> fires;		// 爆発の情報を管理するインスタンス配列
	std::vector<Bomb> bombs;		// 爆弾の情報を管理するインスタンス配列
	
public:

	// イメージおよびサウンドデータを読み込み、各種ハンドルに格納。フォントの設定
	GameControl();

	//********************************
	//		汎用的処理関数群		**
	//********************************

	// キャラクターが３人並んだ描画を処理
	void drawPlayers();

	// 左右カーソルの連続入力時間に応じて戻り値が増える
	int getPushNum();

	// 上下カーソルの入力に応じて選択している行を変更。指定した最大値を超えると０に戻る
	void changeSelectNum(int maxNum);

	// バックスペースもしくはエンターキーの入力に応じて引数のゲームモードに切り替える。
	void changeGameMode(GameMode backMode,GameMode nextMode);

	// 見出しのトークンイメージとフレームを表示
	void drawFlame1(int tokenImageFlame1);

	// ゲームの説明画面に遷移する
	void openGameManual(GameMode nowGameMode);
	
	//********************************
	//		モード別処理関数群		**
	//********************************

	// タイトル画面を処理
	void modeTitle();

	// ゲームの説明画面を処理
	void modeGameManual();

	// キャラクターの選択画面を処理
	void modeSelectChar();

	// 遊び方選択画面を処理
	void modeSelectPlay();

	// 難易度選択画面を処理
	void modeSelectLevel();
	
	// プレイヤー情報の設定画面を処理
	void modeCustomPlayer();

	// 敵情報の設定画面を処理
	void modeCustomEnemy();

	// その他情報の設定画面を処理
	void modeCustomOther();

	// バトル開始前の確認画面を処理
	void modeConfirmation();

	// 設定内容をもとにバトルを初期化
	void modeInitBattle();

	// バトルモードのメイン処理関数
	void modePlayBattle();

	void drawBattle();

	void updateBattle();

	void battleMenu();

	// ゲーム全体を統括するメイン関数。ここでモードごとに処理を振り分ける
	bool mainControl();

};

