#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

// Imgui �̊Ǘ�
class ImGuiManager
{
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// Imgui��t�J�n
	/// </summary>
	void Begin();
	
	/// <summary>
	/// Imgui��t�I��
	/// </summary>
	void End();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


private:
	DirectXCommon* dxCommon_;

	// SRV�p�f�X�N���v�^�[�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;

public:



};

