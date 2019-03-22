/**
* @file		Graphics.h
* @brief	�O���t�B�b�N�X�n
* @author	���R�q��
* @date		2019/03/17
*/
#pragma once

#include "../Windows/Windows.h"

class Graphics {

	friend class Windows;
	friend class Systems;

public:
	static constexpr int WIDTH = 1280;
	static constexpr int HEIGHT = 720;

	Windows* GetWindow(void) { return window_; }		// �E�B���h�E�N���X�̎󂯓n��

protected:
	Graphics(Windows* window) { window_ = window; }

	virtual HRESULT Init(void) = 0;	// ����������
	virtual void	Uninit(void) = 0;	// �㏈��
	virtual HRESULT DrawBegin(void) = 0;	// �`��J�n
	virtual void	DrawEnd(void) = 0;	// �`��I��

	virtual void    ClearRenderer(void) {}	// ��ʂ̃N���A

	Windows* window_;		// �E�B���h�E�N���X�ւ̃|�C���^

};