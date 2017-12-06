#include "Mesh.h"
namespace NeroEngine {

	Mesh::Mesh(const std::vector<Vertex>& vertData, GLint textureId) {
		this->textureId = textureId;
		this->vertData = vertData;
	}

	void Mesh::init() {

		if (VBOId == 0) {
			glGenBuffers(1, &VBOId); // create a buffer
		}
		
		Vertex vertexData[2250];
		for (int i = 0; i < vertData.size(); i++) {
		//std::cout << "x:" << _vertdata[i].position.x << " ,y:" << _vertdata[i].position.y << " ,z:" << _vertdata[i].position.z << std::endl;
		vertexData[i] = vertData[i];
		}

		glBindBuffer(GL_ARRAY_BUFFER, VBOId);//先将buffer绑定到当前
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);//将顶点数组放入这个buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Mesh::draw() {
		glGenVertexArrays(1, &this->VBOId);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		//position attrib pointer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
		//color attrib pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		//uv attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
		//normal attrib pointer
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertData));
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

};