#include "ObjLoader.h"
#include "IOManager.h"
#include "Errors.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace NeroEngine {

	ObjLoader::ObjLoader() {

	}

	ObjLoader::~ObjLoader() {

	}

	std::vector<Vertex> ObjLoader::loadObjFromFile(std::string filePath) {
		
		std::ifstream file(filePath);

		if (file.fail()) {
			perror(filePath.c_str());
		}

		std::vector<UV> uvData;
		std::vector<Position> tempPositionData;
		std::vector<Position> positionData;
		std::vector<Normal> normalData;

		std::string line;
		while (getline(file, line))
		{
			if (line.substr(0, 2) == "vt") //uv
			{
				std::istringstream s(line.substr(2));
				UV v;
				s >> v.u;
				s >> v.v;

				//v.v = -v.v;  // 注意这里加载的dds纹理 要对y进行反转
				uvData.push_back(v);
			}
			else if (line.substr(0, 2) == "vn") // normal
			{
				std::istringstream s(line.substr(2));
				Normal vn;
				s >> vn.x;
				s >> vn.y;
				s >> vn.z;
				normalData.push_back(vn);
			}
			else if (line.substr(0, 1) == "v") // position
			{
				std::istringstream s(line.substr(1));
				Position v;
				s >> v.x;
				s >> v.y;
				s >> v.z;
				positionData.push_back(v);
			}
			else if (line.substr(0, 1) == "f") // face
			{
				std::istringstream s(line.substr(1));
				std::string firstVertex;
				s >> firstVertex;
				std::string secondVertex;
				s >> secondVertex;
				std::string thridVertex;
				s >> thridVertex;
			}
			else if (line[0] == '#') // comment
			{
			}
			else
			{
				// others
			}
		}

		std::vector<Vertex> vertData;

		for (int i = 0; i < positionData.size();i++) {
			Vertex vertex;
			vertex.setColor(255, 0, 0,255);
			vertex.setNormal(0, 1, 0);
			vertex.setUV(1, 0);
			vertex.setPosition(positionData[i].x, positionData[i].y,positionData[i].z);
			vertData.push_back(vertex);
		}

		return vertData;

	}

};