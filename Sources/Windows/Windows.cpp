#include "Windows.h"
#include <Windows.h>
#include "../Graphics/DirectX11/DirectX11.h"
#include "../Systems/Systems.h"
#include <time.h>
#include <tchar.h>

Windows::Windows()
	: _graphics		(nullptr)
	, _systems		(nullptr)
	, _hWnd			(nullptr)
	, _hInstance	(nullptr)
	, _nowTime		(0)
	, _oldTime		(0)
	, _timeFPS		(0)
	, _counterFPS	(0)
	, _fps			(0)
{
}

// ����������
HRESULT Windows::Init(HINSTANCE Instance, int cmdShow)
{
	_hInstance = Instance;

	// �E�B���h�E���̐ݒ�
	SetWindowParam();

	// �E�B���h�E�̐���
	SetWindow(cmdShow);

	// �O���t�B�b�N�X�n�̏�����
	_graphics = nullptr;

	// �Q�[���V�X�e���̏�����
	_systems = nullptr;

	return S_OK;
}

// �㏈��
WPARAM Windows::Uninit(void)
{
	// �V�X�e���n�̉��
	if (_systems)
	{
		_systems->Uninit();
	}
	DeleteThis(_systems);

	// �O���t�B�b�N�X�n�̉��
	if (_graphics)
	{
		_graphics->Uninit();
	}
	DeleteThis(_graphics);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, _wcex.hInstance);

	return _msg.wParam;
}

// �X�V����
bool Windows::Update(void)
{
	if (_graphics == nullptr)
	{
		return InitGame();
	}
	// �V�X�e���n�̍X�V����
	_systems->Update();

	return false;
}

// �`�揈��
void Windows::Draw(void)
{
	if (_graphics == nullptr) { return; }
	if (SUCCEEDED(_graphics->DrawBegin()))
	{
		// �V�X�e���n�̕`��
		_systems->Draw();
	
		_graphics->DrawEnd();
	}
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// WndProc
LRESULT CALLBACK Windows::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			int nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}

		default:
			break;
		}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Windows::SetWindowParam(void)
{
	_wcex.cbSize = sizeof(WNDCLASSEX);
	_wcex.style = CS_VREDRAW | CS_HREDRAW;
	_wcex.lpfnWndProc = WndProc;
	_wcex.cbClsExtra = 0;
	_wcex.cbWndExtra = 0;
	_wcex.hInstance = _hInstance;
	_wcex.hIcon = NULL;
	_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	_wcex.lpszMenuName = NULL;
	_wcex.lpszClassName = CLASS_NAME;
	_wcex.hIconSm = NULL;
	
	RegisterClassEx(&_wcex);

	//UnregisterClass(_T("ImGui Example"), _wcex.hInstance);
}

// �E�B���h�E�̐���
void Windows::SetWindow(int CmdShow)
{
	RECT dr_;
	GetWindowRect(GetDesktopWindow(), &dr_);

	int w_ = SCREEN_WIDTH;
	int h_ = SCREEN_HEIGHT;

	RECT wr_ = { 0, 0, w_, h_ };
	AdjustWindowRect(&wr_, WINDOW_STYLE, false);

	int width_  = wr_.right - wr_.left;
	int	height_ = wr_.bottom - wr_.top;

	// �n���h������
	_hWnd = CreateWindowEx(0,
				CLASS_NAME,
				WINDOW_NAME,
				WINDOW_STYLE,
				WindowCenter(dr_.right, wr_.right),
				WindowCenter(dr_.bottom, wr_.bottom),
				width_,
				height_,
				NULL,
				NULL,
				_hInstance,
				NULL
	);

	// �E�B���h�E�\��
	ShowWindow(_hWnd, CmdShow);

	// �E�B���h�E�X�V
	UpdateWindow(_hWnd);
}

// ���b�Z�[�W�v���Z�X
bool Windows::MsgProcess(void)
{
	//�E�B���h�E�������
	if (_msg.message == WM_QUIT)
	{
		return true;
	}
	//����ȊO
	else
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
	return false;
}

// �Q�[�����[�v
void Windows::Loop(DWORD Fps)
{
	timeBeginPeriod(1);				// timeGetTIme�̐��x���グ��

	for (;;)
	{
		//���b�Z�[�W����
		if (PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (MsgProcess()) { break; }
		}
		//�Q�[������
		else
		{
			// �Q�[���X�V����
			_nowTime = timeGetTime();

			if ((_nowTime - _timeFPS) >= 500)
			{
				_fps = _counterFPS * 1000.f / (_nowTime - _timeFPS);
				_timeFPS = _nowTime;
				_counterFPS = 0;
			}

			if (((_nowTime - _oldTime) * Fps) >= 1000)
			{// �X�V�A�`��

				if (this->Update()) { break; }

				// �`�揈��
				this->Draw();

				_oldTime = _nowTime;
				_counterFPS++;
			}
		}
	}

	timeEndPeriod(1);
}

// �Q�[���n�̏���������
bool Windows::InitGame()
{
	// �O���t�B�b�N�X�n
	_graphics = new DirectX11(this);
	if (FAILED(_graphics->Init())) { return true; }
	
	// �V�X�e���n
	_systems = new Systems(this);
	if (FAILED(_systems->Init())) { return true; }

	return false;
}
