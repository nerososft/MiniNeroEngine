#ifndef __NERO_ENGINE_CAMERA_3D__
#define __NERO_ENGINE_CAMERA_3D__

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace NeroEngine {

	class Camera3D
	{
	public:
		Camera3D();
		~Camera3D();

		void update();
		void init(int screenWidth, int screenHeight);

		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }
		void setPosition(const glm::vec3 newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		glm::vec3 convertScreenToWorld(glm::vec3 screenCoords);
		bool isBoxiInView(const glm::vec3& position, const glm::vec3& dimensions);

		float getScale() { return _scale; }
		glm::vec3 getPosition() { return _position; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

		void rotate(float angle, glm::vec3 axix);

	private:
		int _screenWidth;
		int _screenHeight;
		int _screenDepth;
		bool _needsMatrixUpdate;
		float _scale;

		float _angle;
		glm::vec3 _axis;

		glm::vec3 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};
};
#endif
