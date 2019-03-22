/**
* @file		API.h
* @brief	API群
* @author	小山智也
* @date		2019/03/17
*/
#pragma once

#include <crtdbg.h>
#include "../Define/Color.h"
#include "../Define/Define.h"

//! @def	DirectX系のマクロ再定義の警告非表示
#pragma warning(disable: 4005)
//! @def	XNAMathの縮小変換警告の非表示
#pragma warning(disable: 4838)
//! @def	右辺値のクラスが左辺値に使用されるときの警告の非表示
#pragma warning(disable: 4238)
//! @def	非標準の拡張機能の使用による警告非表示 (enmu限定名)
#pragma warning(disable: 4482)


// メモリリーク発生時にデバッガに出力する内容をわかりやすくする
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


//! @def	型チェック
#define STRICT

#define _CRTDBG_MAP_ALLOC 



