/**
* @file		Wrapper.h
* @brief	���b�p�[
* @author	���R�q��
* @date		2019/03/19
*/
#pragma once
#include "../Define/Define.h"
#include "../Windows/Windows.h"

class Wrapper {

public:

	struct TextureData
	{
		VECTOR2 size;
	};


	Wrapper(){}
	virtual ~Wrapper(){}

	virtual HRESULT Init() = 0;
	virtual void Uninit() {}

	virtual unsigned int CreateVertexBuffer(const void* vertex, unsigned int size, unsigned int num) = 0;
	virtual unsigned int CreateIndexBuffer(const WORD* vertex, unsigned int num) = 0;
	virtual void ReleaseBuffer(unsigned int num) = 0; //@ FVF fvf


	/* @brief	2D�`��J�n	*/
	virtual void BeginDrawCanvas() = 0;
	/* @brief	3D�`��J�n	*/
	virtual void BeginDrawObject() = 0;

	/* @brief	�`��I��	*/
	virtual void EndDraw() = 0;

	virtual void SetTexture(int stage, int texNum = -1, int modelNum = -1) = 0;

	/* @brief	�e�N�X�`���ǂݍ���	*/
	virtual HRESULT LoadTexture(string filename,int texnum) = 0;
	/* @brief	�e�N�X�`���̉��	*/
	virtual void	ReleaseTexture(int texnum) = 0;
	/* @brief	�e�N�X�`���̃T�C�Y�擾	*/
	virtual VECTOR2 GetTextureSize(int num) = 0;
};