﻿#include "Camera.h"

using namespace DirectX;

Camera::Camera(int window_width, int window_height)
{
	aspectRatio = (float)window_width / window_height;

	//ビュー行列の計算
	UpdateViewMatrix();

	// 射影行列の計算
	UpdateProjectionMatrix();

	// ビュープロジェクションの合成
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
	matViewProjection = matView * matProjection;
}

void Camera::Update(Transform wtf){

	Matrix4 affineMat;
	affineMat.MakeIdentity;
	affineMat = Affin::matTrans(eye);

	affineMat *= wtf.matWorld;

	Vector3 newEye;
	newEye.x = affineMat.m[3][0];
	newEye.y = affineMat.m[3][1];
	newEye.z = affineMat.m[3][2];


	UpdateViewMatrix(newEye);
	UpdateProjectionMatrix();
	matViewProjection = matView * matProjection;
}

void Camera::UpdateViewMatrix(){

	XMFLOAT3 xmEye;
	xmEye.x = eye.x;
	xmEye.y = eye.y;
	xmEye.z = eye.z;

	XMFLOAT3 xmTarget;
	xmTarget.x = target.x;
	xmTarget.y = target.y;
	xmTarget.z = target.z;

	XMFLOAT3 xmUp;
	xmUp.x = up.x;
	xmUp.y = up.y;
	xmUp.z = up.z;

	XMMATRIX xmMatView = XMMatrixLookAtLH(
		XMLoadFloat3(&xmEye), XMLoadFloat3(&xmTarget), XMLoadFloat3(&xmUp));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			matView.m[i][j] = xmMatView.r[i].m128_f32[j];

		}
	}

	//// 視点座標
	//Vector3 eyePosition = eye;
	//// 注視点座標
	//Vector3 targetPosition = target;
	//// （仮の）上方向
	//Vector3 upVector = up;

	//Vector3 ZERO = { 0,0,0 };
	//Vector3 resultt;

	//// カメラZ軸（視線方向）
	//Vector3 cameraAxisZ = targetPosition - eyePosition;

	//// 0ベクトルだと向きが定まらないので除外
	//assert(!Vector3::Vector3Equal(cameraAxisZ, ZERO));
	//assert(cameraAxisZ.Vector3IsInfinite());
	//assert(!Vector3::Vector3Equal(upVector, ZERO));
	//assert(upVector.Vector3IsInfinite());

	//// ベクトルを正規化
	//cameraAxisZ.nomalize();

	//// カメラのX軸（右方向）
	//Vector3 cameraAxisX;
	//// X軸は上方向→Z軸の外積で求まる
	//cameraAxisX = upVector.cross(cameraAxisZ);
	//// ベクトルを正規化
	//cameraAxisX.nomalize();

	//// カメラのY軸（上方向）
	//Vector3 cameraAxisY;
	//// Y軸はZ軸→X軸の外積で求まる
	//cameraAxisY = cameraAxisZ.cross(cameraAxisX);

	//// ここまでで直交した3方向のベクトルが揃う
	////（ワールド座標系でのカメラの右方向、上方向、前方向）	

	//// カメラ回転行列
	//Matrix4 matCameraRot;
	//// カメラ座標系→ワールド座標系の変換行列
	//matCameraRot.m[0][0] = cameraAxisX.x;
	//matCameraRot.m[0][1] = cameraAxisX.y;
	//matCameraRot.m[0][2] = cameraAxisX.z;
	//matCameraRot.m[0][3] = 0;

	//matCameraRot.m[1][0] = cameraAxisY.x;
	//matCameraRot.m[1][1] = cameraAxisY.y;
	//matCameraRot.m[1][2] = cameraAxisY.z;
	//matCameraRot.m[1][3] = 0;

	//matCameraRot.m[2][0] = cameraAxisZ.x;
	//matCameraRot.m[2][1] = cameraAxisZ.y;
	//matCameraRot.m[2][2] = cameraAxisZ.z;
	//matCameraRot.m[2][3] = 0;

	//matCameraRot.m[3][0] = 0;
	//matCameraRot.m[3][1] = 0;
	//matCameraRot.m[3][2] = 0;
	//matCameraRot.m[3][3] = 1;

	//// 転置により逆行列（逆回転）を計算
	//matView.MakeInverse(&matCameraRot);

	//// 視点座標に-1を掛けた座標
	//Vector3 reverseEyePosition = -eyePosition;
	//// カメラの位置からワールド原点へのベクトル（カメラ座標系）
	//float tX = cameraAxisX.dot(reverseEyePosition);	// X成分
	//float tY = cameraAxisY.dot(reverseEyePosition);	// Y成分
	//float tZ = cameraAxisZ.dot(reverseEyePosition);	// Z成分
	//// 一つのベクトルにまとめる
	//Vector3 translation = { tX,tY,tZ };
	//// ビュー行列に平行移動成分を設定
	//matView.m[3][0] = translation.x;
	//matView.m[3][1] = translation.y;
	//matView.m[3][2] = translation.z;

