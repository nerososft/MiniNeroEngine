
#ifndef  __NERO_ENGINE_GLSL_VERTEX__
#define  __NERO_ENGINE_GLSL_VERTEX__
#include <GL/glew.h>
namespace NeroEngine {
	struct Position {
		float x;
		float y;
		float z;
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
		void setPosition(float x, float y,float z) {
			position.x = x;
			position.y = y;
			position.z = z;
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


