#include "Renderer.h"

static uint32_t ConvertToRGBA(const glm::vec4& color)
{
	uint8_t r = static_cast<uint8_t>(color.r * 255.0f);
	uint8_t g = static_cast<uint8_t>(color.g * 255.0f);
	uint8_t b = static_cast<uint8_t>(color.b * 255.0f);
	uint8_t a = static_cast<uint8_t>(color.a * 255.0f);

	return (a << 24) | (b << 16) | (g << 8) | r;
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		if(m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;
		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<jjf::Image>(width, height, jjf::ImageFormat::RGBA);
	}

	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}

void Renderer::Render(const Camera& camera)
{
	Ray ray;
	ray.Origin = camera.GetPosition();

	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			ray.Direction = camera.GetRayDirections()[y * m_FinalImage->GetWidth() + x];
			glm::vec4 color = TraceRay(ray);
			color = glm::clamp(color, 0.0f, 1.0f);
			m_ImageData[y * m_FinalImage->GetWidth() + x] = ConvertToRGBA(color);
		}
	}

	m_FinalImage->SetData(m_ImageData);
}

glm::vec4 Renderer::TraceRay(const Ray& ray)
{
	float radius = 0.5f;

	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2.0f * glm::dot(ray.Origin, ray.Direction);
	float c = glm::dot(ray.Origin, ray.Origin) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return {0, 0, 0, 1};

	float closestT = (-b - sqrt(discriminant)) / (2.0f * a);
	float t0 = (-b + sqrt(discriminant)) / (2.0f * a);

	glm::vec3 hitPoint = ray.Origin + ray.Direction * closestT;
	glm::vec3 normal = glm::normalize(hitPoint);

	glm::vec3 lightDirection = glm::normalize(glm::vec3(1, 1, 1));
	float lightIntensity = glm::max(glm::dot(normal, lightDirection), 0.0f);

	glm::vec3 sphereColor = { 1.0f, 0.0f, 1.0f };
	glm::vec3 lightColor = { 1.0f, 1.0f, 1.0f };
	sphereColor = sphereColor * lightIntensity * lightColor;
	return glm::vec4(sphereColor, 1.0f);
}
