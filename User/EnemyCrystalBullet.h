#pragma once
#include "Object3d.h"
#include <memory>
#include <list>
class Player;

class EnemyCrystalBullet {
public:
	~EnemyCrystalBullet();

	///< summary>
	///������
	///</summary>
	void Initialize(int num, Model* crystalModel_);
	///< summary>
	///�X�V
	///</summary>
	void CrystalBAttack();

	///< summary>
	///�X�V
	///</summary>
	void Update();

	///< summary>
	///�`��
	///</summary>
	void Draw();

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { crystalObj_->wtf.position = pos; };

	/// <summary>
	/// �傫��
	/// </summary>
	/// <param name="pos"></param>
	void SetScale(Vector3 scale) { crystalObj_->wtf.scale = scale; };

	void Vec(Vector3 pos);

	bool IsDead() const { if (isLive) { return false; } else { return true; } };

	void OnCollision();

	////���[���h���W���擾
	Vector3 GetWorldPosition();

private:

	////-----------///
	Object3d* crystalObj_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int crystalTimer;
	bool isLive = false;
	int shotTimer;
	//////////////////////////////

	int bulletNum;

	Vector3 A_BVecNolm;
	const float speed = 0.5f;
};

