#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& worldUp, float yaw, float pitch)
	: _position(position)
	, _cameraUp(0.0f, 1.0f, 0.0f)
	, _cameraFront(0.0f, 0.0f, -1.0f)
	, _cameraRight(1.0f, 0.0f, 0.0f)
	, _worldUp(worldUp)
	, _yaw(yaw)
	, _pitch(pitch)
	, _roll(0.0f)
	, _speed(2.5f)
	, _sensitivity(0.1f)
	, _zoom(45.0f)
	, _lastXPos(0.0f)
	, _lastYPos(0.0f)
	, _firstMovement(true)
{
	UpdateCameraVectiors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(_position, _position + _cameraFront, _cameraUp);
}

void Camera::ProcessMouseScroll(float yOffset)
{
	SetZoom(_zoom - yOffset);
}

void Camera::ProcessMouseMovement(float xPos, float yPos)
{
	if (_firstMovement) {
		_lastXPos = xPos;
		_lastYPos = yPos;
		_firstMovement = false;
	}

	float xOffset = xPos - _lastXPos;
	float yOffset = _lastYPos - yPos;
	_lastXPos = xPos;
	_lastYPos = yPos;

	xOffset *= _sensitivity;
	yOffset *= _sensitivity;

	SetYaw(_yaw + xOffset);
	SetPitch(_pitch + yOffset);

	UpdateCameraVectiors();
}

void Camera::ProcessCameraMovement(Direction direction, float delta)
{
	float velocity = _speed * delta;
	if (direction == Direction::FORWARD) _position += _cameraFront * velocity;
	else if (direction == Direction::BACKWARD) _position -= _cameraFront * velocity;
	else if (direction == Direction::RIGHT) _position += _cameraRight * velocity;
	else if (direction == Direction::LEFT) _position -= _cameraRight * velocity;
}

void Camera::UpdateCameraVectiors()
{
	glm::vec3 cameraDirection = glm::vec3(cos(glm::radians(_yaw)) * cos(glm::radians(_pitch))
		, sin(glm::radians(_pitch))
		, sin(glm::radians(_yaw)) * cos(glm::radians(_pitch)));
	_cameraFront = glm::normalize(cameraDirection);
	_cameraRight = glm::normalize(glm::cross(_cameraFront, _worldUp));
	_cameraUp = glm::normalize(glm::cross(_cameraRight, _cameraFront));
}
