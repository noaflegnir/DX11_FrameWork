#pragma once

#pragma warning (disable : 4201)	// �s���struct�̖��O�Ȃ�����W���Ōx�����o��
struct MATRIX;

struct MATRIX {
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};

	MATRIX();

	MATRIX& Identity(void);

	MATRIX operator + (const MATRIX& mtx);
	MATRIX operator * (const float f);
	MATRIX& operator *= (const MATRIX& mtx);
	bool operator == (float n) const;
	bool operator != (float n) const;

	MATRIX& Transpose(const MATRIX& mtx);		// �]�u�s��
	MATRIX& Billboard(const MATRIX& mtx);

};