#pragma region 全方向ビルボード行列の計算
//	// ビルボード行列
//	matBillboard.m[0][0] = cameraAxisX.x;
//	matBillboard.m[0][1] = cameraAxisX.y;
//	matBillboard.m[0][2] = cameraAxisX.z;
//	matBillboard.m[0][3] = 0;
//
//	matBillboard.m[1][0] = cameraAxisY.x;
//	matBillboard.m[1][1] = cameraAxisY.y;
//	matBillboard.m[1][2] = cameraAxisY.z;
//	matBillboard.m[1][3] = 0;
//
//	matBillboard.m[2][0] = cameraAxisZ.x;
//	matBillboard.m[2][1] = cameraAxisZ.y;
//	matBillboard.m[2][2] = cameraAxisZ.z;
//	matBillboard.m[2][3] = 0;
//
//	matBillboard.m[3][0] = 0;
//	matBillboard.m[3][1] = 0;
//	matBillboard.m[3][2] = 0;
//	matBillboard.m[3][3] = 1;
//
//#pragma region Y軸回りビルボード行列の計算
//	// カメラX軸、Y軸、Z軸
//	Vector3 ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;
//
//	// X軸は共通
//	ybillCameraAxisX = cameraAxisX;
//	// Y軸はワールド座標系のY軸
//	ybillCameraAxisY = upVector.nomalize();
//	// Z軸はX軸→Y軸の外積で求まる
//	ybillCameraAxisZ = ybillCameraAxisX.cross(ybillCameraAxisY);
//
//	// Y軸回りビルボード行列
//
//	matBillboardY.m[0][0] = ybillCameraAxisX.x;
//	matBillboardY.m[0][1] = ybillCameraAxisX.y;
//	matBillboardY.m[0][2] = ybillCameraAxisX.z;
//	matBillboardY.m[0][3] = 0;
//
//	matBillboardY.m[1][0] = ybillCameraAxisY.x;
//	matBillboardY.m[1][1] = ybillCameraAxisY.y;
//	matBillboardY.m[1][2] = ybillCameraAxisY.z;
//	matBillboardY.m[1][3] = 0;
//
//	matBillboardY.m[2][0] = ybillCameraAxisZ.x;
//	matBillboardY.m[2][1] = ybillCameraAxisZ.y;
//	matBillboardY.m[2][2] = ybillCameraAxisZ.z;
//	matBillboardY.m[2][3] = 0;
//
//	matBillboardY.m[3][0] = 0;
//	matBillboardY.m[3][1] = 0;
//	matBillboardY.m[3][2] = 0;
//	matBillboardY.m[3][3] = 1;
#pragma endregion
}

void Camera::UpdateViewMatrix(Vector3 newEye) {
	XMFLOAT3 xmEye;
	xmEye.x = newEye.x;
	xmEye.y = newEye.y;
	xmEye.z = newEye.z;

	XMFLOAT3 xmTarget;
	xmTarget.x = target.x;
	xmTarget.y = target.y;
	xmTarget.z = target.z;

	XMFLOAT3 xmUp;
	xmUp.x = up.x;
	xmUp.y = up.y;
	xmUp.z = up.z;

	XMMATRIX xmMatView = XMMatrixLookAtLH(
		XMLoadFloat3(&xmEye), XMLoadFloat3(&xmTarget), XMLoadFloat3(&xmUp));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			matView.m[i][j] = xmMatView.r[i].m128_f32[j];

		}
	}
}

void Camera::UpdateProjectionMatrix()
{
	// 透視投影による射影行列の生成
	matProjection.MakePerspectiveL(
		FieldOfViewY(),
		aspectRatio,
		0.1f, 100000.0f, matProjection
	);
}

void Camera::MoveEyeVector(const Vector3& move)
{
	// 視点座標を移動し、反映
	Vector3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}

void Camera::MoveVector(const Vector3& move)
{
	// 視点と注視点座標を移動し、反映
	Vector3 eye_moved = GetEye();
	Vector3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

float Camera::FieldOfViewY() {

	return 2 * atan(sensor / (2 * focalLengs));

}