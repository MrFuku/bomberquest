#include "Character.h"

int Character::playerImage[3][12];
int Character::enemyImage[3][12];
int Character::questionImage[6];
int Character::magicSound;
int Character::magicEfect[3];


// �L�����N�^�[����ъe��C���[�W�E�T�E���h����荞��

void Character::inputImage(){

	LoadDivGraph("Images/Character/hero.png", 12, 3, 4, 32, 32, playerImage[0]);
	LoadDivGraph("Images/Character/elf.png", 12, 3, 4, 32, 32, playerImage[1]);
	LoadDivGraph("Images/Character/cat.png", 12, 3, 4, 32, 32, playerImage[2]);
	LoadDivGraph("Images/Character/mook.png", 12, 3, 4, 32, 32, enemyImage[0]);
	LoadDivGraph("Images/Character/skeleton.png", 12, 3, 4, 32, 32, enemyImage[1]);
	LoadDivGraph("Images/Character/witch.png", 12, 3, 4, 32, 32, enemyImage[2]);
	LoadDivGraph("Images/Character/emotion.png", 6, 6, 1, 32, 32, questionImage);
	magicSound = LoadSoundMem("Sounds/Field/powerup01.mp3");
	int tmp[32];
	LoadDivGraph("Images/Character/magicEfect.png", 24, 6, 4, 48, 48, tmp);
	for (int i = 0; i < 3; i++) magicEfect[i] = tmp[21 + i];
}


// �_���[�W�����B�_���[�W���󂯂Ă���Ԃ͐V���ȃ_���[�W���󂯂Ȃ�
// ���C�t���O�A���_���[�W�^�C�����O�Ń����[�u�t���O�𗧂Ă�
// �G���m�̍U���͖���

void Character::damageUpdate() {

	if (damageTime > 0) {
		damageTime--;
		return;
	}
	if (life <= 0) {
		removeFlag = 1;
		return;
	}
	int damage = getDamagePlayer(getPos());
	if (characterType== PLAYER) damage = max(damage, getDamageEnemy(getPos()));
	if (damage > 0) {
		life = max(0, life - damage);
		damageTime = 180;
		alive = (life > 0);
	}
}


// �����[�u�t���O�������Ă��邩����

bool Character::isRemove() { return removeFlag; }


// �L�����N�^�[��`��B������ʒu�ɂ���ăC���[�W�n���h�����g��������
// �_���[�W���󂯂Ă���Œ�����ю��S���͕\����ω�������

void Character::draw() {
	int imageId;
	int _x = (int)x;
	int _y = (int)y;
	
	imageId = (_x % 32 + _y % 32) / 12;
	if (muki == 1) imageId += 3;
	if (muki == 3) imageId += 6;
	if (muki == 0) imageId += 9;
	if (alive == 0) imageId = damageTime / 3 % 12;
	if (damageTime > 0 && damageTime / 3 % 2 || (alive + damageTime == 0)) return;
	DrawGraph(_x, _y + MARGIN_TOP, image[imageId], TRUE);
}


// �����t���O�y�ѐ����t���O�������Ă����ꍇ�����Ă�������ɐi��
// �ړ��̑O��łR�Q�̔{�����܂����Ƃ��́A�R�Q�̔{���̈ʒu�Ŏ~�܂�悤�ɏ���

void Character::move() {

	if (walkingFlag == 1 && alive == 1) {        //�����t���O�������Ă�����
		if ((int)x % 32 != 0 || (int)y % 32 != 0) {
			int _x = x + dx[muki] * speed;
			int _y = y + dy[muki] * speed;
			if (muki == 0) {
				if (_y / 32 < (int)y / 32) {
					y = _y + 32 - (_y + 32) % 32;
					return;
				}
			}
			else if (muki == 1) {
				if (_x / 32 < (int)x / 32) {
					x = _x + 32 - (_x + 32) % 32;
					return;
				}
			}
			else if (muki == 2) {
				if (_y / 32 > (int)y / 32) {
					y = _y - (_y + 32) % 32;
					return;
				}
			}
			else {
				if (_x / 32 > (int)x / 32) {
					x = _x - (_x + 32) % 32;
					return;
				}
			}
		}
		x += dx[muki] * speed;
		y += dy[muki] * speed;
	}
}


// �L�����N�^�[�������Ă�������ɐi�߂邩����
// �R�Q�̔{���̈ʒu�ł̎g�p�̂ݑz��

bool Character::isAbleToGo() {

	if (!isTouch({ (int)x / 32 + dx[muki], (int)y / 32 + dy[muki] })) {
		return true;
	}
	else {
		return (characterType == GHOST && !isWall({ (int)x / 32 + dx[muki], (int)y / 32 + dy[muki] }));
	}
}


// �L�����N�^�[�̌��݈ʒu�y�ёO���P�}�X���[�����i�O�ǂ̂��������j�ł��邩���肷��
bool Character::isEdge() {
	int _x = (int)x / 32;
	int _y = (int)y / 32;
	int nx = _x + dx[muki];
	int ny = _y + dy[muki];
	return (_x == 1 || _x == FIELD_X - 2 || _y == 1 || _y == FIELD_Y - 2) && (nx == 1 || nx == FIELD_X - 2 || ny == 1 || ny == FIELD_Y - 2);
}


// �L�����N�^�[�̂���}�X���y�A�ɂ��ĕԂ��B�ړ����ł���΂��߂����̃}�X�̒l�Ƃ���
std::pair<int, int> Character::getPos() {
	int _x = (int)x;
	int _y = (int)y;
	if (_x % 32 > 15) _x += 32;
	if (_y % 32 > 15) _y += 32;
	return { _x / 32,_y / 32 };
}


// �L�����N�^�[�̃C���[�W�n���h����Ԃ�
int Character::getImageHandle(int isPlayer, int type, int num){
	if (isPlayer) {
		return playerImage[type][num];
	}
	else {
		return enemyImage[type][num];
	}
}
