#include "Fire.h"

int Fire::fireImage[6];
int Fire::bombImage[4][6];
int Fire::fireSound;
int Fire::putBombSound;

// ��������є��e�̉摜�A�T�E���h����荞��
void Fire::initFire() {
	fireSound = LoadSoundMem("Sounds/Field/fireSound.mp3");
	putBombSound = LoadSoundMem("Sounds/Field/poyo.mp3");
	int tmp[60];
	LoadDivGraph("Images/Field/Bomb1.png", 60, 6, 10, 32, 32, tmp);
	for (int i = 0; i < 6; i++) fireImage[i] = tmp[i + 30];
	for (int i = 0; i < 6; i++) bombImage[0][i] = tmp[i];
	for (int i = 0; i < 6; i++) bombImage[1][i] = tmp[i + 6];
	for (int i = 0; i < 6; i++) bombImage[2][i] = tmp[i + 18];
	for (int i = 0; i < 6; i++) bombImage[3][i] = tmp[i + 24];
	bombImage[2][5] = bombImage[3][5] = bombImage[0][5];
	


}

// �C���X�^���X��xy���W��pair�ɂ��ĕԂ�
std::pair<int, int> Fire::getPoint() { return std::make_pair(x, y);}

// Fire�z���Fire��`�悷��
// �����̃C���[�W���Q���d�˂Ĕ��͂����o
void Fire::drawFires(std::vector<Fire>& fires){
	for (Fire &fire : fires) {
		if (fire.time > 30) continue;
		DrawGraph(fire.x * 32, fire.y * 32 + MARGIN_TOP, fireImage[fire.time / 3 % 4], TRUE);
		DrawGraph(fire.x * 32, fire.y * 32 + MARGIN_TOP, fireImage[max(0, 5 - fire.time / 3)], TRUE);
	}
}

// Fire�z���Fire�̏�Ԃ��X�V����
void Fire::firesUpdate(std::vector<Fire>& fires) {
	for (auto itr = fires.begin(); itr != fires.end();) {
		int tmpTime = --(*itr).time;
		if (tmpTime <= 0) {
			itr = fires.erase(itr);
			continue;
		}
		else if (tmpTime <= 30) {				// time���R�O�𒴂���ꍇ�͂܂��������Ă��Ȃ���ԂƂ݂Ȃ�
			if ((*itr).attackByPlayer) {		// �v���C���[�ɂ�锚�����Ń_���[�W�̊i�[�悪�ς��
				(*itr).setDamagePlayer((*itr).getPoint(), (*itr).attack);
			}
			else {
				(*itr).setDamageEnemy((*itr).getPoint(), (*itr).attack, true);
			}		
		}
		itr++;
	}
}

// �z���Fire�C���X�^���X��ǉ�����i�j
void Fire::setFire(int _x, int _y, int _range, int _attack, int bombType, std::vector<Fire> & fires){
	PlaySoundMem(fireSound, DX_PLAYTYPE_BACK);

	if (bombType != 2) {		// 
		for (int i = 0; i < 4; i++) {
			for (int dist = 0; dist <= _range; dist++) {
				Fire fire;
				fire.x = _x + dx[i] * dist;
				fire.y = _y + dy[i] * dist;
				fire.attack = _attack;
				fire.time = 30 + dist;
				fire.attackByPlayer = 1;
				if (fire.isWall(fire.getPoint())) break;
				fires.push_back(fire);
				if (bombType != 1 && fire.isBlock(fire.getPoint())) break;;
			}
		}
	}
	else {		// �L�͈͌^���e�ɂ�锚���B
		for (int yy = max(1, _y - _range); yy < min(FIELD_Y - 1, _y + _range + 1); yy++) {
			for (int xx = max(1, _x - _range); xx < min(FIELD_X - 1, _x + _range + 1); xx++) {
				Fire fire;
				int dist = abs(_x - xx) + abs(_y - yy);
				if (dist > _range || fire.isWall({xx,yy})) continue;
				fire.x = xx;
				fire.y = yy;
				fire.attack = _attack;
				fire.time = 30 + dist * 2;
				fire.attackByPlayer = 1;
				fires.push_back(fire);
			}
		}
	}
}

void Fire::setFireWitch(int _x, int _y, int _range, int _muki, int _attack, std::vector<Fire>& fires) {
	PlaySoundMem(fireSound, DX_PLAYTYPE_BACK);
	for (int dist = 0; dist <= _range; dist++) {
		Fire fire;
		fire.x = _x + dx[_muki] * dist;
		fire.y = _y + dy[_muki] * dist;
		fire.attack = _attack;
		fire.time = 30 + dist;
		fire.attackByPlayer = 0;
		if (fire.isWall(fire.getPoint())) break;
		fires.push_back(fire);
		if ( fire.isBlock(fire.getPoint())) break;;
	}
}

// ���e�̃C���[�W�n���h����Ԃ�
int Fire::getBombImage(int type, int num){ return bombImage[type][num]; }
