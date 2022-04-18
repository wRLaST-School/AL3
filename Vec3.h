#pragma once
#include <DirectXMath.h>
class Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float x, float y, float z);

	//Sqrt���Ă΂��
	Vec3& SetLength(float l);

	const Vec3 operator+(const Vec3& v2) const;
			 
	const Vec3 operator-(const Vec3& v2) const;
			 
	const Vec3 operator*(float mul) const;
			 
	const Vec3 operator/(float div) const;

	Vec3& operator +=(const Vec3& v2);

	Vec3& operator -=(const Vec3& v2);

	Vec3& operator *=(float mul);

	Vec3& operator /=(float div);

	//Sqrt���Ă΂��
	Vec3& Norm();

	//Sqrt���Ă΂��
	Vec3 GetNorm() const;

	float GetLength() const;

	float GetSquaredLength() const;

	DirectX::XMFLOAT3 GetXMFloat() const;

	void CalcWithMatLH(DirectX::XMMATRIX mat);

};

Vec3 XMFloatToVec3(DirectX::XMFLOAT3 mat);