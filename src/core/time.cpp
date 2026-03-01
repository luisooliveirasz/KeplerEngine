#include <GLFW/glfw3.h>
#include "time.h"

double Time::m_LastTime = 0.0;
float Time::m_Delta = 0.0f;

void Time::Init()
{
	m_LastTime = glfwGetTime();
	m_Delta = 0.0f;
}

void Time::Update()
{
	double now = glfwGetTime();
	m_Delta = (float)(now - m_LastTime);
	m_LastTime = now;
}