#pragma once
#include "EnemyBullet.h"
#include "EnemyCrystalBullet.h"
#include "EnemyShortRenge.h"

class Player;
#include "Collision.h"
#include "ParticleManager.h"

class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize(Vector3 pos);
	void Update();
	void Draw();

	void EffUpdate();

	void SetPlayer(Player* player) { player_ = player; };

	void CreatDaggerBullet(int bulletNum);

	void CreatCrystalBullet();

	bool IsDead() const { if (isLive) { return false; } else { return true; } };

	void OnColision(int damage);


	void AttackDistance();

	void ResetHit2player() { isHitPlayer = false; };


	////���[���h���W���擾
	Vector3 GetWorldPosition();

	//�s���t�F�[�Y
	enum class Phase {
		Approach, //�ڋ߂���
		Leave,    //���E����
		ReLeave,  //�ė��E����
		ShortAttack,	//�U��
	};

private:
	Player* player_ = nullptr;
	Collision coll;

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;
	bool isLive = true;
	const int hpMax = 10;
	int hp = hpMax;


	//���G����
	bool isHitPlayer;
	bool isHitWolf;

	//�t�F�[�Y
	Phase phase_ = Phase::ReLeave;

	//�G�̍U���n��
	////-----�_�K�[�t�@���l��------///
	std::list<std::unique_ptr<EnemyBullet>> daggerBullets_;
	Model* daggerBulletModel_ = nullptr;
	int enemyAttackTimer = 0;
	//////////////////////////////

	////-----���Ԃɒe�����ł���U��------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> crystalBullets_;
	Model* enemyCBModel_ = nullptr;
	int enemyAttackTimer2 = 0;
	///////////////////////////////////

	////-----�ߐڍU��-----////
	EnemyShortRenge* shortRenge = nullptr;
	int enemyAttackTimer3 = 0;
	/////////////////////////

	////-----�����ŕς��U��-----////
	int enemyRandomAttack = 0;
	////////////////////////////

	////-----�����_���ɍU�����@��ς���-----////
	int AttckNmb = 0;
	int randomAttck = 0;
	int numberOfAttacks = 0;
	////////////////////////////


	int enemyResetTimer = 0;

	//�p�[�e�B�N��
	std::unique_ptr<ParticleManager> DamageParticle;


};
