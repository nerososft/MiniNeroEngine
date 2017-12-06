#ifndef __NERO_ENGINE_TGA_TEXTURE__
#define __NERO_ENGINE_TGA_TEXTURE__

#include <GL/glew.h>

class TGATexture
{
public:

	GLubyte *imageData;//图像数据  
	GLuint bpp;//像素深度  
	GLuint width;//图像宽度  
	GLuint height;//图像高度  
	GLuint texID;//对应的纹理ID  

	TGATexture() {};
	~TGATexture() {};
};

#endif

