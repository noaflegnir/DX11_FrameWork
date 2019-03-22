/**
* @file		Windows.h
* @brief	�E�B���h�E
* @author	���R�q��
* @date		2019/03/17
*/
#pragma once

#include <Windows.h>
#include "API.h"
#include "../Graphics/Graphics.h"

class Systems;
class Windows {

	static constexpr char* CLASS_NAME = "Game";			//! �N���X��
	static constexpr char* WINDOW_NAME = "DX11_Sample";	//! �E�B���h�E��
	static constexpr int   WINDOW_STYLE = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX;	// �E�B���h�E�X�^�C��				// FPS�̐ݒ�
	//#define CLASS_NAME "sample"
	//#define WINDOW_NAME "Magic Enchant Ver2.0"

	static constexpr int  SCREEN_WIDTH = 1280;	// @def	�E�B���h�E�T�C�Y��
	static constexpr int  SCREEN_HEIGHT = 720;	// @def	�E�B���h�E�T�C�Y����

public:

	static constexpr int  FPS = 60;

	/* @brief	�R���X�g���N	*/
	Windows();
	/* @brief	�f�X�g���N�^	*/
	~Windows(){}

	// Getter
	float     GetFps(void) { return _fps; }	// ���ۂ�FPS
	HWND      GetHWND(void) { return _hWnd; }	// HWND
	MSG       GetMsg(void) { return _msg; }	// MSG
	HINSTANCE GetHInstance(void) { return _hInstance; }	// HINSTANCE

	Graphics* GetGraphics(void) { return _graphics; }

	/* @brief	������
	 * @param	(Instance) �n���h��
	 * @parsm	(cmdshow) �n���h���@
	 * @return	���������s��		*/
	HRESULT Init(HINSTANCE Instance, int CmdShow);


	/* @brief	�Q�[�����[�v
	 * @param	(Fps) FPS�l			*/
	void Loop(DWORD Fps);


	/* @brief	���
	 * @return	wparam				*/
	WPARAM  Uninit(void);


private:
	/* @brief	�X�V
	 * @return �������̗L��			*/
	bool Update();

	/* @brief	�`��				*/
	void Draw();

	/* @brief	�E�B���h�E�̐ݒ�	*/
	void SetWindowParam();

	/* @brief	�E�B���h�E�̐���
	 * @param	(CmdShow) �E�B���h�E�������̃t���O	*/
	void SetWindow(int CmdShow);

	/* @brief	���b�Z�[�W�v���Z�X	*/
	bool MsgProcess();

	/* @brief	�Q�[���̏�����		*/
	bool InitGame();

	Graphics*	_graphics;
	Systems*	_systems;


	HWND		_hWnd;
	HINSTANCE	_hInstance;
	MSG			_msg;
	WNDCLASSEX	_wcex;


	int	_nowTime;
	int _oldTime;
	int _timeFPS;
	int _counterFPS;
	float _fps;

	inline LONG WindowCenter(LONG dr, LONG wr) { return Hf(dr - wr) > 0 ? Hf(dr - wr) : 0; }


	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


};