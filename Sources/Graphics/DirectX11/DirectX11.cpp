#include "DirectX11.h"
#include "DirectX11Wrapper.h"

DirectX11::DirectX11(Windows* window)
	: Graphics			(window)
	, _swapChain		(nullptr)
	, _device			(nullptr)
	, _deviceContext	(nullptr)
	, _renderTargetView (nullptr)
	, _depthStencilView	(nullptr)
{}

HRESULT DirectX11::Init()
{
	SetDevice();

	// ���b�p�[�̏�����
	_wrapper = new DX11Wrapper(this);
	if (_wrapper)
	{
		_wrapper->Init();
	}

	return S_OK;
}

void DirectX11::Uninit()
{
	// ���b�p�[�̏���
	_wrapper->Uninit();
	DeleteThis(_wrapper);

	ReleaseThis(_renderTargetView);
	ReleaseThis(_swapChain);
	ReleaseThis(_deviceContext);
	ReleaseThis(_device);
}

// �`��J�n
HRESULT DirectX11::DrawBegin()
{
	ClearRenderer();

	return S_OK;
}

// �`��I��
void DirectX11::DrawEnd()
{
	_swapChain->Present(1, 0);
}

void DirectX11::ClearRenderer(void)
{

	_deviceContext->ClearRenderTargetView(_renderTargetView, (float*)COLOR_RGBA::RGBA(0, 150, 255, 255));
	_deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

HRESULT DirectX11::InitAll()
{
	return E_NOTIMPL;
}

bool DirectX11::SetDevice()
{
	HRESULT hr_;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	//�f�o�C�X�̐���
	hr_ = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &_device, NULL, &_deviceContext);
	if (FAILED(hr_)) { return false; }

	//�g�p�\��MSAA���擾
	DXGI_SAMPLE_DESC MSAA_;
	MSAA_.Count = 0;
	MSAA_.Quality = 0;
	for (int i = 0; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; ++i)
	{
		UINT quality;
		hr_ = _device->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &quality);
		if (SUCCEEDED(hr_))
		{
			if (0 < quality)
			{
				MSAA_.Count = i;
				MSAA_.Quality = quality - 1;
			}
		}
	}

	//�C���^�[�t�F�[�X�擾
	IDXGIDevice1* DXGI_ = nullptr;
	hr_ = _device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&DXGI_);
	if (FAILED(hr_)) { return false; }

	//�A�_�v�^�[�擾
	IDXGIAdapter* adapter_ = nullptr;
	hr_ = DXGI_->GetAdapter(&adapter_);
	if (FAILED(hr_)) { return false; }

	//�t�@�N�g���[�擾
	IDXGIFactory* DXGIFactory_ = nullptr;
	adapter_->GetParent(__uuidof(IDXGIFactory), (void**)&DXGIFactory_);
	if (!DXGIFactory_) { return false; }

	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC sd_;
	ZeroMemory(&sd_, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd_.BufferCount = 1;
	sd_.BufferDesc.Width = Graphics::WIDTH;
	sd_.BufferDesc.Height = Graphics::HEIGHT;
	sd_.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd_.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd_.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd_.SampleDesc = MSAA_;

	// ���t���b�V�����[�g 60fps 
	sd_.BufferDesc.RefreshRate.Numerator = 60;		// ���q
	sd_.BufferDesc.RefreshRate.Denominator = 1;		// ����
	sd_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd_.OutputWindow = _window->GetHWND();
	sd_.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd_.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd_.Windowed = true;

	hr_ = DXGIFactory_->CreateSwapChain(_device, &sd_, &_swapChain);
	if (FAILED(hr_)) { return false; }

	ReleaseThis(DXGIFactory_);
	ReleaseThis(adapter_);
	ReleaseThis(DXGI_);

	//�����_�[�^�[�Q�b�g�r���[�̍쐬
	ID3D11Texture2D *backBuffer_;
	_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer_);
	_device->CreateRenderTargetView(backBuffer_, NULL, &_renderTargetView);
	backBuffer_->Release();

	ID3D11Texture2D* depthTexture_ = nullptr;
	D3D11_TEXTURE2D_DESC txDesc_;
	ZeroMemory(&txDesc_, sizeof(txDesc_));
	txDesc_.Width = Graphics::WIDTH;
	txDesc_.Height = Graphics::HEIGHT;
	txDesc_.MipLevels = 1;
	txDesc_.ArraySize = 1;
	txDesc_.Format = DXGI_FORMAT_D32_FLOAT;
	txDesc_.SampleDesc = MSAA_;
	txDesc_.Usage = D3D11_USAGE_DEFAULT;
	txDesc_.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc_.CPUAccessFlags = 0;
	txDesc_.MiscFlags = 0;
	hr_ = _device->CreateTexture2D(&txDesc_, NULL, &depthTexture_);
	if (FAILED(hr_)) { return false; }

	//�X�e���V���^�[�Q�b�g�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc_;
	depthStencilViewDesc_.Format = txDesc_.Format;
	depthStencilViewDesc_.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc_.Flags = 0;
	if (FAILED(_device->CreateDepthStencilView(depthTexture_, &depthStencilViewDesc_, &_depthStencilView)))
	{
		return false;
	}

	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp_;
	vp_.Width = Graphics::WIDTH;
	vp_.Height = Graphics::HEIGHT;
	vp_.MinDepth = 0.0f;
	vp_.MaxDepth = 1.0f;
	vp_.TopLeftX = 0;
	vp_.TopLeftY = 0;
	_deviceContext->RSSetViewports(1, &vp_);

	return true;
}
