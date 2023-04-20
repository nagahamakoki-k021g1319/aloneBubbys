#pragma once
#include"Object3d.h"
#include "Input.h"

#include"Wolf.h"

#include "Gorilla.h"
#include "ParticleManager.h"
#include "Audio.h"


class Player {


public:
	Player();
	~Player();

	void Initialize(Input* input);
	void Reset();

	void Update(Transform* cam);
	void Rota();

	void Attack();

	void Draw();
	void EffUpdate();
	void EffDraw();

	void OnCollision();

	void SetEnemyPos(Transform* enemyPos) { enemyPos_ = enemyPos; };

	void LightAttack();
	void HeavyAttack();
	void Dodge();

	bool CheckAttack2Enemy(Vector3 enemyPos, float& damage);


	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////���[���h���W���擾
	Vector3 GetWorldPosition();

	float GetHp() { return hp; };
	bool GetIsDodge() { return isDodge; };

	bool GetIsAttackFin() { return isAttackFin; };

	Vector3 GetDodgeMoveVec() { return dodgeMoveVec; };

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };

public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	Collision col;
	Audio* audio = nullptr;
	//�v���C���[
	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;
	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	//�X�e�[�^�X
	const int defaultHp = 100;
	int hp;
	bool isLive = true;
	bool isAttackFin;
	bool nextAttack;

	//���G����
	bool isInvincible;
	const float invincibleLimit = 15;
	float invincibleTimer = invincibleLimit;

	//��U��
	Vector3 lightAttackLPos;
	Vector3 lightAttackWPos;
	//����߂̘A����
	int lightAttackCount;
	//���̍U���S�̂̎���
	float lightAttackLimit[4] = { 17,18,20,30 };
	float lightAttackTimer;
	//�U���̓����蔻��̗L��
	bool isLightAttack;
	//���肪�o�n�߂鎞��
	float lightAttackPopTime[4] = { 14,13,15,24 };
	//���肪�����鎞��
	float lightAttackDeathTime[4] = { 13,12,14,22 };
	//���̘A���ւ̓��͎�t�J�n����
	float lightAttackInput[4] = { 20,20,20,0 };


	//���U��
	Vector3 heavyAttackLPos;
	Vector3 heavyAttackWPos;
	//����߂̘A����
	int heavyAttackCount;
	//���̍U���S�̂̎���
	float heavyAttackLimit[2] = { 30,30 };
	float heavyAttackTimer;
	//�U���̓����蔻��̗L��
	bool isHeavyAttack;
	//���肪�o�n�߂鎞��
	float heavyAttackPopTime[2] = { 15,25 };
	//���肪�����鎞��
	float heavyAttackDeathTime[2] = { 12,22 };
	//���̘A���ւ̓��͎�t�J�n����
	float heavyAttackInput[2] = { 15,0 };


	//���
	bool isDodge;
	const int dodgeLimit = 20;
	int dodgeTimer;
	//�����d������
	const int dodgeStun = 8;
	Vector3 dodgeMoveVec;
	Vector3 dodgeMoveVecNomal;


	//�G
	Transform* enemyPos_ = nullptr;

	//�p�[�e�B�N���N���X�̏����� 
	std::unique_ptr<ParticleManager> particleManager;
	//�����������̃G�t�F�N�g����
	int isEffFlag = 0;
	int EffTimer = 0;

	//�f�o�b�O�p
	Model* debugModel_ = nullptr;
	Object3d* debugObj_ = nullptr;

	//���֌W�܂Ƃ�
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;


public:
	int isAction;
	//�o�f�B
	Wolf* wolf_ = nullptr;
};