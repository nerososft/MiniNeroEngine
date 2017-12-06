#ifndef __NERO_ENGINE_MESH__
#define __NERO_ENGINE_MESH__
#include <vector>
#include "Vertex.h"

namespace NeroEngine {
	class Mesh
	{
	public:
		void draw();
		Mesh(const std::vector<Vertex>& vertData,
			GLint textureId); 
	private:
		std::vector<Vertex> vertData;// ��������
		GLuint VAOId;
		GLuint VBOId; // �������
		GLint textureId; // �������id
		void init();  // ����VAO,VBO�Ȼ�����
	};
};
#endif // ! __NERO_ENGINE_MESH__