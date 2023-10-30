#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Image.h"

class Renderer
{
public:
	Renderer() = default;

	void OnResize(uint32_t width, uint32_t height);
	void Render();

	std::shared_ptr<jjf::Image> GetFinalImage() const { return m_FinalImage; }
private:
	uint32_t PerPixel(glm::vec2 coord);
private:
	std::shared_ptr<jjf::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;
};