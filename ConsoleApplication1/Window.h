
#ifndef __NERO_ENGINE_WINDOW__
#define  __NERO_ENGINE_WINDOW__

#include "StateBase.h"
#include "ColorRGB.h"
#include "GLSLProgram.h"
#include <memory>
#include <vector>
#include "Vertex.h"
#include "TGATexture.h"
#include "Camera3D.h"
#include "InputManager.h"
#include "Mesh.h"

namespace NeroEngine {
	class Window : public StateBase
	{
	public:
		Window(char *title, int width, int height, std::shared_ptr<ColorRGB> backGround);
		~Window();


		virtual void init();
		virtual void update();

		virtual void keycallback(
			GLFWwindow *window,
			int key,
			int scancode,
			int action,
			int mods);

		virtual void framebuffer_size_callback(GLFWwindow *window, int w, int h);
		virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mod);
		virtual void cursor_position_callback(GLFWwindow* window, double x, double y);

		void Render(void);
		int run();

		

	private:
		GLFWwindow *win;

		GLuint _vboID;

		char *title;
		int width;
		int height;
		std::shared_ptr<ColorRGB> backGround;

		GLSLProgram* _glslProgram;
		Camera3D _camera;
		InputManager _inputManager;

		std::vector<Vertex> _vertdata;
		Mesh _dragonMesh;

		GLuint _tga;

		void glInit();

	};
};
#endif // !__NERO_ENGINE_WINDOW__

