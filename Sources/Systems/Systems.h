/**
* @file		Systems.h
* @brief	全システムの管理
* @author	小山智也
* @date		2019/03/19
*/
#pragma once

#include "../Define/Define.h"
#include "../Windows/Windows.h"

#include "Debug/Debug.h"
#include "TextureManager.h"
#include "Input/Input.h"
#include "ModelLoader/ModelLoader.h"


#include "BaseManager.h"

class Graphics;
// しーんまねーじゃの前方宣言
class Systems {

	enum class SYSTEM_NUM {
		DEBUG = 0,
		TEXTURE,
		INPUT,
		MODEL,
		MAX,
	};

	friend Windows;
	// その他からの参照が多い為、その他を参照させない
	static Systems* _system;


public:
	static Systems* Instance()		{ return _system;	}
	Graphics*       GetGraphics()	{ return _graphics;	}
	Windows*        GetWindow()		{ return _window;	}

	Debug* GetDebug() { return (Debug*)_manager[(int)SYSTEM_NUM::DEBUG]; }
	Input* GetInput() { return (Input*)_manager[(int)SYSTEM_NUM::INPUT]; }


private:
	Systems(Windows* window);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// 自分で使うやつ
	template<class T>
	bool Create(int i, string error);

	Graphics* _graphics;
	Windows*  _window;

	Interface* _manager[(int)SYSTEM_NUM::MAX];
};

