#pragma once

#include <vector>
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(float verticalFov, float nearClip, float farClip);

	void OnUpdate(float deltaTime);
	void OnResize(uint32_t width, uint32_t height);

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GetInverseProjectionMatrix() const { return m_InverseProjectionMatrix; }
	const glm::mat4& GetInverseViewMatrix() const { return m_InverseViewMatrix; }

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetForwardDirection() const { return m_ForwardDirection; }

	const std::vector<glm::vec3>& GetRayDirections() const { return m_RayDirections; }

	float GetRotationSpeed();
private:
	void RecalculateProjectionMatrix();
	void RecalculateViewMatrix();
	void RecaluclateRayDirections();
private:
	glm::mat4 m_ProjectionMatrix{ 1.0f };
	glm::mat4 m_ViewMatrix{ 1.0f };
	glm::mat4 m_InverseProjectionMatrix{ 1.0f };
	glm::mat4 m_InverseViewMatrix{ 1.0f };

	float m_VerticalFov = 45.0f;
	float m_NearClip = 0.1f;
	float m_FarClip = 100.0f;

	glm::vec3 m_Position{ 0.0f, 0.0f, 3.0f };
	glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, -1.0f };

	// Cached ray directions
	std::vector<glm::vec3> m_RayDirections;

	glm::vec2 m_LastMousePosition{ 0.0f };

	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
};



