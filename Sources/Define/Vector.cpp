#include "Vector.h"

// コンストラクタ
VECTOR3::VECTOR3(void) {}

VECTOR3::VECTOR3(float f)
{
	this->x = f;
	this->y = f;
	this->z = f;
}

VECTOR3::VECTOR3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

VECTOR3& VECTOR3::operator = (const VECTOR2& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = 0;
	return *this;
}

VECTOR3& VECTOR3::operator += (const VECTOR3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

VECTOR3& VECTOR3::operator -= (const VECTOR3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

VECTOR3& VECTOR3::operator *= (float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	return *this;
}

VECTOR3& VECTOR3::operator /= (float f)
{
	float inv = 1.0f / f;
	this->x *= inv;
	this->y *= inv;
	this->z *= inv;
	return *this;
}

VECTOR3& VECTOR3::operator + (void)
{
	(this->x < 0) ? this->x *= -1 : this->x *= 1;
	(this->y < 0) ? this->y *= -1 : this->y *= 1;
	(this->z < 0) ? this->z *= -1 : this->z *= 1;
	return *this;
}

VECTOR3& VECTOR3::operator - (void)
{
	*this *= -1;
	return *this;
}

VECTOR3 VECTOR3::operator + (const VECTOR3& v) const
{
	return VECTOR3(this->x + v.x, this->y + v.y, this->z + v.z);
}

VECTOR3 VECTOR3::operator - (const VECTOR3& v) const
{
	return VECTOR3(this->x - v.x, this->y - v.y, this->z - v.z);
}

VECTOR3 VECTOR3::operator * (float f) const
{
	return VECTOR3(this->x * f, this->y * f, this->z * f);
}

VECTOR3 VECTOR3::operator * (const VECTOR3& v) const
{
	return VECTOR3(this->x * v.x, this->y * v.y, this->z * v.z);
}

VECTOR3 VECTOR3::operator / (float f) const
{
	float inv = 1.0f / f;
	return VECTOR3(this->x * inv, this->y * inv, this->z * inv);
}

VECTOR3 VECTOR3::operator / (const VECTOR3& v) const
{
	return VECTOR3(this->x / v.x, this->y / v.y, this->z / v.z);
}

bool VECTOR3::operator == (const VECTOR3& v)
{
	return (this->x == v.x && this->y == v.y && this->z == v.z) ? true : false;
}

bool VECTOR3::operator != (float f)
{
	return (this->x != f || this->y != f || this->z != f) ? true : false;
}

bool VECTOR3::operator != (const VECTOR3& v)
{
	return (this->x != v.x || this->y != v.y || this->z != v.z) ? true : false;
}

bool VECTOR3::operator != (std::nullptr_t t)const
{
	return (this != t) ? true : false;
}