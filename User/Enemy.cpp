#include"Enemy.h"
#include"player.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete enemyObj_;
	delete enemyModel_;
	delete daggerBulletModel_;
	daggerBullets_.clear();
	delete enemyCBModel_;
	crystalBullets_.clear();
}

void Enemy::Initialize(Vector3 pos) {
	enemyModel_ = Model::LoadFromOBJ("as");
	enemyObj_ = Object3d::Create();
	enemyObj_->SetModel(enemyModel_);
	enemyObj_->wtf.position = pos;

	// �_�K�[�t�@���l��
	daggerBulletModel_ = Model::LoadFromOBJ("boll");
	//���Ԃɒe�����ł���U��
	enemyCBModel_ = Model::LoadFromOBJ("boll");

	shortRenge = new EnemyShortRenge();
	shortRenge->Initialize(enemyCBModel_);

}

void Enemy::Update() {

	{//���Ńv���C���[�Ƃ̂����
		player_->SetEnemyPos(&enemyObj_->wtf);
	}
	AttackDistance();

	enemyObj_->Update();

	//�e�틅�X�V
	//�_�K�[�o���b�g
	daggerBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });
	for (std::unique_ptr<EnemyBullet>& bullet : daggerBullets_) {
		bullet->Update();
		if (bullet->isPop) {
			//���Ńv���C���[�Ƃ̂����
			if (coll.CircleCollision(player_->GetWorldPosition(), bullet->GetPos(), 1.0f, 1.0f)) {
				player_->OnCollision();
				bullet->OnCollision();
			}
		}
	}
	//�N���X�^���o���b�g
	crystalBullets_.remove_if([](std::unique_ptr<EnemyCrystalBullet>& bullet) { return bullet->IsDead(); });
	for (std::unique_ptr<EnemyCrystalBullet>& bullet : crystalBullets_) {
		bullet->Update();
		{//���Ńv���C���[�Ƃ̂����
			if (coll.CircleCollision(player_->GetWorldPosition(), bullet->GetWorldPosition(), 2.0f, 2.0f)) {
				player_->OnCollision();
				bullet->OnCollision();
			}
		}
	}
	if (shortRenge->GetCollision() == true) {
		player_->OnCollision();
	}

	switch (phase_) {
	case Phase::Approach:
		enemyResetTimer = 0;
		enemyAttackTimer++;

		//�t�F�[�Y�ڍs
		if (enemyAttackTimer >= 450) {
			phase_ = Phase::ReLeave;
			numberOfAttacks++;
		}

		//�U������܂ňړ�
		if (enemyAttackTimer >= 0 && enemyAttackTimer <= 9) {
			enemyObj_->wtf.position.z += 0.1f;
		}
		//�U������܂ňړ�
		if (enemyAttackTimer >= 150 && enemyAttackTimer <= 190) {
			enemyObj_->wtf.position.z += 0.05f;
			enemyObj_->wtf.position.x += 0.1f;
		}

		//�_�K�[�t�@���l����b���ōU��������
		if (enemyAttackTimer == 10 || enemyAttackTimer == 200 || enemyAttackTimer == 250) {
			CreatDaggerBullet(5);
		}


		break;
	case Phase::Leave:

		enemyAttackTimer2++;
		if (enemyAttackTimer2 >= 300) {
			phase_ = Phase::ReLeave;
			numberOfAttacks++;
		}

		//�U������܂ňړ�
		if (enemyAttackTimer2 >= 0 && enemyAttackTimer2 <= 9) {
			enemyObj_->wtf.position.z -= 0.05f;
			enemyObj_->wtf.position.x -= 0.1f;
		}
		//���ԂɍU������e��b���ōU��������
		if (enemyAttackTimer2 == 10) {
			CreatCrystalBullet();
		}

		break;
	case Phase::ReLeave:
		//enemyResetTimer++;
		//if (enemyResetTimer >= 50) {
		//	phase_ = Phase::Random;
		//}
		enemyAttackTimer = 0;
		enemyAttackTimer2 = 0;
		enemyAttackTimer3 = 0;
		//�ߋ���
		if (AttckNmb == 1) {
			if (randomAttck <= 5) {
				phase_ = Phase::Approach;
			}
			else if (6 <= randomAttck <= 8) {
				phase_ = Phase::Leave;
			}
			else if (9 <= randomAttck) {
				phase_ = Phase::ShortAttack;
			}
		}
		//������
		else if (AttckNmb == 2) {
			if (randomAttck <= 5) {
				phase_ = Phase::Leave;
			}
			else if (6 <= randomAttck <= 8) {
				phase_ = Phase::ShortAttack;
			}
			else if (9 <= randomAttck) {
				phase_ = Phase::Approach;
			}
		}
		//������
		else if (AttckNmb == 3) {
			if (randomAttck <= 5) {
				phase_ = Phase::ShortAttack;
			}
			else if (6 <= randomAttck <= 8) {
				phase_ = Phase::Approach;
			}
			else if (9 <= randomAttck) {
				phase_ = Phase::Leave;
			}
		}
		break;
	case Phase::ShortAttack:
		enemyAttackTimer3++;
		shortRenge->Update(player_->GetWorldPosition(), enemyObj_);
		if (enemyAttackTimer3 >= 120) {
			phase_ = Phase::ReLeave;
			shortRenge->ResetAttack();
			numberOfAttacks++;
		}

		break;
	}
	if (numberOfAttacks >= 3) {
		AttckNmb = 0;
		numberOfAttacks = 0;
	}

}

