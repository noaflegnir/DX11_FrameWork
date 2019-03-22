#include "GuiManager.h"
#include "../Systems.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "../../Graphics/DirectX11/DirectX11.h"
#include "../../Windows/Windows.h"
#include "../Systems.h"

GuiManager::GuiManager(void)
	: BaseManager	(Systems::Instance())
	, _draw			(true)
{
}


GuiManager::~GuiManager(void)
{
}


HRESULT GuiManager::Init(void)
{
#ifdef _DEBUG

	const auto& _window = _systems->GetWindow();
	if (!_window) { return E_FAIL; }

	// コンテキスト生成
	ImGui::CreateContext();

	// ImGuiの初期化
	if (!ImGui_ImplWin32_Init(_window->GetHWND()))
	{
		MessageBox(NULL, "ImGuiの初期化に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	DirectX11* directX_ = static_cast<DirectX11*>(_window->GetGraphics());
	if (!directX_) { return E_FAIL; }

	if (!ImGui_ImplDX11_Init(directX_->GetDevice(), directX_->GetDeviceContext()))
	{
		MessageBox(NULL, "ImGuiの初期化に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	ImGui::StyleColorsDark();

	return S_OK;
#endif
}


void GuiManager::Uninit(void)
{
#ifdef _DEBUG
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}


void GuiManager::GuiUpdate(void)
{
#ifdef _DEBUG

	// 描画していない場合は更新せず
	if (!_draw) { return; }
	_draw = false;

	StartFrame();

	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::SetNextWindowPos(ImVec2(30, 30), 0, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(300, 100), 0);

	ImGui::Begin("Debug");
	ImGui::Spacing();
	ImGui::Text("FPS: %.2f", _systems->GetWindow()->GetFps());

	ImGui::SameLine();


	EndFrame();
#endif
}


void GuiManager::Update(void)
{
#ifdef _DEBUG
	GuiUpdate();
#endif
}


void GuiManager::Draw(void)
{
#ifdef _DEBUG
	if (_draw) { return; }
	_draw = true;
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

#endif
}


void GuiManager::StartFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void GuiManager::EndFrame()
{
	ImGui::End();
}
