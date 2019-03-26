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
	unsigned int CreateVertexBuffer(const void* vertex, unsigned int size, unsigned int num) override;
	unsigned int CreateIndexBuffer(const WORD* vertex, unsigned int num) override;
	void ReleaseBuffer(unsigned int num) override; //@ FVF fvf

	/* @brief	2D描画開始	*/
	void BeginDrawCanvas() override;
	/* @brief	3D描画開始	*/
	void BeginDrawObject() override;

	/* @brief	描画終了	*/
	void EndDraw() override;

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


private:

	// pmx関係
	HRESULT GetPMXStringUTF16(ifstream& file, wstring& output);
	bool LoadPMX(PMXModelData& data, const wstring& file);

	void SetPMXModelData(PMXModelData data, int i) override;

	// DirectX11のテクスチャ情報
	struct DX11Texture : public TextureData
	{
		ID3D11ShaderResourceView* _srv;
	};

	DX11Wrapper(DirectX11* directX11);
	~DX11Wrapper() {}

	HRESULT Init() override;
	void Uninit() override;

	DirectX11* _directX11;

	DX11Texture _texture[TextureResource::MAX];
	std::vector<std::vector<DX11Texture>>	texture_;

	PMXModelData _pmxData[ModelResource::MAX]{};
};