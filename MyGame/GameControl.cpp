#include "GameControl.h"

// �C���[�W����уT�E���h�f�[�^��ǂݍ��݁A�e��n���h���Ɋi�[�B�t�H���g�̐ݒ�

GameControl::GameControl(){

	// �C���[�W�̓ǂݍ���
	
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


	// �T�E���h�̓ǂݍ��݁BBGM�̍Đ��J�n

	titleSound = LoadSoundMem("Sounds/Menu/title.mp3");
	cursorSound = LoadSoundMem("Sounds/Menu/cursor.mp3");
	decisionSound = LoadSoundMem("Sounds/Menu/decision.mp3");
	cancelSound = LoadSoundMem("Sounds/Menu/cancel.mp3");
	PlaySoundMem(titleSound, DX_PLAYTYPE_LOOP);

	// �t�H���g�̐ݒ�

	ChangeFont("�l�r �S�V�b�N");
}


//********************************
//		�ėp�I�����֐��Q		**
//********************************


// �L�����N�^�[���R�l���񂾕`�������

void GameControl::drawPlayers() {

	DrawRotaGraph(150, 440, 5.5, 0, player.getImageHandle(1, 0, fps.getCount() / 10 % 3), TRUE);
	DrawRotaGraph(370, 440, 5.5, 0, player.getImageHandle(1, 1, fps.getCount() / 10 % 3), TRUE);
	DrawRotaGraph(590, 430, 5.65, 0, player.getImageHandle(1, 2, fps.getCount() / 10 % 3), TRUE);
}


// ���E�J�[�\���̘A�����͎��Ԃɉ����Ė߂�l��������

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


// �㉺�J�[�\���̓��͂ɉ����đI�����Ă���s��ύX�B�w�肵���ő�l�𒴂���ƂO�ɖ߂�

void GameControl::changeSelectNum(int maxNum){

	bool soundFlag = false;
	if (isPushedKey(KEY_INPUT_UP)) currentSelectNum--, soundFlag = true;
	if (isPushedKey(KEY_INPUT_DOWN)) currentSelectNum++, soundFlag = true;;
	currentSelectNum = (currentSelectNum + maxNum) % maxNum;
	if (soundFlag) {
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	}
}


// �o�b�N�X�y�[�X�������̓G���^�[�L�[�̓��͂ɉ����Ĉ����̃Q�[�����[�h�ɐ؂�ւ���B

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


// ���o���̃g�[�N���C���[�W�ƃt���[����\��

void GameControl::drawFlame1(int tokenImageFlame1){

	DrawRotaGraph(368, 100, 0.55, 0, msgFlame1, TRUE);
	DrawRotaGraph(368, 100, 0.65, 0, tokenImageFlame1, TRUE);
}


// �Q�[���̐�����ʂɑJ�ڂ���
// ������ʂ���߂�Ƃ��̃��[�h�������ɂ���

void GameControl::openGameManual(GameMode nowGameMode){

	previousGameMode = nowGameMode;
	currentGameMode = MODE_GAME_MANUAL;
	PlaySoundMem(decisionSound, DX_PLAYTYPE_BACK);
}


// �^�C�g����ʂł̏���

void GameControl::modeTitle(){

	DrawFormatString(230, 235 - fps.getCount() / 30 % 2 * 3, GetColor(255, 255, 255), "Enter�L�[�������ăQ�[�����͂��߂�");
	DrawFormatString(260, 265 - fps.getCount() / 30 % 2 * 3, GetColor(255, 255, 255), "Esc�L�[�ŃQ�[������߂�");
	DrawFormatString(233, 295 - fps.getCount() / 30 % 2 * 3, GetColor(255, 255, 255), "�X�y�[�X�L�[�ŃQ�[���̐������݂�");
	DrawRotaGraph(565, 140, 1.3, 0, tokenImageTitle, TRUE);
	DrawRotaGraph(675, 130, 2.7, 0, Fire::getBombImage(0, fps.getCount() / 15 % 2 + 1), TRUE);
	drawPlayers();
	changeGameMode(MODE_TITLE, MODE_SELECT_CHAR);
	if (isPushedKey(KEY_INPUT_SPACE)) {
		openGameManual(MODE_TITLE);
	}
}


// �Q�[���̐�����ʂ�����
// �S�T�y�[�W�������ɓ����ɕ`�悵�A�ʒu���X���C�h�����邱�ƂŃy�[�W��؂�ւ���

