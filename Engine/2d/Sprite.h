#pragma once
#include"SpriteCommon.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Affin.h"


// ���_�f�[�^�\����
struct Vertex
{
	Vector3 pos; // xyz���W
	Vector2 uv;  // uv���W
};
//�X�v���C�g
class Sprite {
public:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
	struct ConstBufferDataMaterial {
		Vector4 color; // �F (RGBA)
	};
	//�萔�o�b�t�@�p�\���́i�RD�ϊ��s��j
	struct ConstBufferDataTransform {
		Matrix4 mat;	//3D�ϊ��s��
	};

	//���_�ԍ�
	enum VertexNumber {
		LB,//����
		LT,//����
		RB,//�E��
		RT,//�E��
	};
public:
	//������
	void Initialize(SpriteCommon* spritecommon_, uint32_t textureIndex = UINT32_MAX);

	void Update();

	void Draw();

	void SetPozition(const Vector2& position_);

	const Vector2& GetPosition() const { return position; }

	void SetRotation(float rotation_);

	float GetRotation() { return rotation; }

	void SetColor(const Vector4& color_) { color = color_; }

	Vector4 GetColor() { return color; }

	void SetScale(const Vector3& scale_) { scale = scale_; }

	Vector3 GetScale() { return scale; }

	void SetAnchorPoint(const Vector2& anchorPoint_) { anchorPoint = anchorPoint_; }

	Vector2 GetAnchorPoint() { return anchorPoint; }

	void SetTextureIndex(uint32_t texNmb) { textureIndex_ = texNmb; AdjustTextureSize();}

	uint32_t GetTextureIndex() { return textureIndex_; }

	void SetTexSize(Vector2 texSize) { textureSize = texSize; }

	Vector2 GetTexSize() { return textureSize; }

	Vector2 GetSize() { return size_; }

	void SetSize(Vector2 size);

	/// �㉺���]�̐ݒ�
	void SetIsFlipY(bool isFlipY);

	/// ���E���]�̐ݒ�
	void SetIsFlipX(bool isFlipX);

private:
	//�e�N�X�`���T�C�Y���C���[�W�ɍ��킹��
	void AdjustTextureSize();

	SpriteCommon* spritecomon;
	HRESULT result;
	// ���_�f�[�^
	Vertex vertices[4] = {
		// x      y     z       u     v
		{{-0.4f, -0.7f, 0.0f}, {0.0f, 1.0f}}, // ����
		{{-0.4f, +0.7f, 0.0f}, {0.0f, 0.0f}}, // ����
		{{+0.4f, -0.7f, 0.0f}, {1.0f, 1.0f}}, // �E��
		{{+0.4f, +0.7f, 0.0f}, {1.0f, 0.0f}}, // �E��
	};

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Matrix4 matScale;//�X�P�[�����O�s��
	Matrix4 matWorld;
	Matrix4 matRot;//��]�s��
	Matrix4  matTrans;//���s�ړ��s��

	//���W
	Vector3 scale{ 0.5f, 0.5f, 1.0f };

	Vector2 size_ = { 100.0f,100.0f };

	float rotation = 0.0f;
	Vector2 position = { 0.0f, 0.0f };

	Vector4 color = { 1,1,1,1 };

	Vector2 anchorPoint = { 0.0f,0.0f };

	ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;

	ConstBufferDataMaterial* constMapMaterial = nullptr;

	ComPtr<ID3D12Resource> constBuffMaterial;

	Vertex vertices_[4];

	Vertex* vertMap = nullptr;

	//�e�N�X�`���ԍ�
	uint32_t textureIndex_ = 0;

	//�e�N�X�`��������W
	Vector2 textureLeftTop = { 0.0f,0.0f };
	//�e�N�X�`���؂�o���T�C�Y
	Vector2 textureSize = { 100.0f,100.0f };

	Matrix4 matProjection;

	// �A���J�[�|�C���g
	Vector2 anchorpoint = { 0, 0 };

	// ���_�o�b�t�@�̐���
	ComPtr<ID3D12Resource> vertBuff = nullptr;

	// ���E���]
	bool isFlipX = false;
	// �㉺���]
	bool isFlipY = false;
};

