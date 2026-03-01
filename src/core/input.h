#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

class Input
{
	private:
		static GLFWwindow* m_Window;

		static std::unordered_map<int, bool> m_CurrentKeys;
		static std::unordered_map<int, bool> m_PreviousKeys;

	public:
		static void Init(GLFWwindow* window);
		static void Update();

		static bool GetKey(int key);
		static bool GetKeyDown(int key);
		static bool GetKeyUp(int key);

		static bool GetMouseButton(int button);
		static void GetMousePosition(double& x, double& y);
};