/**
* @file		Vector.h
* @brief	Simplification of vector related functions.
* @author	Koyama Tomoya
* @date		2019/02/24
*/

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct VECTOR2
{
public:
	float x, y;

	VECTOR2(){}
	VECTOR2(float v)
	{
		this->x = v;
		this->y = v;
	}

	VECTOR2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	VECTOR2& operator += (VECTOR2& v)
	{
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	VECTOR2& operator -= (VECTOR2& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}

	VECTOR2& operator *= (float f)
	{
		this->x *= f;
		this->y *= f;
		return *this;
	}

	VECTOR2& operator /= (float f)
	{
		float inv = 1.0f / f;
		this->x *= inv;
		this->y *= inv;
		return *this;
	}

	VECTOR2& operator + ()
	{
		(this->x < 0) ? this->x *= -1 : this->x *= 1;
		(this->y < 0) ? this->y *= -1 : this->y *= 1;
		return *this;
	}

	VECTOR2& operator - ()
	{
		(this->x > 0) ? this->x *= -1 : this->x *= 1;
		(this->y > 0) ? this->y *= -1 : this->y *= 1;
		return *this;
	}

	VECTOR2 operator + (VECTOR2& v)
	{
		return VECTOR2(x + v.x, y + v.y);
	}

	VECTOR2 operator - (VECTOR2& v)
	{
		return VECTOR2(x - v.x, y - v.y);
	}

	VECTOR2 operator * (float f)
	{
		return VECTOR2(x * f, y * f);
	}

	VECTOR2 operator / (float f)
	{
		float inv = 1.0f / f;
		return VECTOR2(x * inv, y * inv);
	}

	bool operator == (VECTOR2 v)
	{
		return (this->x == v.x && this->y == v.y) ? true : false;
	}

	bool operator != (VECTOR2 v)
	{
		return (this->x != v.x || this->y != v.y) ? true : false;
	}

};

struct VECTOR3
{
public:
	float x, y, z;

	/* @brief	コンストラクタ		*/
	VECTOR3();

	/* @brief	コンストラクタ
	* @param	(f)		初期化値	*/
	VECTOR3(float f);

	/* @brief	コンストラクタ
	* @param	(x)		xの初期化値
	* @param	(y)		yの初期化値
	* @param	(z)		zの初期化値	*/
	VECTOR3(const float x, const float y, const float z);

	template<class T1, class T2, class T3>
	VECTOR3(const T1 x, const T2 y, const T3 z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {}

	// 演算子のオーバーロード
	VECTOR3& operator = (const VECTOR2& v);

	VECTOR3& operator += (const VECTOR3& v);
	VECTOR3& operator -= (const VECTOR3& v);
	VECTOR3& operator *= (float f);
	VECTOR3& operator /= (float f);

	VECTOR3& operator + ();
	VECTOR3& operator - ();

	VECTOR3 operator + (const VECTOR3& v) const;
	VECTOR3 operator - (const VECTOR3& v) const;
	VECTOR3 operator * (float f) const;
	VECTOR3 operator * (const VECTOR3& v) const;
	VECTOR3 operator / (float f) const;
	VECTOR3 operator / (const VECTOR3& v) const;

	bool operator == (const VECTOR3& v);
	bool operator != (float f);
	bool operator != (const VECTOR3& v);
	bool operator != (std::nullptr_t t)const;

	operator float*() { return &x; }
};

struct VECTOR4
{
public:
	float x, y, z, w;

	// コンストラクタ
	VECTOR4(void);
	VECTOR4(float f);
	VECTOR4(float x, float y, float z, float w);

	// 演算子のオーバーロード
	VECTOR4& operator += (const VECTOR4& v);
	VECTOR4& operator -= (const VECTOR4& v);
	VECTOR4& operator *= (float f);
	VECTOR4& operator /= (float f);

	VECTOR4& operator + (void);
	VECTOR4& operator - (void);
	VECTOR4 operator + (const VECTOR4& v) const;
	VECTOR4 operator - (const VECTOR4& v) const;
	VECTOR4 operator * (float f) const;
	VECTOR4 operator / (float f) const;

	bool operator == (const VECTOR4& v);
	bool operator != (const VECTOR4& v);
	bool operator != (std::nullptr_t t)const;
};
