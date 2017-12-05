#ifndef __NERO_ENGINE_IMAGE_LOADER__
#define __NERO_ENGINE_IMAGE_LOADER__

#include "GLTexture.h"
#include <string>
namespace NeroEngine {
	class ImageLoader {
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}
#endif // __NERO_ENGINE_IMAGE_LOADER__
