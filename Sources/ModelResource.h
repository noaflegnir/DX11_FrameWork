#pragma once

#include "Define/Define.h"

class ModelResource {

#ifdef _DEBUG
	const string directory_ = "../Resource/Model/";
#else
	const string directory_ = "./Resource/Model/";
#endif


public:

	enum MODEL_NUM {
		TITLE = 0,
		MAX,
	};

	const string PMXModelFilePath[MAX] = {
		{ directory_ + "hatune.pmx" },
	};

};