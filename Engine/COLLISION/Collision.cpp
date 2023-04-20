#include "Collision.h"

using namespace DirectX;

void Collision::ClosestPtPoint2Triangle(const Vector3& point, const Triangle& triangle, Vector3* closest)
{
	//point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	Vector3 p0_p2 = triangle.p2 - triangle.p0;
	Vector3 p0_pt = point - triangle.p0;

	float d1 = p0_p1.dot(p0_pt);
	float d2 = p0_p2.dot(p0_pt);

	if (d1<= 0.0f && d2<= 0.0f)
	{
		// p0���ŋߖT
		*closest = triangle.p0;
		return;
	}

	// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p1_pt = point - triangle.p1;

	float d3 = p0_p1.dot(p1_pt);
	float d4 = p0_p2.dot(p1_pt);

	if (d3>= 0.0f && d4 <= d3)
	{
		// p1���ŋߖT
		*closest = triangle.p1;
		return;
	}

	// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p2_pt = point - triangle.p2;

	float d5 = p0_p1.dot(p2_pt);
	float d6 = p0_p2.dot(p2_pt);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, Vector3* inter)
{
	Vector3 p;

	ClosestPtPoint2Triangle(sphere.center, triangle, &p);

	Vector3 v = p - sphere.center;

	float vp = v.dot(v);

	if (vp > sphere.radius * sphere.radius) { return false; }

	if (inter) {
		*inter = p;
	}

	return true;
}

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter)
{
	float distV = sphere.center.dot(plane.normal);

	float dist = distV - plane.distance;

	if (fabs(dist) > sphere.radius) { return false; }

	// �[����_���v�Z
	if (inter)
	{
		// ���ʏ�̍Đڋߓ_���A�^����_�Ƃ���
		*inter = -dist * plane.normal + sphere.center;
	}

	return true;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, Vector3* inter)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl

	float d1 = plane.normal.dot(ray.dir);
	// ���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon)
	{
		return false;
	}

	float d2 = plane.normal.dot(ray.start);
	float dist = d2 - plane.distance;

	float t = dist / -d1;

	if (t < 0) return false;

	// ��������������
	if (distance)
	{
		*distance = t;
	}

	// ��_���v�Z
	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance, Vector3* inter)
{
	Plane plane;

	Vector3 interPlane;
	plane.normal = triangle.normal;
	plane.distance = triangle.normal.dot(triangle.p0);

	if (!CheckRay2Plane(ray, plane, distance, &interPlane)) { return false; }

	const float epsilon = 1.0e-5f;

	Vector3 m;

	Vector3 pt_p0 = triangle.p0 - interPlane;
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	m = pt_p0.cross(p0_p1);

	if (m.dot(triangle.normal) < -epsilon) { return false; }

	// ��p1_p2�ɂ���
	Vector3 pt_p1 = triangle.p1 - interPlane;
	Vector3 p1_p2 = triangle.p2 - triangle.p1;
	m = pt_p1.cross(p1_p2);
	// �ӂ̊O��
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	// ��p2_p0�ɂ���
	Vector3 pt_p2 = triangle.p2 - interPlane;
	Vector3 p2_p0 = triangle.p0 - triangle.p2;
	m = pt_p2.cross(p2_p0);
	// �ӂ̊O��
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}
	if (inter)
	{
		*inter = interPlane;
	}

	// �����Ȃ̂ŁA�������Ă���
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance, Vector3* inter)
{
	Vector3 m = ray.start - sphere.center;
	float b = m.dot(ray.dir);
	float c = m.dot(m) - sphere.radius * sphere.radius;
	// lay�̎n�_��sphere�̊O���ɂ���(c > 0)�Alay��sphere���痣��Ă���������
	// �����Ă���ꍇ(b > 0)�A������Ȃ�
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	// ���̔��ʎ��̓��C�������O��Ă��邱�ƂɈ�v
	if (discr < 0.0f)
	{
		return false;
	}

	// ���C�͋��ƌ������Ă���B
	// ��������ŏ��̒lt���v�Z
	float t = -b - sqrtf(discr);
	// t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
	if (t < 0) t = 0.0f;

	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::BoxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth, Vector3 enemyWidth)
{

	//�v���C���[
	float pXMin = player.x - playerWidth.x;

	float pXMax = player.x + playerWidth.x;

	float pYMin = player.y - playerWidth.y;

	float pYMax = player.y + playerWidth.y;

	float pZMin = player.z - playerWidth.z;

	float pZMax = player.z + playerWidth.z;

	//�G
	//����
	float eXMin = enemy.x - enemyWidth.x;

	float eXMax = enemy.x + enemyWidth.x;

	float eYMin = enemy.y - enemyWidth.y;

	float eYMax = enemy.y + enemyWidth.y;

	float eZMin = enemy.z - enemyWidth.z;

	float eZMax = enemy.z + enemyWidth.z;

	if ((pXMin <= eXMax && pXMax >= eXMin) && (pYMin <= eYMax && pYMax >= eYMin) && (pZMin <= eZMax && pZMax >= eZMin)) {
		return true;
	}
	return false;
}

