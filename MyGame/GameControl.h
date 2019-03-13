#pragma once
#include "SystemControl.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"

class GameControl{
private:

	// �Q�[����������p���
	enum GameMode
	{
		MODE_TITLE,			// �Q�[���^�C�g���p���[�h
		MODE_GAME_MANUAL,	// �Q�[���������[�h
		MODE_SELECT_CHAR,	// �L�����N�^�[�I����ʗp���[�h
		MODE_SELECT_PLAY,	// �V�ѕ��I����ʗp���[�h
		MODE_SELECT_LEVEL,	// ��Փx�I����ʗp���[�h
		MODE_CUSTOM_PLAYER,	// �v���C���[���̐ݒ胂�[�h
		MODE_CUSTOM_ENEMY,	// �G���̐ݒ胂�[�h
		MODE_CUSTOM_OTHER,	// ���̑����̐ݒ胂�[�h
		MODE_COMFIRMATION,	// �o�g���J�n�O�̍ŏI�m�F���[�h
		MODE_INIT_BATTLE,	// �o�g���̏��������[�h
		MODE_PLAY_BATTLE,	// �o�g�������p���[�h
		MODE_EXIT			// �Q�[���̏I�����[�h
	};

	GameMode currentGameMode = MODE_TITLE;	// ���݂̃Q�[�����[�h���i�[
	GameMode previousGameMode;				// ���O�̃Q�[�����[�h���i�[�B�Q�[���������[�h����߂�Ƃ��Ɏg�p
	int currentSelectNum = 0;				// �ݒ��ʂŌ��ݑI�𒆂̈ʒu������
	int distMapUpdateCount = 0;				// �v���C���[�܂ł̍ŒZ�������v������Ԋu�𑪂�J�E���^�[
	Fps fps;								// FPS�����p�N���X

	// �C���[�W�n���h��
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

	// �T�E���h�n���h���p
	int titleSound;
	int cursorSound;
	int decisionSound;
	int cancelSound;

	// �o�g���̏����X�e�[�^�X�ݒ�p�ϐ�
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

	// �o�g���󋵂Ɋւ�����
	Field field;					// �t�B�[���h���i��Q���E�u���b�N�E�_���[�W�E�A�C�e�����̔���j���Ǘ�����N���X	
	Player player;					// �v���C���[�����Ǘ�����N���X
	std::vector<Enemy> enemys;		// �G�����Ǘ�����C���X�^���X�z��
	std::vector<Fire> fires;		// �����̏����Ǘ�����C���X�^���X�z��
	std::vector<Bomb> bombs;		// ���e�̏����Ǘ�����C���X�^���X�z��
	
public:

	// �C���[�W����уT�E���h�f�[�^��ǂݍ��݁A�e��n���h���Ɋi�[�B�t�H���g�̐ݒ�
	GameControl();

	//********************************
	//		�ėp�I�����֐��Q		**
	//********************************

	// �L�����N�^�[���R�l���񂾕`�������
	void drawPlayers();

	// ���E�J�[�\���̘A�����͎��Ԃɉ����Ė߂�l��������
	int getPushNum();

	// �㉺�J�[�\���̓��͂ɉ����đI�����Ă���s��ύX�B�w�肵���ő�l�𒴂���ƂO�ɖ߂�
	void changeSelectNum(int maxNum);

	// �o�b�N�X�y�[�X�������̓G���^�[�L�[�̓��͂ɉ����Ĉ����̃Q�[�����[�h�ɐ؂�ւ���B
	void changeGameMode(GameMode backMode,GameMode nextMode);

	// ���o���̃g�[�N���C���[�W�ƃt���[����\��
	void drawFlame1(int tokenImageFlame1);

	// �Q�[���̐�����ʂɑJ�ڂ���
	void openGameManual(GameMode nowGameMode);
	
	//********************************
	//		���[�h�ʏ����֐��Q		**
	//********************************

	// �^�C�g����ʂ�����
	void modeTitle();

	// �Q�[���̐�����ʂ�����
	void modeGameManual();

	// �L�����N�^�[�̑I����ʂ�����
	void modeSelectChar();

	// �V�ѕ��I����ʂ�����
	void modeSelectPlay();

	// ��Փx�I����ʂ�����
	void modeSelectLevel();
	
	// �v���C���[���̐ݒ��ʂ�����
	void modeCustomPlayer();

	// �G���̐ݒ��ʂ�����
	void modeCustomEnemy();

	// ���̑����̐ݒ��ʂ�����
	void modeCustomOther();

	// �o�g���J�n�O�̊m�F��ʂ�����
	void modeConfirmation();

	// �ݒ���e�����ƂɃo�g����������
	void modeInitBattle();

	// �o�g�����[�h�̃��C�������֐�
	void modePlayBattle();

	void drawBattle();

	void updateBattle();

	void battleMenu();

	// �Q�[���S�̂𓝊����郁�C���֐��B�����Ń��[�h���Ƃɏ�����U�蕪����
	bool mainControl();

};

