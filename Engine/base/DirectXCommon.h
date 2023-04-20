#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
//#include <DirectXTex.h>
#include <vector>

// Microsoft::WRL::���ȗ�
//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

//DirectX���
class DirectXCommon
{
public://�����o�֐�
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//������
	void Initialize(WinApp* winApp);

	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapchain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

	//�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();

	//�f�o�C�X�擾
	ID3D12Device* GetDevice() const { return device.Get(); }

	//�R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }

	//�o�b�N�o�b�t�@�̐����擾
	size_t GetBackBufferCount() const { return backBuffers.size(); }

private:
	//DirectX12�f�o�C�X
	ComPtr<ID3D12Device> device;
	//DXGI�t�@�N�g��
	ComPtr<IDXGIFactory7> dxgiFactory;
	//�o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>> backBuffers;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_RESOURCE_DESC depthResourceDesc{};

	//WindowsAPI
	WinApp* winApp_ = nullptr;

	HRESULT result;
    ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	ComPtr<ID3D12Fence> fence;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	D3D12_RESOURCE_BARRIER barrierDesc{};
	UINT64 fenceVal = 0;
	ComPtr<ID3D12Resource> depthBuff;
};