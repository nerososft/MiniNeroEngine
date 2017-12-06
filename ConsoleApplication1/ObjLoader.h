#ifndef __NERO_ENGINE_OBJ_LOADER__
#define __NERO_ENGINE_OBJ_LOADER__

#include <string>
#include <vector>
#include "Vertex.h"
#include "Mesh.h"

namespace NeroEngine {
	class ObjLoader
	{
	public:
		ObjLoader();
		~ObjLoader();
		std::vector<Vertex> loadObjFromFile(std::string filePath);

	};
};
#endif // __NERO_ENGINE_OBJ_LOADER__
