/**
* @file		DirectX11Wrapper.h
* @brief	DirectX11�Ɋւ��鏈���̊Ǘ�
* @author	���R�q��
* @date		2019/03/18
*/
#pragma once

#include "DirectX11.h"
#include "../Wrapper.h"

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

	void SetTexture(int stage, int texNum = -1, int modelNum = -1) override;

	/* @brief	�e�N�X�`���ǂݍ���	*/
	HRESULT LoadTexture(string filename, int texnum) override;
	/* @brief	�e�N�X�`���̉��	*/
	void ReleaseTexture(int texnum) override;
	/* @brief	�e�N�X�`���̃T�C�Y�擾	*/
	VECTOR2 GetTextureSize(int num) override;


private:

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
};