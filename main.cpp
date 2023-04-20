
#include "WinApp.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "ImGuiManager.h"
#include <imgui.h>


#include "GameScene.h"



int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

#pragma region WindowsAPI����������


	//�|�C���^
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;
	GameScene* gameScene = nullptr;

	ImGuiManager* imgui = nullptr;

	//windowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏������@
	input = new Input();
	input->Initialize(winApp);

	// ImGui�̏�����
	imgui = new ImGuiManager();
	imgui->Initialize(winApp,dxCommon);





#pragma endregion

#pragma region DirectX����������
	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//�p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	

#pragma endregion

#pragma region �`�揉��������

	////////////////////////////
	//------�����ǂݍ���--------//
	///////////////////////////

	// �Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input);

	//FPS�ς������Ƃ�
	fps->SetFrameRate(60);

#pragma endregion
	//�Q�[�����[�v
	while (true) {
#pragma region �E�B���h�E���b�Z�[�W����

		//�A�v���P�[�V�������I��鎞��message��WM_QUIT�ɂȂ�
		if (winApp->ProcessMessage()) {
			break;
		}
		if (input->PushKey(DIK_ESCAPE)) {
			break;
		}


		fps->FpsControlBegin();

#pragma endregion

#pragma region DirectX���t���[������
		/////////////////////////////////////////////////////
		//----------DireceX���t���[�������@��������------------//
		///////////////////////////////////////////////////

		//���͂̍X�V
		input->Update();	

		// �Q�[���V�[���̖��t���[������
		gameScene->Update();		

		//////////////////////////////////////////////
		//-------DireceX���t���[�������@�����܂�--------//
		////////////////////////////////////////////

#pragma endregion

#pragma region �O���t�B�b�N�X�R�}���h

		//4.�`��R�}���h��������
		dxCommon->PreDraw();

		// Imgui��t�J�n
		imgui->Begin();
		// �f���E�B���h�E�̕\���I��
		ImGui::ShowDemoWindow();

		// �Q�[���V�[���̕`��
		gameScene->Draw();


		// Imgui��t�I��
		imgui->End();
		// Imgui�`��
		imgui->Draw();

		// �`��I��
		dxCommon->PostDraw();

		fps->FpsControlEnd();
		//4.�`��R�}���h�����܂�

#pragma endregion

#pragma region ��ʓ���ւ�

#pragma endregion
	}
#pragma region  WindowsAPI��n��

	/*ID3D12DebugDevice* debugInterface;
	if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(&debugInterface))) {
		debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
		debugInterface->Release();
	}*/

	delete gameScene;

	imgui->Finalize();
	//WindowsAPI�̏I������
	winApp->Finalize();
	delete imgui;

	//���͊J��
	delete input;
	//WindowsAPI�J��
	delete winApp;
	delete dxCommon;

	delete fps;
	
#pragma endregion
	return 0;
}