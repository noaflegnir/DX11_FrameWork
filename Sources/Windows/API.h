/**
* @file		API.h
* @brief	API�Q
* @author	���R�q��
* @date		2019/03/17
*/
#pragma once

#include <crtdbg.h>
#include "../Define/Color.h"
#include "../Define/Define.h"

//! @def	DirectX�n�̃}�N���Ē�`�̌x����\��
#pragma warning(disable: 4005)
//! @def	XNAMath�̏k���ϊ��x���̔�\��
#pragma warning(disable: 4838)
//! @def	�E�Ӓl�̃N���X�����Ӓl�Ɏg�p�����Ƃ��̌x���̔�\��
#pragma warning(disable: 4238)
//! @def	��W���̊g���@�\�̎g�p�ɂ��x����\�� (enmu���薼)
#pragma warning(disable: 4482)


// ���������[�N�������Ƀf�o�b�K�ɏo�͂�����e���킩��₷������
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#define NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW  new
#endif
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#define NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW  new
#endif


//! @def	�^�`�F�b�N
#define STRICT

#define _CRTDBG_MAP_ALLOC 



