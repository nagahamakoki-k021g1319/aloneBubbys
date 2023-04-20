#include "Transform.h"

Transform::Transform() {
	// ���[�J���X�P�[��
	scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	rotation = { 0,0,0 };
	// ���[�J�����W
	position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	matWorld = Affin::matUnit();
}
Transform::~Transform() {}

void Transform::Initialize() {
	// ���[�J���X�P�[��
	scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	rotation = { 0,0,0 };
	// ���[�J�����W
	position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	matWorld = Affin::matUnit();
}

void Transform::UpdateMat() {
	Matrix4 matScale, matRot, matTrans;
	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = Affin::matScale(scale.x, scale.y, scale.z);
	matRot = Affin::matUnit();
	matRot *= Affin::matRotation(rotation);
	matTrans = Affin::matTrans(position.x, position.y, position.z);

	// ���[���h�s��̍���
	matWorld = Affin::matUnit(); // �ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f
}