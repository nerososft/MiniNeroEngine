#ifndef __NERO_ENGINE_MESH__
#define __NERO_ENGINE_MESH__
#include <vector>
#include "Vertex.h"

namespace NeroEngine {
	class Mesh
	{
	public:
		void draw();
		Mesh() {};
		Mesh(const std::vector<Vertex>& vertData,
			GLint textureId); 
	private:
		std::vector<Vertex> _vertData;// 顶点数据
		GLuint _VAOId;
		GLuint _VBOId; // 缓存对象
		GLint _textureId; // 纹理对象id
		void init();  // 建立VAO,VBO等缓冲区
	};
};
#endif // ! __NERO_ENGINE_MESH__