int modeGameManualNowPage = 0;
int modeGameManualNowPageAxis = 0;
void GameControl::modeGameManual() {

	// ��ʑJ�ڂ̓X���C�h�ŉ��o����
	if (modeGameManualNowPage * 736 > modeGameManualNowPageAxis) modeGameManualNowPageAxis+=46;
	if (modeGameManualNowPage * 736 < modeGameManualNowPageAxis) modeGameManualNowPageAxis-=46;

	// ���o�������̕\��
	int imageHandle[] = { tokenImageMenuOperation ,tokenImageBattleOperation,tokenImageBattleRule, tokenImageItemDescription,tokenImageEnemyDescription };
	for (int i = 0; i < 5; i++) {
		DrawRotaGraph(368 + 736 * i - modeGameManualNowPageAxis, 100, 0.55, 0, msgFlame1, TRUE);
		DrawRotaGraph(368 + 736 * i - modeGameManualNowPageAxis, 100, 0.65, 0, imageHandle[i], TRUE);
		DrawRotaGraph(368 + 736 * i - modeGameManualNowPageAxis, 350, 0.55, 0, msgFlame3, TRUE);
	}
	
	// �P�y�[�W�ځ@���j���[�̑���
	DrawRotaGraph(270 + 736 * 0 - modeGameManualNowPageAxis, 270 + 80 * 0, 0.55, 0, tokenImageCursor, TRUE);
	DrawRotaGraph(270 + 736 * 0 - modeGameManualNowPageAxis, 270 + 80 * 1, 0.55, 0, tokenImageEnter, TRUE);
	DrawRotaGraph(270 + 736 * 0 - modeGameManualNowPageAxis, 270 + 80 * 2, 0.55, 0, tokenImageBackSpace, TRUE);
	DrawFormatString(400 + 736 * 0 - modeGameManualNowPageAxis, 257 + 80 * 0, GetColor(50, 50, 50), "�J�[�\���̈ړ��E���l�̕ύX");
	DrawFormatString(400 + 736 * 0 - modeGameManualNowPageAxis, 257 + 80 * 1, GetColor(50, 50, 50), "����");
	DrawFormatString(400 + 736 * 0 - modeGameManualNowPageAxis, 257 + 80 * 2, GetColor(50, 50, 50), "�߂�E�L�����Z��");

	// �Q�y�[�W�ځ@�킢�̑���
	DrawRotaGraph(270 + 736 * 1 - modeGameManualNowPageAxis, 270 + 80 * 0, 0.55, 0, tokenImageCursor, TRUE);
	DrawRotaGraph(270 + 736 * 1 - modeGameManualNowPageAxis, 270 + 80 * 1, 0.55, 0, tokenImageSpace, TRUE);
	DrawRotaGraph(270 + 736 * 1 - modeGameManualNowPageAxis, 270 + 80 * 2, 0.55, 0, tokenImageShift, TRUE);
	DrawFormatString(400 + 736 * 1 - modeGameManualNowPageAxis, 257 + 80 * 0, GetColor(50, 50, 50), "�v���C���[�̈ړ�");
	DrawFormatString(400 + 736 * 1 - modeGameManualNowPageAxis, 257 + 80 * 1, GetColor(50, 50, 50), "���e������");
	DrawFormatString(400 + 736 * 1 - modeGameManualNowPageAxis, 257 + 80 * 2, GetColor(50, 50, 50), "���j���[��ʂ̕\��");

	// �R�y�[�W�ځ@�킢�̐���
	DrawRotaGraph(375 + 736 * 2 - modeGameManualNowPageAxis, 180 + 80 * 2, 0.65, 0, tokenImageBattleRuleDescription, TRUE);

	// �S�y�[�W�ځ@�A�C�e���̐���
	for (int i = 0; i < 4; i++) {
		DrawRotaGraph(100 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * i, 1.5, 0, field.getItemImage(i), TRUE);
		DrawRotaGraph(410 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * i, 1.5, 0, field.getItemImage(i+4), TRUE);
	}
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 232 + 80 * 0, GetColor(50, 50, 50), "�U���͂��A�b�v���܂�");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 232 + 80 * 1, GetColor(50, 50, 50), "���e�������鐔�������܂�");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 220 + 80 * 2, GetColor(50, 50, 50), "�������u���b�N���ђʂ���");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * 2, GetColor(50, 50, 50), "�悤�ɂȂ�܂�");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 220 + 80 * 3, GetColor(50, 50, 50), "�������ƂĂ��L���͈͂�");
	DrawFormatString(150 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * 3, GetColor(50, 50, 50), "�L����悤�ɂȂ�܂�");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 220 + 80 * 0, GetColor(50, 50, 50), "�̗͂������܂�");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * 0, GetColor(50, 50, 50), "���e�̔������Ԃ����ɖ߂�܂�");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 220 + 80 * 1, GetColor(50, 50, 50), "���e�̔������Ԃ������_����");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 240 + 80 * 1, GetColor(50, 50, 50), "�Ȃ�܂�");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 232 + 80 * 2, GetColor(50, 50, 50), "�ړ����x��������܂�");
	DrawFormatString(460 + 736 * 3 - modeGameManualNowPageAxis, 232 + 80 * 3, GetColor(50, 50, 50), "�����͈̔͂��L���Ȃ�܂�");

	// �T�y�[�W�ځ@�G�̐���
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(125 + 736 * 4 - modeGameManualNowPageAxis, 260 + 90 * i, 1.5, 0, player.getImageHandle(0, i, fps.getCount() / 10 % 3), TRUE);
		DrawRotaGraph(270 + 736 * 4 - modeGameManualNowPageAxis, 260 + 90 * i, 1, 0, tokenImageEnemyName[i], TRUE);
	}
	DrawFormatString(340 + 736 * 4 - modeGameManualNowPageAxis, 255 + 90 * 0, GetColor(50, 50, 50), "�u���b�N�┚�e�����蔲���Ĉړ����܂�");
	DrawFormatString(340 + 736 * 4 - modeGameManualNowPageAxis, 255 + 90 * 1, GetColor(50, 50, 50), "�v���C���[��������ƒǂ������Ă��܂�");
	DrawFormatString(340 + 736 * 4 - modeGameManualNowPageAxis, 240 + 90 * 2, GetColor(50, 50, 50), "���̖��@���g���āA�v���C���[��");
	DrawFormatString(340 + 736 * 4 - modeGameManualNowPageAxis, 260 + 90 * 2, GetColor(50, 50, 50), "�u���b�N���U�����܂�");


	// �y�[�W�J�ڂ��\�ł��邱�Ƃ��������̕`��
	if (modeGameManualNowPage > 0) {
		DrawRotaGraph(50, 340, 1.2, 3.141592654*0.5, cursorImage[fps.getCount() / 20 % 3], TRUE);
	}
	if (modeGameManualNowPage < 4) {
		DrawRotaGraph(686, 340, 1.2, 3.141592654*1.5, cursorImage[fps.getCount() / 20 % 3], TRUE);
	}
	
	// ���E�J�[�\���̓��͂ɉ����ăy�[�W��؂�ւ�
	if (isPushedKey(KEY_INPUT_LEFT)) {
		modeGameManualNowPage = max(0, modeGameManualNowPage - 1);
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	}
	if (isPushedKey(KEY_INPUT_RIGHT)) {
		modeGameManualNowPage = min(4, modeGameManualNowPage + 1);
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	}

	// �Q�[���������I�����đJ�ڌ��̃��[�h�ɖ߂�
	if (isPushedKey(KEY_INPUT_BACK)) {
		currentGameMode = previousGameMode;
		modeGameManualNowPage = 0;
		modeGameManualNowPageAxis = 0;
		PlaySoundMem(cancelSound, DX_PLAYTYPE_BACK);
	}
}


