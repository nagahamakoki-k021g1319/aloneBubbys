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


	////ワールド座標を取得
	Vector3 GetWorldPosition();

	//行動フェーズ
	enum class Phase {
		Approach, //接近する
		Leave,    //離脱する
		ReLeave,  //再離脱する
		ShortAttack,	//攻撃
	};

private:
	Player* player_ = nullptr;
	Collision coll;

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;
	bool isLive = true;
	const int hpMax = 10;
	int hp = hpMax;


	//無敵時間
	bool isHitPlayer;
	bool isHitWolf;

	//フェーズ
	Phase phase_ = Phase::ReLeave;

	//敵の攻撃系統
	////-----ダガーファンネル------///
	std::list<std::unique_ptr<EnemyBullet>> daggerBullets_;
	Model* daggerBulletModel_ = nullptr;
	int enemyAttackTimer = 0;
	//////////////////////////////

	////-----順番に弾が飛んでくる攻撃------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> crystalBullets_;
	Model* enemyCBModel_ = nullptr;
	int enemyAttackTimer2 = 0;
	///////////////////////////////////

	////-----近接攻撃-----////
	EnemyShortRenge* shortRenge = nullptr;
	int enemyAttackTimer3 = 0;
	/////////////////////////

	////-----距離で変わる攻撃-----////
	int enemyRandomAttack = 0;
	////////////////////////////

	////-----ランダムに攻撃方法を変える-----////
	int AttckNmb = 0;
	int randomAttck = 0;
	int numberOfAttacks = 0;
	////////////////////////////


	int enemyResetTimer = 0;

	//パーティクル
	std::unique_ptr<ParticleManager> DamageParticle;


};