void Enemy::CreatDaggerBullet(int bulletNum) {
	for (int i = 0; i < bulletNum; i++) {
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(20 + 20 * i, daggerBulletModel_);
		newBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f + 2.0f * i,enemyObj_->wtf.position.y,enemyObj_->wtf.position.z + 8.0f });
		newBullet->SetScale({ 0.5f,0.5f, 0.5f });
		daggerBullets_.push_back(std::move(newBullet));
	}
}

void Enemy::CreatCrystalBullet() {
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
		newCrystalBullet->Initialize(i, enemyCBModel_);
		newCrystalBullet->SetPos({ enemyObj_->wtf.position.x - 2.0f + 4.0f * i,enemyObj_->wtf.position.y - 3.0f,enemyObj_->wtf.position.z + 15.0f });
		newCrystalBullet->Vec(player_->GetWorldPosition());
		crystalBullets_.push_back(std::move(newCrystalBullet));
	}

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet->Initialize(2, enemyCBModel_);
	newCrystalBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f,enemyObj_->wtf.position.y + 1.0f, enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet));

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet2 = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet2->Initialize(3, enemyCBModel_);
	newCrystalBullet2->SetPos({ enemyObj_->wtf.position.x + 4.0f,enemyObj_->wtf.position.y + 1.0f, enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet2->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet2));

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet3 = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet3->Initialize(4, enemyCBModel_);
	newCrystalBullet3->SetPos({ enemyObj_->wtf.position.x,enemyObj_->wtf.position.y + 4.0f,enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet3->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet3));
}

void Enemy::Draw() {
	enemyObj_->Draw();

	for (std::unique_ptr<EnemyBullet>& bullet : daggerBullets_) {
		bullet->Draw();
	}

	for (std::unique_ptr<EnemyCrystalBullet>& bullet : crystalBullets_) {
		bullet->Draw();
	}

	switch (phase_) {
	case Phase::Approach:

		break;
	case Phase::Leave:

		break;

	case Phase::ReLeave:
		break;
	case Phase::ShortAttack:
		shortRenge->Draw();
		break;
	}


}

void Enemy::EffUpdate()
{
	//�p�[�e�B�N���͈�
	for (int i = 0; i < 20; i++) {
		//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 0.1f;
		const float rnd_pos2 = 10.0f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos2 - rnd_pos2 / 2.0f;
		pos += enemyObj_->wtf.position;

		//���x
		//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
		const float rnd_acc = 0.00001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//�ǉ�
		DamageParticle->Add(60, pos, vel, acc, 1.0f, 0.0f);

		DamageParticle->Update();
	}

}

Vector3 Enemy::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyObj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyObj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyObj_->wtf.matWorld.m[3][2];


	return worldPos;
}

void Enemy::OnColision(int damage) {
	//player
	if (isHitPlayer == false) {
		hp -= damage;
		if (hp <= 0) {
			isLive = false;
		}
		isHitPlayer = true;
	}
}

void Enemy::AttackDistance()
{
	Vector3 EnemyLength = GetWorldPosition() - player_->GetWorldPosition();
	float len = EnemyLength.length();
	randomAttck = rand() % 10 + 1;
	if (AttckNmb == 0) {
		if (len <= 20) {
			AttckNmb = 1;
		}
		else if (20 < len < 60) {
			AttckNmb = 2;
		}
		else if (len >= 60) {
			AttckNmb = 3;
		}
		numberOfAttacks = 0;
	}
}

