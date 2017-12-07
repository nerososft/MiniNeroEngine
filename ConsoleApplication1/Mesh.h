#ifndef __NERO_ENGINE_MESH__
#define __NERO_ENGINE_MESH__
#include <vector>
#include "Vertex.h"
#include "GLSLProgram.h"

namespace NeroEngine {
	class Mesh
	{
	public:
		void draw();
		Mesh() {};
		Mesh(const std::vector<Vertex>& vertData,
			GLint textureId,GLSLProgram* glslProgram); 
	private:
		std::vector<Vertex> _vertData;// ��������
		GLuint _VAOId;
		GLuint _VBOId; // �������
		GLint _textureId; // �������id
		GLSLProgram* _glslProgram;
		void init();  // ����VAO,VBO�Ȼ�����
	};
};
#endif // ! __NERO_ENGINE_MESH__