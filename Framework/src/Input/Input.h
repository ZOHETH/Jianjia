#pragma once

#include <glm/glm.hpp>

#include "KeyCodes.h"

namespace jjf {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseButton button);

		static glm::vec2 GetMousePosition();
		
		static void SetCursorMode(CursorMode mode);
	};
}