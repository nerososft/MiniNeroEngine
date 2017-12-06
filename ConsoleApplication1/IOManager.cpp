#include "IOManager.h"
#include <fstream>
namespace NeroEngine {
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&buffer[0], fileSize);

		return true;


	}

	bool IOManager::readFileToString(std::string filePath, std::string data) {
		std::ifstream file(filePath);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		file.seekg(0, std::ios::end);
		int len = file.tellg();
		file.seekg(std::ios::beg);

		char* str = new char[len];
		file.read(str, len);

		data = str;
		return true;
	}
}