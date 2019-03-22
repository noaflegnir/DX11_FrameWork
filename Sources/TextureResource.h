#pragma once

#include "Define/Define.h"

namespace TextureResource
{
	class Texture {

		const string directory_ = "./Resource/Texture/";

	public:

		enum TEXTURE_NUM {
			TEST = 0,
			MAX
		};

		const string TextureFilePath[MAX] = {
			{ directory_ + "aaa" },
		};
	};
}