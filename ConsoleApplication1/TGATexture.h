#ifndef __NERO_ENGINE_TGA_TEXTURE__
#define __NERO_ENGINE_TGA_TEXTURE__

#include <GL/glew.h>

class TGATexture
{
public:

	GLubyte *imageData;//ͼ������  
	GLuint bpp;//�������  
	GLuint width;//ͼ����  
	GLuint height;//ͼ��߶�  
	GLuint texID;//��Ӧ������ID  

	TGATexture() {};
	~TGATexture() {};
};

#endif

