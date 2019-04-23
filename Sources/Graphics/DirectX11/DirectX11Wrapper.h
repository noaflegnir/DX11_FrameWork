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
	uint CreateVertexBuffer(const void* vertex, uint size, uint num) override;
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
	MATRIX  CreateProjectionMatrix(int fov, float aspect, float camera_near, float camera_far);

	void SetTexture(int stage, int texNum = -1, int modelNum = -1) override;

	/* @brief	�e�N�X�`���ǂݍ���	*/
	HRESULT LoadTexture(string filename, int texnum) override;
	/* @brief	�e�N�X�`���̉��	*/
	void ReleaseTexture(int texnum) override;
	/* @brief	�e�N�X�`���̃T�C�Y�擾	*/
	VECTOR2 GetTextureSize(int num) override;
		

	/* @brief	�V�F�[�_�[�Q�̍쐬	*/
	uint CreateVertexShader(string filename, string met, string ver, void* t, uint ele) override;
	uint CreatePixelShader(string filename, string met, string ver) override;
	uint CreateGeometryShader(string filename, string met, string ver) override;
	uint CreateComputeShader(string filename, string met, string ver, const void* v, uint size, uint num) override;

	uint CreateConstantBuffer(uint size) override;

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

	/* @brief	�V�F�[�_�[�̃R���p�C��	*/
	ID3DBlob* CompiledShader(string filename, string met, string ver);

	// pmx�֌W
	HRESULT GetPMXStringUTF16(ifstream& file, wstring& output);
	bool LoadPMX(PMXModelData& data, const wstring& file);
	void SetPMXModelData(PMXModelData& data, int i) override;

	struct VertexBuffer
	{
		ID3D11Buffer* _buffer;
		uint _stride;
		uint _offset;
	};

	struct SHADER_SCENE
	{
		MATRIX _view;
		MATRIX _proj;
	};
	// DirectX11�̃e�N�X�`�����
	struct DX11Texture : public TextureData
	{
		ID3D11ShaderResourceView* _srv;
	};
	// DirectX11�̒��_�V�F�[�_�[
	struct VertexShader
	{
		ID3D11VertexShader* shader;
		ID3D11InputLayout*  layout;
	};
	// DirectX11�̃s�N�Z���V�F�[�_�[
	struct PixelShader
	{
		ID3D11PixelShader*	shader;
		ID3D11SamplerState* sampler;
	};
	struct ComputeShader
	{
		ID3D11ComputeShader* shader;
		ID3D11Buffer*		 buffer;
		ID3D11ShaderResourceView* shaderResource;
		ID3D11UnorderedAccessView* unordereAcces;
	};

	struct Shader
	{
		std::vector<uint> _vertexShader;
		std::vector<uint> _pixelShader;
		std::vector<uint> _geometryShader;
		std::vector<uint> _constantBuffer;
	};

	DX11Wrapper(DirectX11* directX11);
	~DX11Wrapper() {}

	void Init()   override;
	void Uninit() override;

	uint InsideBuffer();

	DirectX11* _directX11;

	std::vector<VertexBuffer>  _vertexBuffer;

	ID3D11DepthStencilState*   _depthState;
	ID3D11RasterizerState*     _rasterizerState;


	std::vector<VertexShader>			_vertexShader;
	std::vector<PixelShader>			_pixelShader;
	std::vector<ID3D11GeometryShader*>	_geometryShader;
	std::vector<ComputeShader>			_computeShader;

	// �V�F�[�_�Ƃ̃f�[�^�̂��Ƃ��������
	std::vector<ID3D11Buffer*> _constantBuffer;

	// Canvas��Object��2��
	Shader _shader[2];


	DX11Texture _texture[TextureResource::MAX];
	std::vector<std::vector<DX11Texture>>	texture_;

	
	PMXModelData _pmxData[ModelResource::MAX]{};
};