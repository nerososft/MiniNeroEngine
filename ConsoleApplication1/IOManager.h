//#ifndef __NERO_ENGINE_IO_MANAGER__
#define __NERO_ENGINE_IO_MANAGER__
#include <vector>
#include <string>
namespace NeroEngine {
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
		static bool readFileToString(std::string filePath, std::string data);
	};
};
//#endif // __NERO_ENGINE_IO_MANAGER__
