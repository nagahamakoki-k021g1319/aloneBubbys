#include "EnemyShortRenge.h"

EnemyShortRenge::~EnemyShortRenge()
{
}

void EnemyShortRenge::Initialize(Model* model_)
{
	obj_ = Object3d::Create();
	obj_->SetModel(model_);

	attackRenge = Object3d::Create();
	attackRenge->SetModel(model_);
	attackRenge->wtf.scale = { 2.0f,2.0f,2.0f };

	obj_->wtf.position = { 0.0f,0.0f,10.0f };
}

void EnemyShortRenge::ShortAttack()
{
	attackAccumulate--;
	if (attackAccumulate <= 0) {
		isAttackTime--;
		OnCollision();
		//if (isAttackTime <= 0) {
		//	isAttack = false;
		//	attackAccumulate = 60;
		//	isAttackTime = 10;
		//}
	}
}


void EnemyShortRenge::Update(Vector3 PlayerPos, Object3d* enemy)
{
	obj_ = enemy;
	playerPos = PlayerPos;
	
	if (isAttack == false) {
		PlayerVec();
		if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 1.0f, 1.0f)) {
			isAttackTime = 3;
			isAttack = true;
		}
		else if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 1.0f, 1.0f) == false) {
			obj_->wtf.position += playerLen;
		}
	}
	if (isAttack) {
		ShortAttack();
	}
	attackRenge->wtf.position = obj_->wtf.position + (playerLen * 2);
	obj_->Update();
	attackRenge->Update();
	enemy = obj_;
}

void EnemyShortRenge::Draw()
{
	/*obj_->Draw();*/
	if (isAttack) {
		if (attackAccumulate <= 0) {
			attackRenge->Draw();
		}
	}

}

void EnemyShortRenge::OnCollision()
{
	if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 2.0f, 2.0f)) {
		hitAttck = true;
	}
	else if (coll->CircleCollision(Vector3{ obj_->wtf.position.x + (playerLen.x * 2), obj_->wtf.position.y + playerLen.y + 2.0f, obj_->wtf.position.z + (playerLen.z * 2) }, playerPos, 2.0f, 2.0f)) {
		hitAttck = true;
	}
	hitAttck = false;
}

void EnemyShortRenge::PlayerVec()
{



	playerLen = playerPos - obj_->wtf.position;
	playerLen.nomalize();
	playerLen *= enemySpeed;

}

void EnemyShortRenge::ResetAttack()
{
	isAttack = false;
	attackAccumulate = 60;
	isAttackTime = 10;
}

bool EnemyShortRenge::GetCollision()
{
	return hitAttck;
}
