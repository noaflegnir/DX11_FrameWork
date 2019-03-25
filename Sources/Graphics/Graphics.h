/**
* @file		Graphics.h
* @brief	�O���t�B�b�N�X�n
* @author	���R�q��
* @date		2019/03/17
*/
#pragma once

#include "Wrapper.h"

class Graphics {

	friend class Windows;
	friend class Systems;

public:
	static constexpr int WIDTH = 1280;
	static constexpr int HEIGHT = 720;

	Windows* GetWindow(void) { return _window; }

	inline Wrapper*	GetWrapper(void) { return _wrapper; }

protected:
	Graphics(Windows* window) { _window = window; }

	virtual HRESULT Init(void) = 0;
	virtual void	Uninit(void) = 0;
	virtual HRESULT DrawBegin(void) = 0;
	virtual void	DrawEnd(void) = 0;

	virtual void    ClearRenderer(void) {}	// ��ʂ̃N���A

	Windows* _window;		// �E�B���h�E�N���X�ւ̃|�C���^
	Wrapper* _wrapper;

};