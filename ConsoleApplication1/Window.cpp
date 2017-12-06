
#include "Window.h"
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "Vertex.h"
#include "Errors.h"
#include "ObjLoader.h"
#include "ImageLoader.h"

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
	void Window::keycallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
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

		glfwSetKeyCallback(win, StateBase::keycallback_dispatch);
		glfwSetMouseButtonCallback(win, StateBase::mouse_button_callback_dispatch);
		glfwSetCursorPosCallback(win, StateBase::cursor_position_callback_dispatch);
		glfwSetFramebufferSizeCallback(win, StateBase::framebuffer_size_callback_dispatch);

		glfwMakeContextCurrent(win);

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
		_vertdata = ObjLoader.loadObjFromFile("obj/arcticcondor.obj");
		_tga = imageLoader.loadTGA("obj/ArcticCondorGold.tga").texID;
		
	
		Vertex vertexData[2250];
		for (int i = 0; i < _vertdata.size(); i++) {
			//std::cout << "x:" << _vertdata[i].position.x << " ,y:" << _vertdata[i].position.y << " ,z:" << _vertdata[i].position.z << std::endl;
			//std::cout << "u:" << _vertdata[i].uv.u << " ,v:" << _vertdata[i].uv.v << std::endl;
			vertexData[i] = _vertdata[i];
		}
	
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);//先将buffer绑定到当前
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);//将顶点数组放入这个buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		_glslProgram = new NeroEngine::GLSLProgram();
		_glslProgram->complieShaders("shader/myshader.vert","shader/myshader.frag");
		_glslProgram->addAttribute("vertexPosition");
		_glslProgram->addAttribute("vertexColor");
		_glslProgram->addAttribute("vertexUV");
		_glslProgram->addAttribute("vertexNormal");
		_glslProgram->linkShaders();

		_camera.init(width,height);
		
		_camera.setScale(100);
		_camera.setPosition(glm::vec3(0, 0, 150));
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


	void Window::Render() {
		update(); 

		glClearDepth(200.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		_glslProgram->use();
		glActiveTexture(GL_TEXTURE0);

		GLuint textureUniform = _glslProgram->getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);

		glm::mat4 projectionMatrix = _camera.getCameraMatrix();
		GLuint pUniform = _glslProgram->getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
		glBindTexture(GL_TEXTURE_2D, _tga);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//position attrib pointer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
		//color attrib pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		//uv attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
		//normal attrib pointer
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
		glDrawArrays(GL_TRIANGLES, 0, 2250);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
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