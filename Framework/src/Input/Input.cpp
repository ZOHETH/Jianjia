#include "Input.h"

#include <GLFW/glfw3.h>

#include "Application.h"

namespace jjf {
	bool Input::IsKeyPressed(KeyCode key)
	{
		GLFWwindow* window = Application::Get().GetWindowHandle();
		int state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseButton button)
	{
		GLFWwindow* window = Application::Get().GetWindowHandle();
		int state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = Application::Get().GetWindowHandle();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos};
	}

	void Input::SetCursorMode(CursorMode mode)
	{
		GLFWwindow* window = Application::Get().GetWindowHandle();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + static_cast<int32_t>(mode));
	}
}
