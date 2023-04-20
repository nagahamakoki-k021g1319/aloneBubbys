#pragma once
#include "Object3d.h"
#include "Collision.h"

class EnemyShortRenge {
public:
	~EnemyShortRenge();

	///< summary>
	///������
	///</summary>
	void Initialize(Model* model_);

	///< summary>
	///�X�V
	///</summary>
	void ShortAttack();

	///< summary>
	///�X�V
	///</summary>
	void Update(Vector3 playerPos,Object3d* enemy);

	///< summary>
	///�`��
	///</summary>
	void Draw();

	void OnCollision();

	void PlayerVec();

	void ResetAttack();

	bool GetCollision();

private:
	Collision* coll = nullptr;
	Object3d* obj_ = nullptr;

	Object3d* attackRenge = nullptr;
	
	Vector3 playerLen;
	Vector3 playerPos;

	float enemySpeed = 1.5f;

	bool attackHit = false;
	bool isAttack = false;
	int isAttackTime = 10;
	int attackAccumulate = 20;
	bool hitAttck = false;
public:
};