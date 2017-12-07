#include "Mesh.h"
#include <iostream>
namespace NeroEngine {

	Mesh::Mesh(const std::vector<Vertex>& vertData, GLint textureId, GLSLProgram* glslProgram) {
		_textureId = textureId;
		_vertData = vertData;
		_glslProgram = glslProgram;
		init();
	}

	void Mesh::init() {
		if (_VBOId == 0) {
			glGenBuffers(1, &_VBOId); // create a buffer
		}
	
		Vertex* data = new Vertex[_vertData.size()];
		data = _vertData.data();
	
		int size = 0;
		for (int i = 0; i < _vertData.size(); i++) {
			size += sizeof(_vertData[i]);
		}
		std::cout <<size << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, _VBOId);//先将buffer绑定到当前
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);//将顶点数组放入这个buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Mesh::draw() {

		glBindTexture(GL_TEXTURE_2D,_textureId);
		glBindBuffer(GL_ARRAY_BUFFER, _VBOId);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
		glDrawArrays(GL_TRIANGLES, 0, _vertData.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

};