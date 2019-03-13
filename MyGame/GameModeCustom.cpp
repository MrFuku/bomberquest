#include "GameControl.h"

void GameControl::modeCustomPlayer(){
	drawFlame1(tokenImagePlayerStatusH1);
	DrawRotaGraph(368, 350, 0.55, 0, msgFlame3, TRUE);

	for (int i = 0; i < 6; i++) {
		DrawRotaGraph(300, 250 + i * 45, 1 + (currentSelectNum == i)*0.05, 0, tokenImagePlayerStatus[i], TRUE);
	}
	DrawRotaGraph(150, 245 + currentSelectNum * 45, 1.2, 0, Fire::getBombImage(initBombType, fps.getCount() / 15 % 2 + 1), TRUE);
	DrawFormatString(420, 240 + 0 * 45, GetColor(0, 0, 139), "%d", initPlayerLife);
	DrawFormatString(420, 240 + 1 * 45, GetColor(0, 0, 139), "%d", (int)(initPlayerSpeed * 10));
	DrawFormatString(420, 240 + 2 * 45, GetColor(0, 0, 139), "%d", initPlayerAttackPower);
	DrawFormatString(420, 240 + 3 * 45, GetColor(0, 0, 139), "%d", initPlayerAttackRange);
	DrawFormatString(420, 240 + 4 * 45, GetColor(0, 0, 139), "%d", initBombType);
	DrawFormatString(420, 240 + 5 * 45, GetColor(0, 0, 139), "%d", initBombMaxNum);

	int x = getPushNum();
	changeSelectNum(6);

	switch (currentSelectNum)
	{
	case 0:
		initPlayerLife += x;
		initPlayerLife = max(1, initPlayerLife);
		initPlayerLife = min(10000, initPlayerLife);
		break;
	case 1:
		if (abs(x) > 0) {
			int tmp = (int)(initPlayerSpeed * 10) + x;
			tmp = max(5, tmp);
			tmp = min(200, tmp);
			initPlayerSpeed = tmp / 10.0;
		}
		break;
	case 2:
		initPlayerAttackPower += x;
		initPlayerAttackPower = max(1, initPlayerAttackPower);
		initPlayerAttackPower = min(10000, initPlayerAttackPower);
		break;
	case 3:
		initPlayerAttackRange += x;
		initPlayerAttackRange = max(1, initPlayerAttackRange);
		initPlayerAttackRange = min(20, initPlayerAttackRange);
		break;
	case 4:
		if (x) x = (x > 0 ? 1 : -1);
		initBombType = (initBombType + x + 3) % 3;
		break;
	case 5:
		initBombMaxNum += x;
		initBombMaxNum = max(1, initBombMaxNum);
		initBombMaxNum = min(50, initBombMaxNum);
		break;
	default:

		break;
	}

	changeGameMode(MODE_SELECT_PLAY, MODE_CUSTOM_ENEMY);
}

void GameControl::modeCustomEnemy(){

	currentSelectNum = (currentSelectNum + 3) % 3;
	drawFlame1(tokenImageSelectEnemyNum);
	DrawRotaGraph(368, 350, 0.55, 0, msgFlame3, TRUE);
	DrawRotaGraph(150, 250 + currentSelectNum * 45, 1.2, 0, Fire::getBombImage(initBombType, fps.getCount() / 15 % 2 + 1), TRUE);
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(280, 250 + i * 45, 1 + (currentSelectNum == i)*0.05, 0, tokenImageEnemyName[i], TRUE);
	}
	DrawFormatString(420, 240 + 0 * 45, GetColor(0, 0, 139), "%d", initEnemyNum_Ghost);
	DrawFormatString(420, 240 + 1 * 45, GetColor(0, 0, 139), "%d", initEnemyNum_Skeleton);
	DrawFormatString(420, 240 + 2 * 45, GetColor(0, 0, 139), "%d", initEnemyNum_Witch);
	DrawRotaGraph(590, 340, 4, 0, player.getImageHandle(0, currentSelectNum, fps.getCount() / 10 % 3), TRUE);

	int x = getPushNum();
	changeSelectNum(3);

	if (x) {
		if (currentSelectNum == 0) {
			initEnemyNum_Ghost += x;
			initEnemyNum_Ghost = max(0, initEnemyNum_Ghost);
			initEnemyNum_Ghost = min(1000, initEnemyNum_Ghost);
		}
		else if (currentSelectNum == 1) {
			initEnemyNum_Skeleton += x;
			initEnemyNum_Skeleton = max(0, initEnemyNum_Skeleton);
			initEnemyNum_Skeleton = min(1000, initEnemyNum_Skeleton);
		}
		else {
			initEnemyNum_Witch += x;
			initEnemyNum_Witch = max(0, initEnemyNum_Witch);
			initEnemyNum_Witch = min(1000, initEnemyNum_Witch);
		}
	}
	if (initEnemyNum_Ghost + initEnemyNum_Skeleton + initEnemyNum_Witch == 0) {
		DrawFormatString(200, 400, GetColor(255, 0, 0), "“G‚Íˆê‘ÌˆÈã‘I‚ñ‚Å‚­‚¾‚³‚¢");
		if (isPushedKey(KEY_INPUT_RETURN)) {
			PlaySoundMem(cancelSound, DX_PLAYTYPE_BACK);
		}
	}
	changeGameMode(MODE_CUSTOM_PLAYER,MODE_CUSTOM_OTHER);
}

void GameControl::modeCustomOther(){

	const char* str[] = { "‚È‚µ","‚©‚È‚è­‚È‚ß","­‚È‚ß","•’Ê","‘½‚ß","‚©‚È‚è‘½‚ß" };
	int blockNum = initBlockNum / 40;
	int itemRate = initItemRate / 10;
	
	DrawRotaGraph(368, 100, 0.55, 0, msgFlame1, TRUE);
	DrawRotaGraph(368, 100, 0.8, 0, tokenImageOtherConfig, TRUE);
	DrawRotaGraph(368, 350, 0.55, 0, msgFlame3, TRUE);
	DrawRotaGraph(280, 250, 1 + (currentSelectNum == 0)*0.05, 0, tokenImageBlockNum, TRUE);
	DrawRotaGraph(280, 250 + 45, 1 + (currentSelectNum == 1)*0.05, 0, tokenImageItemNum, TRUE);
	DrawFormatString(420, 240 + 0 * 45, GetColor(0, 0, 139), "%s", str[blockNum]);
	DrawFormatString(420, 240 + 1 * 45, GetColor(0, 0, 139), "%s", str[itemRate]);
	DrawRotaGraph(150, 250 + currentSelectNum * 45, 1.2, 0, Fire::getBombImage(initBombType, fps.getCount() / 15 % 2 + 1), TRUE);

	changeSelectNum(2);
	int x = getPushNum();

	if (x) {
		if (currentSelectNum == 0) {
			blockNum = blockNum + x;
			blockNum = max(0, blockNum);
			blockNum = min(5, blockNum);
			initBlockNum = blockNum * 40;
		}
		else {
			itemRate = itemRate + x;
			itemRate = max(0, itemRate);
			itemRate = min(5, itemRate);
			initItemRate = itemRate * 10;
		}
	}

	initSelectLevel = 3;
	previousGameMode = MODE_CUSTOM_OTHER;
	changeGameMode(MODE_CUSTOM_ENEMY, MODE_COMFIRMATION);
}





