#pragma once

#include <algorithm>

#include <glm/glm.hpp>

class Camera
{
public:
	enum class Direction
	{
		FORWARD,
		BACKWARD,
		RIGHT,
		LEFT
	};

	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

	void SetPosition(const glm::vec3& position) { _position = position; }
	const glm::vec3& GetPosition() const { return _position; }

	void SetFrontDirection(const glm::vec3& frontDirection) { _cameraFront = frontDirection; }
	const glm::vec3& GerFrontDirection() const { return _cameraFront; }

	void SetRightDirection(const glm::vec3& rightDirection) { _cameraRight = rightDirection; }
	const glm::vec3& GetRightDirection() const { return _cameraRight; }

	void SetUpDirecrion(const glm::vec3& upDirection) { _cameraUp = upDirection; }
	const glm::vec3& GetUpDirecrion() const { return _cameraUp; }

	void SetSpeed(float speed) { _speed = speed; }
	const float GetSpeed() const { return _speed; }

	void SetZoom(float zoom)
	{
		_zoom = std::min(std::max(zoom, 1.0f), 60.f);
	}
	const float GetZoom() const { return _zoom; }

	void SetSensitivity(float sensitivity) { _sensitivity = sensitivity; }
	const float GetSensitivity() const { return _sensitivity; }

	void SetYaw(float yaw) { _yaw = yaw; }
	const float GetYaw() const { return _yaw; }

	void SetPitch(float pitch)
	{
		_pitch = std::min(std::max(pitch, -89.0f), 89.0f);
	}
	const float GetPitch() const { return _pitch; }

	glm::mat4 GetViewMatrix() const;
	void ProcessMouseScroll(float yOffset);
	void ProcessMouseMovement(float xPos, float yPos);
	void ProcessCameraMovement(Direction direction, float delta);


private:
	void UpdateCameraVectiors();

	glm::vec3 _worldUp;

	glm::vec3 _position;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraRight;
	glm::vec3 _cameraUp;

	float _speed;
	float _zoom;
	float _sensitivity;

	float _yaw;
	float _pitch;
	float _roll;

	float _lastXPos;
	float _lastYPos;

	bool _firstMovement;
};