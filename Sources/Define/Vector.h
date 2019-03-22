/**
* @file		Vector.h
* @brief	Simplification of vector related functions.
* @author	Koyama Tomoya
* @date		2019/02/24
*/
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