bool Collision::BoxCircle(Vector3 boxPos, Vector3 circlePos, Vector3 boxWidth, float circleWidth)
{
	//�v���C���[
	float bXMin = boxPos.x - boxWidth.x;

	float bXMax = boxPos.x + boxWidth.x;

	float bYMin = boxPos.y - boxWidth.y;

	float bYMax = boxPos.y + boxWidth.y;

	float bZMin = boxPos.z - boxWidth.z;

	float bZMax = boxPos.z + boxWidth.z;

	XMFLOAT3 box1 = { bXMax,bYMax,bZMax };

	XMFLOAT3 box2 = { bXMin,bYMax,bZMax };

	XMFLOAT3 box3 = { bXMin,bYMax,bZMin };

	XMFLOAT3 box4 = { bXMax,bYMax,bZMin };

	XMFLOAT3 box5 = { bXMax,bYMin,bZMax };

	XMFLOAT3 box6 = { bXMin,bYMin,bZMax };

	XMFLOAT3 box7 = { bXMin,bYMin,bZMin };

	XMFLOAT3 box8 = { bXMax,bYMin,bZMin };

	double bo1c = (box1.x - circlePos.x) * (box1.x - circlePos.x) + (box1.y - circlePos.y) * (box1.y - circlePos.y) + (box1.z - circlePos.z) * (box1.z - circlePos.z);
	double bo2c = (box2.x - circlePos.x) * (box2.x - circlePos.x) + (box2.y - circlePos.y) * (box2.y - circlePos.y) + (box2.z - circlePos.z) * (box2.z - circlePos.z);
	double bo3c = (box3.x - circlePos.x) * (box3.x - circlePos.x) + (box3.y - circlePos.y) * (box3.y - circlePos.y) + (box3.z - circlePos.z) * (box3.z - circlePos.z);
	double bo4c = (box4.x - circlePos.x) * (box4.x - circlePos.x) + (box4.y - circlePos.y) * (box4.y - circlePos.y) + (box4.z - circlePos.z) * (box4.z - circlePos.z);
	double bo5c = (box5.x - circlePos.x) * (box5.x - circlePos.x) + (box5.y - circlePos.y) * (box5.y - circlePos.y) + (box5.z - circlePos.z) * (box5.z - circlePos.z);
	double bo6c = (box6.x - circlePos.x) * (box6.x - circlePos.x) + (box6.y - circlePos.y) * (box6.y - circlePos.y) + (box6.z - circlePos.z) * (box6.z - circlePos.z);
	double bo7c = (box7.x - circlePos.x) * (box7.x - circlePos.x) + (box7.y - circlePos.y) * (box7.y - circlePos.y) + (box7.z - circlePos.z) * (box7.z - circlePos.z);
	double bo8c = (box8.x - circlePos.x) * (box8.x - circlePos.x) + (box8.y - circlePos.y) * (box8.y - circlePos.y) + (box8.z - circlePos.z) * (box8.z - circlePos.z);

	double circleLen = circleWidth * circleWidth;
	if (circleLen>=bo1c||circleLen>=bo2c||circleLen>=bo3c||circleLen>=bo4c|| circleLen >= bo5c || circleLen >= bo6c || circleLen >= bo7c || circleLen >= bo8c) {
		return true;
	}

	return false;
}

bool Collision::CircleCollision(Vector3 playerPos, Vector3 enemyPos, float playerWidth, float enemyWidth)
{
	float lol = { (enemyPos.x - playerPos.x) * (enemyPos.x - playerPos.x) + (enemyPos.y - playerPos.y) * (enemyPos.y - playerPos.y) + (enemyPos.z - playerPos.z) * (enemyPos.z - playerPos.z) };

	float redius = { (playerWidth + enemyWidth) * (playerWidth + enemyWidth) };


	if (lol <= redius) {
		return true;
	}

	return false;
}

bool Collision::CircleCollisionXZ(Vector3 playerPos, Vector3 enemyPos, float playerWidth, float enemyWidth)
{
	float lol = { (enemyPos.x - playerPos.x) * (enemyPos.x - playerPos.x) + (0 - 0) * (0 - 0) + (enemyPos.z - playerPos.z) * (enemyPos.z - playerPos.z) };

	float redius = { (playerWidth + enemyWidth) * (playerWidth + enemyWidth) };

	if (lol <= redius) {
		return true;
	}

	return false;
}
