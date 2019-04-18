/**
* @file		DirectX11Wrapper.h
* @brief	DirectX11に関する処理の管理
* @author	小山智也
* @date		2019/03/18
*/
#pragma once

#include "DirectX11.h"
#include "../Wrapper.h"
#include "../../Systems/ModelLoader/PMXLoader/PMXLoader.h"

#include "../../TextureResource.h"


class DX11Wrapper : public Wrapper {

	friend DirectX11;

public:
	uint CreateVertexBuffer(const void* vertex, uint size, uint num) override;
	unsigned int CreateIndexBuffer(const WORD* vertex, unsigned int num) override;
	void ReleaseBuffer(unsigned int num) override; //@ FVF fvf

	/* @brief	2D描画開始	*/
	void BeginDrawCanvas() override;
	/* @brief	3D描画開始	*/
	void BeginDrawObject() override;

	/* @brief	描画終了	*/
	void EndDraw() override;

	/* @brif	ビュー行列の生成	*/
	MATRIX  CreateViewMatrix(VECTOR3 position, VECTOR3 at, VECTOR3 up);
	MATRIX  CreateProjectionMatrix(int fov, float aspect, float camera_near, float camera_far);

	void SetTexture(int stage, int texNum = -1, int modelNum = -1) override;

	/* @brief	テクスチャ読み込み	*/
	HRESULT LoadTexture(string filename, int texnum) override;
	/* @brief	テクスチャの解放	*/
	void ReleaseTexture(int texnum) override;
	/* @brief	テクスチャのサイズ取得	*/
	VECTOR2 GetTextureSize(int num) override;

	/* @brief	pmxファイルの読み込み*/
	HRESULT LoadpmxModel(PMXModelData& data, const wstring& file) override;
	void ReleasepmxModel() override;


	inline XMMATRIX    XM(const MATRIX&  m)
	{
		XMMATRIX temp;
		for (int i = 0; i < 4; ++i) { for (int j = 0; j < 4; ++j) { temp.r[i].m128_f32[j] = m.m[i][j]; } }
		return temp;
	}
	inline XMVECTORF32 XM(const VECTOR3& v) { XMVECTORF32 temp = { v.x, v.y, v.z, 1 }; return temp; }

	inline MATRIX  V(const XMMATRIX&    m)
	{
		MATRIX temp;
		for (int i = 0; i < 4; ++i) { for (int j = 0; j < 4; ++j) { temp.m[i][j] = m.r[i].m128_f32[j]; } }
		return temp;
	}
	inline VECTOR3 V(const XMVECTORF32& v) { return VECTOR3(v.f[0], v.f[1], v.f[2]); }


private:

	// pmx関係
	HRESULT GetPMXStringUTF16(ifstream& file, wstring& output);
	bool LoadPMX(PMXModelData& data, const wstring& file);

	void SetPMXModelData(PMXModelData& data, int i) override;

	struct SHADER_SCENE
	{
		MATRIX _view;
		MATRIX _proj;
	};
	// DirectX11のテクスチャ情報
	struct DX11Texture : public TextureData
	{
		ID3D11ShaderResourceView* _srv;
	};
	// DirectX11の頂点シェーダー
	struct VertexShader
	{
		ID3D11VertexShader* shader;
		ID3D11InputLayout*  layout;
	};
	// DirectX11のピクセルシェーダー
	struct PixelShader
	{
		ID3D11PixelShader*	shader;
		ID3D11SamplerState* sampler;
	};

	struct Shader
	{
		std::vector<uint> _vertexShader;
		std::vector<uint> _pixelShader;
		std::vector<uint> _constantBuffer;
	};

	DX11Wrapper(DirectX11* directX11);
	~DX11Wrapper() {}

	void Init()   override;
	void Uninit() override;

	DirectX11* _directX11;


	ID3D11DepthStencilState*   _depthState;
	ID3D11RasterizerState*     _rasterizerState;


	std::vector<VertexShader>  _vertexShader;
	std::vector<PixelShader>   _pixelShader;
	std::vector<ID3D11GeometryShader> _geometryShader;
	// シェーダとのデータのやりとりをするやつ
	std::vector<ID3D11Buffer*> _constantBuffer;

	// CanvasとObjectの2つ
	Shader _shader[2];


	DX11Texture _texture[TextureResource::MAX];
	std::vector<std::vector<DX11Texture>>	texture_;

	
	PMXModelData _pmxData[ModelResource::MAX]{};
};