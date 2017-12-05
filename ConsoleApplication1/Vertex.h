<<<<<<< HEAD
#ifndef  __NERO_ENGINE_GLSL_VERTEX__
#define  __NERO_ENGINE_GLSL_VERTEX__
#include <GL/glew.h>
namespace NeroEngine {
	struct Position {
		float x;
		float y;
	};
	struct  Color{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	struct UV{
		float u;
		float v;
	};
	struct  Vertex
	{
		Position position;
		Color color;
		UV uv;
		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		};
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		};
		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}

	};
}
#endif // ! __NERO_ENGINE_GLSL_VERTEX__


=======
#ifndef  __NERO_ENGINE_GLSL_VERTEX__
#define  __NERO_ENGINE_GLSL_VERTEX__
#include <GL/glew.h>
namespace NeroEngine {
	struct Position {
		float x;
		float y;
	};
	struct  Color{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	struct UV{
		float u;
		float v;
	};
	struct  Vertex
	{
		Position position;
		Color color;
		UV uv;
		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		};
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		};
		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}

	};
}
#endif // ! __NERO_ENGINE_GLSL_VERTEX__


>>>>>>> 569357d9b33b73a7a369a00dc66de4303f7138a5