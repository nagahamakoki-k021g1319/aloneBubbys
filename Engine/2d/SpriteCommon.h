#pragma once
#include"DirectXCommon.h"
#include <DirectXTex.h>
#include <array>
#include <string>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Affin.h"


//�X�v���C�g���ʕ���
class SpriteCommon {
public:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	struct Vertex
	{
		Vector3 pos; // xyz���W
		Vector2 uv;  // uv���W
	};
	// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
	struct ConstBufferDataMaterial {
		Vector4 color; // �F (RGBA)
	};
	//�萔�o�b�t�@�p�\���́i�RD�ϊ��s��j
	struct ConstBufferDataTransform {
		Matrix4 mat;	//3D�ϊ��s��
	};
public:
	//������
	void Initialize(DirectXCommon* dxcommon);

	DirectXCommon* GetDxCommon() { return dxcommon_; }

	ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }

	ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }

	ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }

	D3D12_CPU_DESCRIPTOR_HANDLE GetSrvHandle() { return srvHandle; }

	UINT GetSizeVB() { return sizeVB; }

	D3D12_RESOURCE_DESC& GetResourceDesc() { return resDesc; }

	void LoadTexture(uint32_t index, const std::string& fileName);

	void SetTextureCommands(uint32_t index);

	//Microsoft::WRL::ComPtr<ID3D12Resource> GetTexBuff(uint32_t index) { return texBuff[index]; }

	Microsoft::WRL::ComPtr<ID3D12Resource> GetTextureBuffer(uint32_t index)const { return texBuff[index].Get(); }

	//SRV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap = nullptr;
private:
	// ���_�f�[�^
	Vertex vertices[4] = {
		// x      y     z       u     v
		{{-0.4f, -0.7f, 0.0f}, {0.0f, 1.0f}}, // ����
		{{-0.4f, +0.7f, 0.0f}, {0.0f, 0.0f}}, // ����
		{{+0.4f, -0.7f, 0.0f}, {1.0f, 1.0f}}, // �E��
		{{+0.4f, +0.7f, 0.0f}, {1.0f, 0.0f}}, // �E��
	};
	// SRV�̍ő��
	static const size_t kMaxSRVCount = 2056;

	DirectXCommon* dxcommon_;
	ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g
	HRESULT result;

	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v�����X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;
	std::array<ComPtr<ID3D12Resource>, kMaxSRVCount>texBuff;

	//�������s�N�Z����
	const size_t textureWidth = 256;
	//�c�����s�N�Z����
	const size_t textureHeight = 256;
	//�z��̗v�f��
	const size_t imageDataCount = textureWidth * textureHeight;

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

	TexMetadata metadata{};
	ScratchImage scratchImg{};
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	D3D12_RESOURCE_DESC textureResourceDesc{};

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	UINT sizeVB;

	D3D12_RESOURCE_DESC resDesc{};

	//�f�t�H���g�e�N�X�`���i�[�f�B���N�g��
	static std::string kDefaultTextureDirectoryPath;

	UINT incrementSize;
};