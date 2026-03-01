#pragma once

#include <GLFW/glfw3.h>

class Time
{
	private:
		static double m_LastTime;
		static float m_Delta;

	public:
		static void Init();
		static void Update();

		// Getters
		static float TotalTime() { return (float)glfwGetTime(); }
		static float DeltaTime() { return m_Delta; }
};