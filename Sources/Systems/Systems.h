/**
* @file		Systems.h
* @brief	�S�V�X�e���̊Ǘ�
* @author	���R�q��
* @date		2019/03/19
*/
#pragma once

#include "../Define/Define.h"
#include "../Windows/Windows.h"

#include "Debug/Debug.h"
#include "TextureManager.h"


#include "BaseManager.h"

class Graphics;
// ���[��܂ˁ[����̑O���錾
class Systems {

	enum class SYSTEM_NUM {
		DEBUG = 0,
		TEXTURE,
		MAX,
	};

	friend Windows;
	// ���̑�����̎Q�Ƃ������ׁA���̑����Q�Ƃ����Ȃ�
	static Systems* _system;


public:
	static Systems* Instance(void)		{ return _system; }
	Graphics*       GetGraphics(void)	{ return _graphics; }
	Windows*        GetWindow(void)		{ return _window; }

	Debug* GetDebug(void) { return (Debug*)_manager[(int)SYSTEM_NUM::DEBUG]; }


private:
	// Windows�N���X�݂̂��g�p
	Systems(Windows* window);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �������g���g��
	template<class T>
	bool Create(int i, string error);

	Graphics* _graphics;
	Windows*  _window;

	Interface* _manager[(int)SYSTEM_NUM::MAX];
};

