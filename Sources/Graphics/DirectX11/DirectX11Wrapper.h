/**
* @file		DirectX11Wrapper.h
* @brief	DirectX11�Ɋւ��鏈���̊Ǘ�
* @author	���R�q��
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

	/* @brief	2D�`��J�n	*/
	void BeginDrawCanvas() override;
	/* @brief	3D�`��J�n	*/
	void BeginDrawObject() override;

	/* @brief	�`��I��	*/
	void EndDraw() override;

	/* @brif	�r���[�s��̐���	*/
	MATRIX  CreateViewMatrix(VECTOR3 position, VECTOR3 at, VECTOR3 up);

	void SetTexture(int stage, int texNum = -1, int modelNum = -1) override;

	/* @brief	�e�N�X�`���ǂݍ���	*/
	HRESULT LoadTexture(string filename, int texnum) override;
	/* @brief	�e�N�X�`���̉��	*/
	void ReleaseTexture(int texnum) override;
	/* @brief	�e�N�X�`���̃T�C�Y�擾	*/
	VECTOR2 GetTextureSize(int num) override;

	/* @brief	pmx�t�@�C���̓ǂݍ���*/
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

	// pmx�֌W
	HRESULT GetPMXStringUTF16(ifstream& file, wstring& output);
	bool LoadPMX(PMXModelData& data, const wstring& file);

	void SetPMXModelData(PMXModelData& data, int i) override;

	// DirectX11�̃e�N�X�`�����
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