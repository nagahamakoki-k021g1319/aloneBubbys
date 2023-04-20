#include "EnemyBullet.h"

EnemyBullet::~EnemyBullet() {
	delete obj_;
}


void EnemyBullet::Initialize(int timer, Model* model_){
	// �_�K�[�t�@���l��
	obj_ = Object3d::Create();
	obj_->SetModel(model_);

	daggerTimer = timer;
	isLive = true;
	isPop = false;
	shotTimer = 120;

}

void EnemyBullet::DaggerFAttack(){
	//�\���܂�
	daggerTimer--;
	if (daggerTimer < 0) {
		isPop = true;
	}


	shotTimer--;

	if (isLive) {
		if (shotTimer <= 0) {
			obj_->wtf.position.z -= 0.5;
		}
	}
	if (obj_->wtf.position.z <= -1000) {
		isLive = false;
	}
}

void EnemyBullet::Update(){
	DaggerFAttack();
	obj_->Update();
	
}

void EnemyBullet::Draw(){
	if (isPop) {
		obj_->Draw();
	}
}


void EnemyBullet::OnCollision() {
	isLive = false;

}