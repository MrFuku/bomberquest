#include "Player.h"

void Player::initPlayer(const int & initType, const int & initLife, const double & initSpeed, const int & initAttack, int & initBombType, int & initBombRange, int & initBombMaxNum){
	for (int i = 0; i < 12; i++) {
		image[i] = playerImage[initType][i];
	}
	characterType = PLAYER;
	x = 32;
	y = 32;
	muki = 2;
	life = initLife;
	alive = 1;
	removeFlag = 0;
	speed = initSpeed;
	attack = initAttack;
	bombType = initBombType;
	bombRange = initBombRange;
	bombMaxNum = initBombMaxNum;
	bombRandom = 0;
	pickUpItemSound = LoadSoundMem("Sounds/Menu/heal02.mp3");
}

// Bomb�z��ɐV����Bomb�C���X�^���X��ǉ�����
void Player::setBomb(std::vector<Bomb>& bombs){
	if (bombs.size() >= bombMaxNum || !IsRepeatedKey(KEY_INPUT_SPACE) || alive == 0) return;
	int _x = plyPos.first;
	int _y = plyPos.second;
	if (isTouch({ _x, _y })) return;
	Bomb::insertBomb( _x, _y, bombType, bombRange, attack, bombRandom, bombs);
}

// �L�[���͂ɉ����ĕ����t���O�ƌ����t���O��؂�ւ���
bool Player::walkingFlagUpdate() {
	int _x = (int)x;
	int _y = (int)y;
	
	if (_x % 32 == 0 && _y % 32 == 0) {         //���W��32�Ŋ���؂ꂽ����͉\
		walkingFlag = 1;         //�����t���O�𗧂Ă�B
		if (IsRepeatedKey(KEY_INPUT_UP))  //��{�^���������ꂽ��
			muki = 0;         //������t���O�𗧂Ă�
		else if (IsRepeatedKey(KEY_INPUT_LEFT))  //���{�^���������ꂽ��
			muki = 1;         //�������t���O�𗧂Ă�
		else if (IsRepeatedKey(KEY_INPUT_DOWN))  //���{�^���������ꂽ��
			muki = 2;         //�������t���O�𗧂Ă�
		else if (IsRepeatedKey(KEY_INPUT_RIGHT))  //�E�{�^���������ꂽ��
			muki = 3;         //�E�����t���O�𗧂Ă�
		else                                    //���̃{�^����������ĂȂ�������
			walkingFlag = 0; //�����Ȃ��t���O�𗧂Ă�
		if (walkingFlag && !isAbleToGo()) {
			walkingFlag = 0;
		}
		return walkingFlag;
	}
	return 0;
}

void Player::pickUpItem(){
	int itemNum = getItem(plyPos);
	if (itemNum != -1) {
		if (itemNum == 0) {			// �U���̓A�b�v���ʁB
			attack = min(attack + 10, 10000);
		}
		else if (itemNum == 1) {	// �ݒu���e�������B
			bombMaxNum = min(bombMaxNum + 1, 50);
		}
		else if (itemNum == 2) {	// ���e�^�C�v�P�ɕύX�B�ђʌ^
			bombType = 1;
		}
		else if (itemNum == 3) {	// ���e�^�C�v�Q�ɕύX�B�L�͈͌^
			bombType = 2;
		}
		else if (itemNum == 4) {	// �̗͑�������є������ԃ����_����ԉ���
			life += 100;
			bombRandom = 0;
		}
		else if (itemNum == 5) {	// �������ԃ����_����ԉ�
			bombRandom = 1;
		}
		else if (itemNum == 6) {	// �ړ����x�㏸
			speed = min(speed + 0.5, 20);
		}
		else if (itemNum == 7) {	// �����͈͂̑���
			bombRange = min(bombRange + 1, 20);
		}

		PlaySoundMem(pickUpItemSound, DX_PLAYTYPE_BACK);
		removeItem(plyPos);
	}
}

// �v���C���[�����X�V����
void Player::playerUpdate(std::vector<Bomb> &bombs) {

	setBomb(bombs);
	walkingFlagUpdate();
	move();
	pickUpItem();
	damageUpdate();
	plyPos = getPos();
}

void Player::drowStatus(){

	DrawFormatString(10, 10, GetColor(255, 255, 255), "�g�o�@ %d", life);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "�U���� %d", attack);
	DrawFormatString(160, 10, GetColor(255, 255, 255), "�ő唚�e�� %d", bombMaxNum);
	DrawFormatString(160, 40, GetColor(255, 255, 255), "�����͈�   %d", bombRange);
	if (bombRandom) {
		DrawFormatString(310, 10, GetColor(255, 255, 255), "�������ԃ����_�����");
	}
}
