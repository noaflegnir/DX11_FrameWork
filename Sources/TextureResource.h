#pragma once

#include "Define/Define.h"

class TextureResource {

#ifdef _DEBUG
	const string directory_ = "../Resource/Texture/";
#else
	const string directory_ = "./Resource/Texture/";
#endif


public:

	enum TEXTURE_NUM {
		TITLE = 0,
		MAX,
	};

	const string TextureFilePath[MAX] = {
		{ directory_ + "title.png" },
	};

};