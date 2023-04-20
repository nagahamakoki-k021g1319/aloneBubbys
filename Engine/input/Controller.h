#pragma once
#include <windows.h>
#include "Vector2.h"
#include <xinput.h>
#pragma comment (lib, "xinput.lib")

enum ControllerButton
{
	B = XINPUT_GAMEPAD_B,
	A = XINPUT_GAMEPAD_A,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,
	START = XINPUT_GAMEPAD_START,
	BACK = XINPUT_GAMEPAD_BACK,
	LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	LT,
	RT
};

enum ControllerStick
{
	L_UP, L_DOWN, L_LEFT, L_RIGHT,
	R_UP, R_DOWN, R_LEFT, R_RIGHT, XBOX_STICK_NUM
};

class Controller
{
private:

	XINPUT_STATE xinputState{};
	XINPUT_STATE oldXinputState{};

	//�R���g���[���[�U������
	float shakePower = 0.0f;
	//�R���g���[���[�U������(�t���[����)
	int shakeTimer = 0;

	//�f�b�h�]�[���ɓ����Ă��邩(DeadRate : �f�b�h�]�[������̓x�����A1.0f���ƃf�t�H���g)
	bool StickInDeadZone(Vector2& thumb, const Vector2& deadRate);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Controller& operator=(const Controller&) = delete;
	Controller(const Controller&) = delete;

	//�ō����͋��x
	const float STICK_INPUT_MAX = 32768.0f;

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	Controller() ;
	~Controller();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �R���g���[���[�{�^���̃g���K�[����
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool ButtonTrigger(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̃g���K�[����
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�|�������ǂ���</returns>
	bool StickTrigger(ControllerStick stickInput, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });
	
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
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
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
};

