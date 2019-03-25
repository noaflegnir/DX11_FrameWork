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


#include "BaseManager.h"

class Graphics;
// しーんまねーじゃの前方宣言
class Systems {

	enum class SYSTEM_NUM {
		DEBUG = 0,
		TEXTURE,
		MAX,
	};

	friend Windows;
	// その他からの参照が多い為、その他を参照させない
	static Systems* _system;


public:
	static Systems* Instance(void)		{ return _system; }
	Graphics*       GetGraphics(void)	{ return _graphics; }
	Windows*        GetWindow(void)		{ return _window; }

	Debug* GetDebug(void) { return (Debug*)_manager[(int)SYSTEM_NUM::DEBUG]; }


private:
	// Windowsクラスのみが使用
	Systems(Windows* window);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 自分自身が使う
	template<class T>
	bool Create(int i, string error);

	Graphics* _graphics;
	Windows*  _window;

	Interface* _manager[(int)SYSTEM_NUM::MAX];
};

