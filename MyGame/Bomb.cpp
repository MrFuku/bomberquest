#include "Bomb.h"

// Bomb�z���Bomb�C���X�^���X��`�悷��
// �����܂ł̎c�莞�Ԃɂ���ăC���[�W�n���h�����g��������
void Bomb::drawBombs(std::vector<Bomb>& bombs) {

	for (Bomb &bomb : bombs) {
		int _x = bomb.x * 32;
		int _y = bomb.y * 32 + MARGIN_TOP;
		int imageId = bomb.time / 20 % 2;
		if (bomb.time <= 200) imageId++;
		if (bomb.time <= 100) imageId += 2;
		if (bomb.time < 5) imageId = 5;
		if (bomb.randomFlag) imageId = 0;
		DrawGraph(_x , _y , bombImage[bomb.bombType][imageId], TRUE);
	}
}

// Bomb�z���Bomb�C���X�^���X�̏�Ԃ��X�V����
void Bomb::bombsUpdate(std::vector<Bomb>& bombs, std::vector<Fire>& fires) {

	for (auto itr = bombs.begin(); itr != bombs.end();) {

		if ((*itr).isIgnition((*itr).getPoint())) {		// ���e�̂���ʒu�Ɉ��΃t���O�������Ă����瑦������
			(*itr).time = 0;
		}
		
		if ((*itr).randomFlag) {	// �����_���t���O�������Ă���Έ��m���Ńt���O����菜�����B����܂ł̓J�E���g���Ȃ�
			if (GetRand(350) == 0) (*itr).randomFlag = 0;
		}
		else {
			(*itr).time--;
		}
		if ((*itr).time <= 0) {		// �c�莞�ԂO�ŐV����Fire�C���X�^���X�𐶐�����
			(*itr).removeTouch((*itr).getPoint());
			Fire::setFire((*itr).x, (*itr).y, (*itr).range, (*itr).attack, (*itr).bombType, fires);
			itr = bombs.erase(itr);
			continue;
		}
		itr++;
	}
}

// Bomb�z��ɐV����Bomb�C���X�^���X���i�[����
void Bomb::insertBomb(int _x, int _y, int type, int _range, int _attack, bool random, std::vector<Bomb> &bombs){

	Bomb bomb;
	bomb.x = _x;
	bomb.y = _y;
	bomb.setTouch({ _x, _y });
	bomb.bombType = type;
	bomb.range = _range;
	bomb.attack = _attack;
	bomb.time = (random ? 100 : 200);
	bomb.randomFlag = random;
	bombs.push_back(bomb);
	PlaySoundMem(putBombSound, DX_PLAYTYPE_BACK);
}
