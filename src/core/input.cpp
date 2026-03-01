#include "input.h"

#include <GLFW/glfw3.h>
#include <unordered_map>

GLFWwindow* Input::m_Window = nullptr;

std::unordered_map<int, bool> Input::m_CurrentKeys;
std::unordered_map<int, bool> Input::m_PreviousKeys;

void Input::Init(GLFWwindow* window)
{
	m_Window = window;
}

void Input::Update()
{
	m_PreviousKeys = m_CurrentKeys;

	for (auto& [key, value] : m_CurrentKeys)
	{
		m_CurrentKeys[key] = glfwGetKey(m_Window, key) == GLFW_PRESS;
	}
}

bool Input::GetKey(int key)
{
	bool pressed = glfwGetKey(m_Window, key) == GLFW_PRESS;
	m_CurrentKeys[key] = pressed;
	return pressed;
}

bool Input::GetKeyDown(int key)
{
	return m_CurrentKeys[key] && !m_PreviousKeys[key];
}

bool Input::GetKeyUp(int key)
{
	return !m_CurrentKeys[key] && m_PreviousKeys[key];
}

bool Input::GetMouseButton(int button)
{
	return glfwGetMouseButton(m_Window, button) == GLFW_PRESS;
}

void Input::GetMousePosition(double& x, double& y)
{
	glfwGetCursorPos(m_Window, &x, &y);
}