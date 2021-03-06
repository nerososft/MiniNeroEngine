
#include "Window.h"
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "Vertex.h"
#include "Errors.h"
#include "ObjLoader.h"
#include "ImageLoader.h"
#include <time.h>

namespace NeroEngine {
	Window::Window(char *title, int width, int height, std::shared_ptr<ColorRGB> backGround) :
		title(title),
		width(width),
		height(height),
		backGround(backGround) {
		_vboID = 0;
		glInit();
		init();
	}

	Window::~Window() {
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}
	GLfloat ratio = 1.f;

	void Window::framebuffer_size_callback(GLFWwindow *window, int w, int h) {
		if (h == 0) {
			h = 1;
		}
		if (h > 0) {
			ratio = (float)w / (float)h;
		}
		glViewport(0, 0, w, h);
		this->width = w;
		this->height = h;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		update();
	}
	void Window::keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
		if(action == GLFW_PRESS){
			std::cout << key << std::endl;
			_inputManager.pressKey(key);
		}
		else if (action==GLFW_RELEASE) {
			_inputManager.releaseKey(key);
		}
	}
	
	void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mod) {
		if (action == GLFW_PRESS) switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT: {
			std::cout << "Mosue left button clicked!" << std::endl;
			break;
		}
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "Mosue middle button clicked!" << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "Mosue right button clicked!" << std::endl;
			break;
		default:
			return;
		}
		return;
	}
	void Window::cursor_position_callback(GLFWwindow* window, double x, double y) {
		_inputManager.setMouseCoords(x, y);
	}

	void Window::glInit() {
		if (!glfwInit()) {
			fatalError("glfw init failed");
			exit(0);
		}
		win = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
		if (!win) {
			glfwTerminate();
			fatalError("win init failed");
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(win);

		glfwSetKeyCallback(win, StateBase::keycallback_dispatch);
		glfwSetMouseButtonCallback(win, StateBase::mouse_button_callback_dispatch);
		glfwSetCursorPosCallback(win, StateBase::cursor_position_callback_dispatch);
		glfwSetFramebufferSizeCallback(win, StateBase::framebuffer_size_callback_dispatch);

		

		GLenum err = glewInit();
		if (GLEW_OK != err) {
			fatalError("glew init failed");
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			exit(0);
		}
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
		printf("%s\n", glGetString(GL_VERSION));
	}
	void Window::init() {
		if (_vboID == 0) {
			glGenBuffers(1, &_vboID); // create a buffer
		}

		ObjLoader ObjLoader;
		ImageLoader imageLoader;
	
		
		
		_glslProgram = new NeroEngine::GLSLProgram();
		_glslProgram->complieShaders("shader/myshader.vert","shader/myshader.frag");
		_glslProgram->addAttribute("vertexPosition");
		_glslProgram->addAttribute("vertexColor");
		_glslProgram->addAttribute("vertexUV");
		_glslProgram->addAttribute("vertexNormal");
		_glslProgram->linkShaders();


		_tga = imageLoader.loadTGA("obj/ArcticCondorGold.tga").texID;
		_vertdata = ObjLoader.loadObjFromFile("obj/arcticcondor.obj");
		_dragonMesh = Mesh(_vertdata, _tga, _glslProgram);

		_camera.init(width,height);
		_camera.setScale(100);
		_camera.setPosition(glm::vec3(0, 0.5, 0));
		_camera.rotate(30, glm::vec3(0, 1, 0));
	}

	float scale = 1;
	float angle = 0;
	float scale_speed = 1;
	void Window::update() {
		_camera.update();
	
		_camera.rotate(angle, glm::vec3(0, 1, 0));
		angle += 0.1;

		if (_inputManager.isKeyPressed(GLFW_KEY_Q)) {
			std::cout << "key Q pressed" << std::endl;
			_camera.setScale(scale);
			scale++;
		}
		if (_inputManager.isKeyPressed(GLFW_KEY_E)) {
			std::cout << "key E pressed" << std::endl;
			_camera.setScale(scale);
			scale--;
		}
	}

	float t = 0.0f;

	void Window::Render() {
		update(); 

		glClearDepth(200.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_glslProgram->use();
		glActiveTexture(GL_TEXTURE0);

		GLuint textureUniform = _glslProgram->getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);

		
		t += 0.003f;
		GLuint timeUniform = _glslProgram->getUniformLocation("time");
		glUniform1f(timeUniform,t);

		glm::mat4 projectionMatrix = _camera.getCameraMatrix();
		
		GLuint pUniform = _glslProgram->getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	
		_dragonMesh.draw();

		
		_glslProgram->unuse();
	}

	int Window::run() {
		while (!glfwWindowShouldClose(win)) {
			glClearColor(backGround->R(), backGround->G(), backGround->B(), 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Render();
			glfwSwapBuffers(win);
			glfwPollEvents();
		}
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
}