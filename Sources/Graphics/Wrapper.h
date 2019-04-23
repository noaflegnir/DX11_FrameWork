/**
* @file		Wrapper.h
* @brief	���b�p�[
* @author	���R�q��
* @date		2019/03/19
*/
#pragma once
#include "../Define/Define.h"
#include "../Windows/Windows.h"
#include "../Systems/ModelLoader/PMXLoader/PMXLoader.h"

class Wrapper {

protected:
	MATRIX _inverse; //View�̋t�s��

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

	// �r���[�s��̐���
	virtual MATRIX  CreateViewMatrix(VECTOR3 position, VECTOR3 at, VECTOR3 up) = 0;
	// �v���W�F�N�V�����s��̐���
	virtual MATRIX  CreateProjectionMatrix(int fov, float aspect, float camera_near, float camera_far) = 0;

	/* @brief	���_�V�F�[�_�[�쐬			*/
	virtual uint CreateVertexShader(string filename, string met, string ver, void* t, uint ele) = 0;
	/* @brief	�s�N�Z���V�F�[�_�[�쐬		*/
	virtual uint CreatePixelShader(string filename, string met, string ver) = 0;
	/* @brief	�W�I���g���V�F�[�_�[�쐬	*/
	virtual uint CreateGeometryShader(string filename, string met, string ver) = 0;
	/* @brief	�R���s���[�g�V�F�[�_�[�쐬	*/
	virtual uint CreateComputeShader(string filename, string met, string ver, const void* v, uint size, uint num) = 0;

	/* @brief	�R���X�^���g�o�b�t�@�쐬	*/
	virtual uint CreateConstantBuffer(uint size) = 0;

	/* @brief	PMX���f�����[�_�[�Q (proto type)	*/
	virtual HRESULT LoadpmxModel(PMXModelData& data, const wstring& file) = 0;
	virtual void ReleasepmxModel() = 0;
	virtual void SetPMXModelData(PMXModelData& data, int i) = 0;


	virtual void GuiUpdate(){}
};