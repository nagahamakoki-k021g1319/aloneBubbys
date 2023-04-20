#pragma once
#include <windows.h>
#include <wrl.h>
#include <dinput.h>
#include "WinApp.h"
#include"Controller.h"

#define DIRECTINPUT_VERSION 0x0800 // DirectInput�̃o�[�W�����w��


// ����
class Input
{
public:
	// namespace
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�
	// ������
	void Initialize(WinApp* winApp);

	// �X�V
	void Update();

	/// <summary>
	/// �L�[�̉������`�F�b�N
	/// </summary>
	/// <param name = "keyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	/// </param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
	/// <reutrns>�g���K�[��</params>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	/// </param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
	/// <reutrns>�����ꂽ��</params>
	bool ReleaseKey(BYTE keyNumber);

	//----- �R���g���[��- ------//

	/// <summary>
	/// �R���g���[���[�{�^���̃g���K�[����
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool PButtonTrigger(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̃g���K�[����
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�|�������ǂ���</returns>
	bool PStickTrigger(ControllerStick stickInput, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�{�^���̓���
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool ButtonInput(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̓���
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�|�������ǂ���</returns>
	bool StickInput(ControllerStick stickInput, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });


	/// <summary>
	/// �R���g���[���[���X�e�B�b�N�̓���
	/// </summary>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�|�������ǂ���</returns>
	bool LeftStickInput(const float& deadRange = 0.3f);

	/// <summary>
	/// �R���g���[���[�{�^���̗������u��
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool ButtonOffTrigger(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̗������u��
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>��������</returns>
	bool StickOffTrigger(ControllerStick stickInput, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�̍��X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�x�N�g��</returns>
	Vector2 GetLeftStickVec(const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�̉E�X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�x�N�g��</returns>
	Vector2 GetRightStickVec(const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[��U��������
	/// </summary>
	/// <param name="power">�U���̋���0.0f�`1.0f</param>
	/// <param name="span">�U���̎��ԃt���[��</param>
	void ShakeController(const float& power, const int& span);


private: // �����o�ϐ�
	// �L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> keyboard;
	// DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput;
	//�R���g���[���[
	Controller* controller = nullptr;
	// �S�L�[�̏��
	BYTE key[256] = {};
	// �O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
	//windwsAPI
	WinApp* winApp_ = nullptr;
};