// �L�����N�^�[�̑I����ʂ�����

void GameControl::modeSelectChar(){

	drawFlame1(tokenImageSelectChar);
	drawPlayers();
	DrawRotaGraph(210 + initPlayerType * 220, 310 - fps.getCount() / 30 % 2 * 3, 0.25, 0, fukidashiImage, TRUE);
	DrawRotaGraph(210 + initPlayerType * 220, 300 - fps.getCount() / 30 % 2 * 3, 0.6, 0, tokenImageCharName[initPlayerType], TRUE);
	
	if (isPushedKey(KEY_INPUT_LEFT)) initPlayerType = (initPlayerType + 2) % 3, PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	if (isPushedKey(KEY_INPUT_RIGHT)) initPlayerType = (initPlayerType + 1) % 3, PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
	changeGameMode(MODE_TITLE, MODE_SELECT_PLAY);
}


// �V�ѕ��I����ʂ�����

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


// ��Փx�I����ʂ�����

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


// �o�g���J�n�O�̊m�F��ʂ�����

void GameControl::modeConfirmation() {

	changeSelectNum(2);
	DrawRotaGraph(360, 350, 0.6 + 0.05, 0, msgFlame2, TRUE);
	DrawFormatString(270, 270, GetColor(180, 0, 0), "�ݒ肵�����e�ŃQ�[����");
	DrawFormatString(270, 290, GetColor(180, 0, 0), "�͂��߂Ă���낵���ł����H");
	DrawFormatString(340, 340, GetColor(0 + (currentSelectNum != 0) * 180, 0 + (currentSelectNum != 0) * 180, 0 + (currentSelectNum != 0) * 180), "�͂�");
	DrawFormatString(335, 380, GetColor(0 + (currentSelectNum != 1) * 180, 0 + (currentSelectNum != 1) * 180, 0 + (currentSelectNum != 1) * 180), "������");

	if (currentSelectNum == 0) {
		changeGameMode(previousGameMode, MODE_INIT_BATTLE);
	}
	else {
		changeGameMode(previousGameMode, previousGameMode);
	}
}


