#include "DirectX11Wrapper.h"
#include "../../Windows/Windows.h"
#include <D3DX11tex.h>



DX11Wrapper::DX11Wrapper(DirectX11* directX)
	: _directX11 (directX)
{
}

HRESULT DX11Wrapper::Init()
{
	return E_NOTIMPL;
}

void DX11Wrapper::Uninit()
{

}

unsigned int DX11Wrapper::CreateVertexBuffer(const void * vertex, unsigned int size, unsigned int num)
{
	return 0;
}

unsigned int DX11Wrapper::CreateIndexBuffer(const WORD * vertex, unsigned int num)
{
	return 0;
}

void DX11Wrapper::ReleaseBuffer(unsigned int num)
{
}

void DX11Wrapper::BeginDrawCanvas()
{
}

void DX11Wrapper::BeginDrawObject()
{
}

void DX11Wrapper::EndDraw()
{
}

void DX11Wrapper::SetTexture(int stage, int texNum, int modelNum)
{
	const auto& context_ = _directX11->GetDeviceContext();
	if (!context_) { return; }

	if (texNum < 0)
	{
		ID3D11ShaderResourceView* temp = nullptr;
		context_->PSSetShaderResources(stage, 1, &temp);
	}
	else
	{
		context_->PSSetShaderResources(stage, 1, &_texture[texNum]._srv);
	}

}

HRESULT DX11Wrapper::LoadTexture(string filename, int texnum)
{

	string fn_;
	fn_ = filename;

	if (texture_.size() == 0) { texture_.resize(1); }
	DX11Texture temp;

	std::wstring name(filename.begin(), filename.end());
	ID3D11Resource* descOriginal_;

	// ファイルを開く
	HRESULT hr = DirectX::CreateWICTextureFromFile(_directX11->GetDevice(), name.c_str(), &descOriginal_, &temp._srv);

	if (FAILED(hr))
	{
		string error_ = "が開けませんでした";
		fn_ += error_;

		MessageBox(_directX11->GetWindow()->GetHWND(), fn_.c_str(), "エラー", MB_OK);
		return E_FAIL;
	}

	// テクスチャサイズの取得
	D3D11_TEXTURE2D_DESC desc_;
	static_cast<ID3D11Texture2D*>(descOriginal_)->GetDesc(&desc_);
	ReleaseThis(descOriginal_);

	temp.size.x = (float)desc_.Width;
	temp.size.y = (float)desc_.Height;

	_texture[texnum] = temp;

	// サンプラー作成はピクセルシェーダ作成時に

	return S_OK;
}

void DX11Wrapper::ReleaseTexture(int texnum)
{
	MessageBox(_directX11->GetWindow()->GetHWND(), "よばれてる", "エラー", MB_OK);

	// シェーダーリソースビューの解放
	ReleaseThis(_texture[texnum]._srv);
}

VECTOR2 DX11Wrapper::GetTextureSize(int num)
{
	return VECTOR2();
}
