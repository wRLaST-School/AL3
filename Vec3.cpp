#include "Vec3.h"
#include <math.h>

Vec3::Vec3() :x(0), y(0), z(0)
{
}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vec3& Vec3::SetLength(float l)
{
	float len2 = this->GetLength();
	float mul = l / len2;
	x *= mul;
	y *= mul;
	z *= mul;

	return *this;
}

const Vec3 Vec3::operator+(const Vec3& v2) const
{
	return Vec3(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

const Vec3 Vec3::operator-(const Vec3& v2) const
{
	return Vec3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

const Vec3 Vec3::operator*(float mul) const
{
	return Vec3(this->x * mul, this->y * mul, this->z * mul);
}

const Vec3 Vec3::operator/(float div) const
{
	return Vec3(this->x / div, this->y / div, this->z / div);
}

Vec3& Vec3::operator+=(const Vec3& v2)
{
	this->x += v2.x;
	this->y += v2.y;
	this->z += v2.z;

	return *this;
}

Vec3& Vec3::operator-=(const Vec3& v2)
{
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;

	return *this;
}

Vec3& Vec3::operator*=(float mul)
{
	this->x *= mul;
	this->y *= mul;
	this->z *= mul;

	return *this;
}

Vec3& Vec3::operator/=(float div)
{
	this->x /= div;
	this->y /= div;
	this->z /= div;

	return *this;
}

Vec3& Vec3::Norm()
{
	float l = this->GetLength();
	if (l) {
		this->x /= l;
		this->y /= l;
		this->z /= l;
	}
	else {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	return *this;
}

Vec3 Vec3::GetNorm() const
{
	float l = this->GetLength();
	if (l)
		return Vec3(this->x / l, this->y / l, this->z / l);
	else
		return Vec3();
}

float Vec3::GetLength() const
{
	return sqrt(this->GetSquaredLength());
}

float Vec3::GetSquaredLength() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

DirectX::XMFLOAT3 Vec3::GetXMFloat() const
{
	return DirectX::XMFLOAT3(x, y, z);
}

void Vec3::CalcWithMatLH(DirectX::XMMATRIX mat)
{
	Vec3 result;
	result.x = mat.r[0].m128_f32[0] * x + mat.r[1].m128_f32[0] * y + mat.r[2].m128_f32[0] * z;
	result.y = mat.r[0].m128_f32[1] * x + mat.r[1].m128_f32[1] * y + mat.r[2].m128_f32[1] * z;
	result.z = mat.r[0].m128_f32[2] * x + mat.r[1].m128_f32[2] * y + mat.r[2].m128_f32[2] * z;

	*this = result;
}

Vec3 XMFloatToVec3(DirectX::XMFLOAT3 mat)
{
	return Vec3(mat.x, mat.y, mat.z);
}
