#include "Camera3D.h"
namespace NeroEngine {
	Camera3D::Camera3D() :_position(0.0f, 0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_angle(0.0f),
		_axis(0.0f, 0.0f, 0.0f),
		_needsMatrixUpdate(true),
		_screenWidth(100),
		_screenHeight(100)
	{

	}


	Camera3D::~Camera3D()
	{
	}
	void Camera3D::init(int screenWidth, int screenHeight) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, float(_screenWidth), 0.0f, float(_screenHeight));
	}
	void Camera3D::update() {
		if (_needsMatrixUpdate) {
			glm::vec3 translate(-_position.x + _screenWidth / 2.0f, -_position.y + _screenHeight / 2.0f, -_position.z + _screenDepth / 2.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			glm::vec3 scale(_scale, _scale, 0);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_cameraMatrix = glm::rotate(_cameraMatrix, _angle, _axis);


			_needsMatrixUpdate = false;
		}
	}
	void Camera3D::rotate(float angle, glm::vec3 axis) {
		_angle = angle; 
		_axis = axis;
		_needsMatrixUpdate = true;
	}
	glm::vec3 Camera3D::convertScreenToWorld(glm::vec3 screenCoords) {
		//invert dir Y
		screenCoords.y = _screenHeight - screenCoords.y;
		//in the center
		screenCoords -= glm::vec3(_screenWidth / 2, _screenHeight / 2,_screenDepth/2);
		//scala the coordnates
		screenCoords /= _scale;
		//translate with the camera position
		screenCoords += _position;

		return screenCoords;
	}
	bool Camera3D::isBoxiInView(const glm::vec3& position, const glm::vec3& dimensions) {

		glm::vec3 scaledScreenDimensions = glm::vec3(_screenWidth, _screenHeight,_screenDepth) / (_scale);

		float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
		float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

		glm::vec3 centerPos = position + dimensions / 2.0f;
		glm::vec3 centerCameraPos = _position;
		glm::vec3 distVec = centerPos - centerCameraPos;

		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		if (xDepth > 0 && yDepth > 0) {
			
			return true;
		}
		return false;

	}
}