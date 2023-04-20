#include "EnemyCrystalBullet.h"
#include "Player.h"

EnemyCrystalBullet::~EnemyCrystalBullet() {
	delete crystalObj_;
}

void EnemyCrystalBullet::Initialize(int num, Model* crystalModel_) {
	// �_�K�[�t�@���l��
	crystalObj_ = Object3d::Create();
	crystalObj_->SetModel(crystalModel_);

	isLive = true;
	bulletNum = num;
	shotTimer = 300 - num * 50;
}


//�ړ��x�N�g���v�Z
void EnemyCrystalBullet::Vec(Vector3 pos) {
	//�v���C���[�̃��[���h���W�̎擾
	Vector3 playerPosition;
	playerPosition = pos;
	//�G�̃��[���h���W���擾
	Vector3 BulletPosition;
	BulletPosition = GetWorldPosition();
	//�����x�N�g�������߂�
	Vector3 A_BVec = Vector3(
		playerPosition.x - BulletPosition.x,
		playerPosition.y - BulletPosition.y,
		playerPosition.z - BulletPosition.z
	);

	//�x�N�g�����K��
	float length = sqrt(A_BVec.x * A_BVec.x + A_BVec.y * A_BVec.y + A_BVec.z * A_BVec.z);
	A_BVecNolm = Vector3(A_BVec.x / length, A_BVec.y / length, A_BVec.z / length);

	A_BVecNolm *= speed;
}

void EnemyCrystalBullet::CrystalBAttack() {
	shotTimer--;

	if (isLive) {
		if (shotTimer <= 100) {
			crystalObj_->wtf.position += A_BVecNolm;
		}
	}

	if (crystalObj_->wtf.position.z <= -1000|| crystalObj_->wtf.position.z >= 1000) {
		isLive = false;
	}
	if (crystalObj_->wtf.position.x <= -1000 || crystalObj_->wtf.position.x >= 1000) {
		isLive = false;
	}
}

void EnemyCrystalBullet::Update(){
	CrystalBAttack();
	crystalObj_->Update();

}

void EnemyCrystalBullet::Draw(){
	crystalObj_->Draw();

}

Vector3 EnemyCrystalBullet::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ�����
	worldPos.x = crystalObj_->wtf.position.x;
	worldPos.y = crystalObj_->wtf.position.y;
	worldPos.z = crystalObj_->wtf.position.z;

	return worldPos;
}


void EnemyCrystalBullet::OnCollision() {
	isLive = false;

}