#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Image.h"

#include "Camera.h"
#include "Ray.h"

class Renderer
{
public:
	Renderer() = default;

	void OnResize(uint32_t width, uint32_t height);
	void Render(const Camera& camera);

	std::shared_ptr<jjf::Image> GetFinalImage() const { return m_FinalImage; }
private:
	glm::vec4 TraceRay(const Ray& ray);
private:
	std::shared_ptr<jjf::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;
};