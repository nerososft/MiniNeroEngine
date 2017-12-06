
#ifndef __NERO_ENGINE_GLSL_PROGRAM__
#define __NERO_ENGINE_GLSL_PROGRAM__

#include <gl\glew.h>
namespace NeroEngine {
	class GLSLProgram
	{
	private:
		int _numAttributes;
		void complieShader(const std::string& filePath, GLuint& id);
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	public:
		GLSLProgram() :
			_numAttributes(0),
			_programID(0),
			_vertexShaderID(0),
			_fragmentShaderID(0) {
		}
		~GLSLProgram();
		void complieShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(const std::string& attributeName);
		GLint getUniformLocation(const std::string& uniformLocationName);
		void use();
		void unuse();

	};
};
#endif // ! __NERO_ENGINE_GLSL_PROGRAM__

