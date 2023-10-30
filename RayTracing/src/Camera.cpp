#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Input/Input.h"

using namespace jjf;

Camera::Camera(float verticalFov, float nearClip, float farClip)
	: m_VerticalFov(verticalFov), m_NearClip(nearClip), m_FarClip(farClip)
{
}

void Camera::OnUpdate(float deltaTime)
{
	glm::vec2 mousePosition = Input::GetMousePosition();
	glm::vec2 delta = (mousePosition - m_LastMousePosition) * 0.05f;
	m_LastMousePosition = mousePosition;

	if (!Input::IsMouseButtonPressed(MouseButton::Right))
	{
		Input::SetCursorMode(CursorMode::Normal);
		return;
	}

	Input::SetCursorMode(CursorMode::Locked);

	bool moved = false;

	constexpr glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 rightDirection = glm::normalize(glm::cross(m_ForwardDirection, upDirection));

	float speed = 3.0f;

	if (Input::IsKeyPressed(KeyCode::W))
	{
		m_Position += m_ForwardDirection * speed * deltaTime;
		moved = true;
	}
	else if (Input::IsKeyPressed(KeyCode::S))
	{
		m_Position -= m_ForwardDirection * speed * deltaTime;
		moved = true;
	}
	if (Input::IsKeyPressed(KeyCode::A))
	{
		m_Position -= rightDirection * speed * deltaTime;
		moved = true;
	}
	else if (Input::IsKeyPressed(KeyCode::D))
	{
		m_Position += rightDirection * speed * deltaTime;
		moved = true;
	}
	if (Input::IsKeyPressed(KeyCode::Q))
	{
		m_Position -= upDirection * speed * deltaTime;
		moved = true;
	}
	else if (Input::IsKeyPressed(KeyCode::E))
	{
		m_Position += upDirection * speed * deltaTime;
		moved = true;
	}

	// Rotation
	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		float pitchDelta = -delta.y * GetRotationSpeed();
		float yawDelta = -delta.x * GetRotationSpeed();

		glm::quat q = glm::normalize(glm::cross(glm::angleAxis(glm::radians(pitchDelta), rightDirection), glm::angleAxis(glm::radians(yawDelta), upDirection)));
		m_ForwardDirection = glm::rotate(q, m_ForwardDirection);

		moved = true;
	}

	if (moved)
	{
		RecalculateViewMatrix();
		RecaluclateRayDirections();
	}
}

void Camera::OnResize(uint32_t width, uint32_t height)
{
	if (m_ViewportWidth == width && m_ViewportHeight == height)
		return;

	m_ViewportWidth = width;
	m_ViewportHeight = height;

	RecalculateProjectionMatrix();
	RecaluclateRayDirections();
}

float Camera::GetRotationSpeed()
{
	return 0.3f;
}

void Camera::RecalculateProjectionMatrix()
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_VerticalFov), (float)m_ViewportWidth / (float)m_ViewportHeight, m_NearClip, m_FarClip);
	m_InverseProjectionMatrix = glm::inverse(m_ProjectionMatrix);
}

void Camera::RecalculateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0.0f, 1.0f, 0.0f));
	m_InverseViewMatrix = glm::inverse(m_ViewMatrix);
}

void Camera::RecaluclateRayDirections()
{
	m_RayDirections.resize(m_ViewportWidth * m_ViewportHeight);

	for (uint32_t y = 0; y < m_ViewportHeight; y++)
	{
		for (uint32_t x = 0; x < m_ViewportWidth; x++)
		{
			glm::vec2 coord = { (float)x / (float)m_ViewportWidth, (float)y / (float)m_ViewportHeight };
			coord = coord * 2.0f - 1.0f; // [0, 1] -> [-1, 1]

			glm::vec4 target = m_InverseProjectionMatrix * glm::vec4(coord.x, coord.y, 1.0f, 1.0f);
			target /= target.w;

			glm::vec3 rayDirection = glm::vec3(m_InverseViewMatrix * glm::vec4(glm::normalize(glm::vec3(target)), 0)); // World space

			m_RayDirections[y * m_ViewportWidth + x] = rayDirection;
		}
	}
}