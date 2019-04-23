/**
* @file		Wrapper.h
* @brief	ラッパー
* @author	小山智也
* @date		2019/03/19
*/
#pragma once
#include "../Define/Define.h"
#include "../Windows/Windows.h"
#include "../Systems/ModelLoader/PMXLoader/PMXLoader.h"

class Wrapper {

protected:
	MATRIX _inverse; //Viewの逆行列

public:

	static constexpr uint E_ERROR = UINT_MAX;

	struct TextureData
	{
		VECTOR2 size;
	};


	Wrapper(){}
	virtual ~Wrapper(){}

	virtual void Init(){};
	virtual void Uninit() {}

	virtual uint CreateVertexBuffer(const void* vertex, uint size, uint num) = 0;
	virtual unsigned int CreateIndexBuffer(const WORD* vertex, unsigned int num) = 0;
	virtual void ReleaseBuffer(unsigned int num) = 0; //@ FVF fvf


	/* @brief	2D描画開始	*/
	virtual void BeginDrawCanvas() = 0;
	/* @brief	3D描画開始	*/
	virtual void BeginDrawObject() = 0;

	/* @brief	描画終了	*/
	virtual void EndDraw() = 0;


	virtual void SetTexture(int stage, int texNum = -1, int modelNum = -1) = 0;

	/* @brief	テクスチャ読み込み	*/
	virtual HRESULT LoadTexture(string filename,int texnum) = 0;
	/* @brief	テクスチャの解放	*/
	virtual void	ReleaseTexture(int texnum) = 0;
	/* @brief	テクスチャのサイズ取得	*/
	virtual VECTOR2 GetTextureSize(int num) = 0;

	// ビュー行列の生成
	virtual MATRIX  CreateViewMatrix(VECTOR3 position, VECTOR3 at, VECTOR3 up) = 0;
	// プロジェクション行列の生成
	virtual MATRIX  CreateProjectionMatrix(int fov, float aspect, float camera_near, float camera_far) = 0;

	/* @brief	頂点シェーダー作成			*/
	virtual uint CreateVertexShader(string filename, string met, string ver, void* t, uint ele) = 0;
	/* @brief	ピクセルシェーダー作成		*/
	virtual uint CreatePixelShader(string filename, string met, string ver) = 0;
	/* @brief	ジオメトリシェーダー作成	*/
	virtual uint CreateGeometryShader(string filename, string met, string ver) = 0;
	/* @brief	コンピュートシェーダー作成	*/
	virtual uint CreateComputeShader(string filename, string met, string ver, const void* v, uint size, uint num) = 0;

	/* @brief	コンスタントバッファ作成	*/
	virtual uint CreateConstantBuffer(uint size) = 0;

	/* @brief	PMXモデルローダー群 (proto type)	*/
	virtual HRESULT LoadpmxModel(PMXModelData& data, const wstring& file) = 0;
	virtual void ReleasepmxModel() = 0;
	virtual void SetPMXModelData(PMXModelData& data, int i) = 0;


	virtual void GuiUpdate(){}
};