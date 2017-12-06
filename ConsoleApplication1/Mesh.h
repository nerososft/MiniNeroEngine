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
		std::vector<Vertex> _vertData;// ��������
		GLuint _VAOId;
		GLuint _VBOId; // �������
		GLint _textureId; // �������id
		void init();  // ����VAO,VBO�Ȼ�����
	};
};
#endif // ! __NERO_ENGINE_MESH__