// �ݒ���e�����ƂɃo�g����������

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


// �o�g�����[�h�̃��C�������֐�

int modeBattleMenuFlag = 0;
void GameControl::modePlayBattle() {

	// �o�g���̕`��t�F�[�Y
	drawBattle();
	
	if (modeBattleMenuFlag == 1) {	
		// �o�g�����j���[�t�F�[�Y
		battleMenu();
	}
	else {
		// �o�g���󋵂̍X�V�t�F�[�Y
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
			DrawFormatString(310, 340, GetColor(180, 0, 0), "�����܂���");
		}
		else {
			DrawFormatString(310, 340, GetColor(180, 0, 0), "�����܂���");
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
		DrawFormatString(300, 300, GetColor(0 + (currentSelectNum != 0) * 180, 0 + (currentSelectNum != 0) * 180, 0 + (currentSelectNum != 0) * 180), "�Q�[�����Â���");
		DrawFormatString(300, 350, GetColor(0 + (currentSelectNum != 1) * 180, 0 + (currentSelectNum != 1) * 180, 0 + (currentSelectNum != 1) * 180), "�Q�[���̐������݂�");
		DrawFormatString(300, 400, GetColor(0 + (currentSelectNum != 2) * 180, 0 + (currentSelectNum != 2) * 180, 0 + (currentSelectNum != 2) * 180), "�Q�[������߂�");
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
		DrawFormatString(270, 270, GetColor(180, 0, 0), "�{���ɃQ�[������߂܂����H");
		DrawFormatString(330, 330, GetColor(0 + (currentSelectNum != 3) * 180, 0 + (currentSelectNum != 3) * 180, 0 + (currentSelectNum != 3) * 180), "������");
		DrawFormatString(340, 380, GetColor(0 + (currentSelectNum != 4) * 180, 0 + (currentSelectNum != 4) * 180, 0 + (currentSelectNum != 4) * 180), "�͂�");
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


// �Q�[�������̃��C���R���g���[���֐�

bool GameControl::mainControl(){
	
	field.inputImage();
	player.inputImage();	
	Fire::initFire();

	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && UpdateKey() == 0) {
		
		// �Q�[�����[�h�ɉ����ď����𕪊�
		switch (currentGameMode)
		{
		case MODE_TITLE:			// �^�C�g����ʂ̏���
			modeTitle();
			break;

		case MODE_GAME_MANUAL:		// �Q�[���������[�h
			modeGameManual();
			break;

		case MODE_SELECT_CHAR:		// �L�����N�^�[�I����ʗp���[�h
			modeSelectChar();
			break;

		case MODE_SELECT_PLAY:		// �V�ѕ��I����ʗp���[�h
			modeSelectPlay();
			break;

		case MODE_SELECT_LEVEL:		// ��Փx�I����ʗp���[�h
			modeSelectLevel();
			break;

		case MODE_CUSTOM_PLAYER:	// �v���C���[���̐ݒ胂�[�h
			modeCustomPlayer();
			break;

		case MODE_CUSTOM_ENEMY:		// �G���̐ݒ胂�[�h
			modeCustomEnemy();
			break;

		case MODE_CUSTOM_OTHER:		// ���̑����̐ݒ胂�[�h
			modeCustomOther();
			break;

		case MODE_COMFIRMATION:		// ���̑����̐ݒ胂�[�h
			modeConfirmation();
			break;

		case MODE_INIT_BATTLE:		// �o�g���̏��������[�h
			modeInitBattle();
			break;

		case MODE_PLAY_BATTLE:		// �o�g�������p���[�h
			modePlayBattle();
			break;

		case MODE_EXIT:				// �Q�[���̏I�����[�h
			return true;
			break;

		default:
			return true;
			break;
		}

		fps.Control();	// FPS�𒲐�

		if (isPushedKey(KEY_INPUT_ESCAPE)) {
			currentGameMode = MODE_EXIT;
		}
	}
	return true;
}