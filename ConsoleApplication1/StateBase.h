<<<<<<< HEAD
#ifndef __NERO_ENGINE_STATEBASE__
#define __NERO_ENGINE_STATEBASE__

#include <gl\glew.h>
#include <GLFW\glfw3.h>
namespace NeroEngine {
	class StateBase {
	public:
		virtual void keycallback(
			GLFWwindow *window,
			int key,
			int scancode,
			int action,
			int mods) = 0;

		virtual void framebuffer_size_callback(GLFWwindow *window, int w, int h) = 0;

		static StateBase *event_handling_instance;

		virtual void setEventHandling() { event_handling_instance = this; }

		static void keycallback_dispatch(
			GLFWwindow *window,
			int key,
			int scancode,
			int action,
			int mods) {
			if (event_handling_instance)
				event_handling_instance->keycallback(window, key, scancode, action, mods);
		}

		static void framebuffer_size_callback_dispatch(GLFWwindow *window, int w, int h) {
			if (event_handling_instance)
				event_handling_instance->framebuffer_size_callback(window, w, h);
		}

		virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mod) = 0;
		virtual void cursor_position_callback(GLFWwindow* window, double x, double y) = 0;

		static void mouse_button_callback_dispatch(GLFWwindow* window, int button, int action, int mod) {
			if (event_handling_instance)
				event_handling_instance->mouse_button_callback(window, button, action, mod);
		}

		static void cursor_position_callback_dispatch(GLFWwindow* window, double x, double y) {
			if (event_handling_instance)
				event_handling_instance->cursor_position_callback(window, x, y);
		}
	};
}
=======
#ifndef __NERO_ENGINE_STATEBASE__
#define __NERO_ENGINE_STATEBASE__

#include <gl\glew.h>
#include <GLFW\glfw3.h>
namespace NeroEngine {
	class StateBase {
	public:
		virtual void keycallback(
			GLFWwindow *window,
			int key,
			int scancode,
			int action,
			int mods) = 0;

		virtual void framebuffer_size_callback(GLFWwindow *window, int w, int h) = 0;

		static StateBase *event_handling_instance;

		virtual void setEventHandling() { event_handling_instance = this; }

		static void keycallback_dispatch(
			GLFWwindow *window,
			int key,
			int scancode,
			int action,
			int mods) {
			if (event_handling_instance)
				event_handling_instance->keycallback(window, key, scancode, action, mods);
		}

		static void framebuffer_size_callback_dispatch(GLFWwindow *window, int w, int h) {
			if (event_handling_instance)
				event_handling_instance->framebuffer_size_callback(window, w, h);
		}

		virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mod) = 0;
		virtual void cursor_position_callback(GLFWwindow* window, double x, double y) = 0;

		static void mouse_button_callback_dispatch(GLFWwindow* window, int button, int action, int mod) {
			if (event_handling_instance)
				event_handling_instance->mouse_button_callback(window, button, action, mod);
		}

		static void cursor_position_callback_dispatch(GLFWwindow* window, double x, double y) {
			if (event_handling_instance)
				event_handling_instance->cursor_position_callback(window, x, y);
		}
	};
}
>>>>>>> 569357d9b33b73a7a369a00dc66de4303f7138a5
#endif /* __NERO_ENGINE_STATEBASE__ */