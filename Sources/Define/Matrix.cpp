#include "Matrix.h"

MATRIX::MATRIX()
{
	_11 = _12 = _13 = _14 =
	_21 = _22 = _23 = _24 =
	_31 = _32 = _33 = _34 =
	_41 = _42 = _43 = _44 = 0.0f;
}

MATRIX & MATRIX::Identity(void)
{
	_12 = _13 = _14 =
	_21 = _23 = _24 =
	_31 = _32 = _34 =
	_41 = _42 = _43 = 0.0f;

	_11 = _22 = _33 = _44 = 1.0f;
	return *this;
}

MATRIX MATRIX::operator + (const MATRIX& mtx)
{
	MATRIX t;
	t._11 = _11 + mtx._11;
	t._12 = _12 + mtx._12;
	t._13 = _13 + mtx._13;
	t._14 = _14 + mtx._14;
	t._21 = _21 + mtx._21;
	t._22 = _22 + mtx._22;
	t._23 = _23 + mtx._23;
	t._24 = _24 + mtx._24;
	t._31 = _31 + mtx._31;
	t._32 = _32 + mtx._32;
	t._33 = _33 + mtx._33;
	t._34 = _34 + mtx._34;
	t._41 = _41 + mtx._41;
	t._42 = _42 + mtx._42;
	t._43 = _43 + mtx._43;
	t._44 = _44 + mtx._44;
	return t;
}

MATRIX MATRIX::operator * (const float f)
{
	MATRIX t;
	t._11 = _11 * f;
	t._12 = _12 * f;
	t._13 = _13 * f;
	t._14 = _14 * f;
	t._21 = _21 * f;
	t._22 = _22 * f;
	t._23 = _23 * f;
	t._24 = _24 * f;
	t._31 = _31 * f;
	t._32 = _32 * f;
	t._33 = _33 * f;
	t._34 = _34 * f;
	t._41 = _41 * f;
	t._42 = _42 * f;
	t._43 = _43 * f;
	t._44 = _44 * f;
	return t;
}

MATRIX& MATRIX::operator *= (const MATRIX& mtx)
{
	MATRIX r;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			r.m[i][j] = m[i][0] * mtx.m[0][j] + m[i][1] * mtx.m[1][j] + m[i][2] * mtx.m[2][j] + m[i][3] * mtx.m[3][j];
		}
	}
	*this = r;

	return *this;
}

bool MATRIX::operator == (float n) const
{
	if (((_11 == n) && (_12 == n)) && ((_13 == n) && (_14 == n)))
	{
		if (((_21 == n) && (_22 == n)) && ((_23 == n) && (_24 == n)))
		{
			if (((_31 == n) && (_32 == n)) && ((_33 == n) && (_34 == n)))
			{
				if (((_41 == n) && (_42 == n)) && ((_43 == n) && (_44 == n)))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool MATRIX::operator != (float n) const
{
	return !operator==(n);
}

MATRIX & MATRIX::Transpose(const MATRIX & mtx)
{
	*this = mtx;

	_12 = mtx._21;
	_13 = mtx._31;
	_14 = mtx._41;

	_21 = mtx._12;
	_23 = mtx._32;
	_24 = mtx._42;

	_31 = mtx._13;
	_32 = mtx._23;
	_34 = mtx._43;

	_41 = mtx._14;
	_42 = mtx._24;
	_43 = mtx._34;

	return *this;
}

MATRIX & MATRIX::Billboard(const MATRIX & mtx)
{
	Transpose(mtx);

	_14 = _24 = _34 = 0;

	return *this;
}



