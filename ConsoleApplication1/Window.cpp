
#include "Window.h"
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "Vertex.h"
#include "Errors.h"
#include "ObjLoader.h"

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

	void Window::keycallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
		update();
		if (action != GLFW_PRESS)
			return;
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		default:
			break;
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
		return;
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

		framebuffer_size_callback(win, this->width, this->height);
		glfwSetKeyCallback(win, StateBase::keycallback_dispatch);
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

		_vertdata = ObjLoader.loadObjFromFile("obj/arcticcondor.obj");
		
		

		
		Vertex vertexData[2250];
		for (int i = 0; i < _vertdata.size(); i++) {
			std::cout << "x:" << _vertdata[i].position.x << " ,y:" << _vertdata[i].position.y << " ,z:" << _vertdata[i].position.z << std::endl;
			vertexData[i] = _vertdata[i];
		}
		
		/*
		//first triangle
		//right bottom
		vertexData[0].setPosition(0.5f, -0.5f, 0.0f);
		vertexData[0].setUV(1.0f, 1.0f);
		
		//left bottom
		vertexData[1].setPosition(-0.5f, -0.5f, 0.0f);
		vertexData[1].setUV(0.0f, 1.0f);
		//left top
		vertexData[2].setPosition(-0.5f, 0.5f, 0.0f);
		vertexData[2].setUV(0.0f, 0.0f);

		//second triangle
		//left top
		vertexData[3].setPosition(-0.5f, 0.5f, 0.0f);
		vertexData[3].setUV(0.0f, 0.0f);
		//right top
		vertexData[4].setPosition(0.5f, 0.5f, 0.0f);
		vertexData[4].setUV(1.0f, 0.0f);
		//right bottom
		vertexData[5].setPosition(0.5f, -0.5f, 0.0f);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 5; i++) {
			vertexData[i].setColor(255, 0, 255, 255);
			vertexData[i].setNormal(0, 0, 1);
		}
		vertexData[1].setColor(255, 0, 0, 255);
		vertexData[4].setColor(0, 255, 0, 255);

		*/


	
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

	}
	void Window::update() {
		
	}


	void Window::Render() {
		_glslProgram->use();
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