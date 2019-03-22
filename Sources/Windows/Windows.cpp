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

// 初期化処理
HRESULT Windows::Init(HINSTANCE Instance, int cmdShow)
{
	_hInstance = Instance;

	// ウィンドウ情報の設定
	SetWindowParam();

	// ウィンドウの生成
	SetWindow(cmdShow);

	// グラフィックス系の初期化
	_graphics = nullptr;

	// ゲームシステムの初期化
	_systems = nullptr;

	return S_OK;
}

// 後処理
WPARAM Windows::Uninit(void)
{
	// システム系の解放
	if (_systems)
	{
		_systems->Uninit();
	}
	DeleteThis(_systems);

	// グラフィックス系の解放
	if (_graphics)
	{
		_graphics->Uninit();
	}
	DeleteThis(_graphics);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, _wcex.hInstance);

	return _msg.wParam;
}

// 更新処理
bool Windows::Update(void)
{
	if (_graphics == nullptr)
	{
		return InitGame();
	}
	// システム系の更新処理
	_systems->Update();

	return false;
}

// 描画処理
void Windows::Draw(void)
{
	if (_graphics == nullptr) { return; }
	if (SUCCEEDED(_graphics->DrawBegin()))
	{
		// システム系の描画
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
			int nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
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

// ウィンドウの生成
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

	// ハンドル生成
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

	// ウィンドウ表示
	ShowWindow(_hWnd, CmdShow);

	// ウィンドウ更新
	UpdateWindow(_hWnd);
}

// メッセージプロセス
bool Windows::MsgProcess(void)
{
	//ウィンドウを閉じた時
	if (_msg.message == WM_QUIT)
	{
		return true;
	}
	//それ以外
	else
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
	return false;
}

// ゲームループ
void Windows::Loop(DWORD Fps)
{
	timeBeginPeriod(1);				// timeGetTImeの精度を上げる

	for (;;)
	{
		//メッセージ処理
		if (PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (MsgProcess()) { break; }
		}
		//ゲーム処理
		else
		{
			// ゲーム更新処理
			_nowTime = timeGetTime();

			if ((_nowTime - _timeFPS) >= 500)
			{
				_fps = _counterFPS * 1000.f / (_nowTime - _timeFPS);
				_timeFPS = _nowTime;
				_counterFPS = 0;
			}

			if (((_nowTime - _oldTime) * Fps) >= 1000)
			{// 更新、描画

				if (this->Update()) { break; }

				// 描画処理
				this->Draw();

				_oldTime = _nowTime;
				_counterFPS++;
			}
		}
	}

	timeEndPeriod(1);
}

// ゲーム系の初期化処理
bool Windows::InitGame()
{
	// グラフィックス系
	_graphics = new DirectX11(this);
	if (FAILED(_graphics->Init())) { return true; }
	
	// システム系
	_systems = new Systems(this);
	if (FAILED(_systems->Init())) { return true; }

	return false;
}
