#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../graphics/renderer2D.h"

class GameState
{
    private:
        static GameState* s_Instance;

        GLFWwindow* m_Window;
        Renderer2D* m_Renderer2D;

        GameState(GLFWwindow* window, Renderer2D* renderer2D);

    public:
        static void Init(GLFWwindow* window, Renderer2D* renderer2D);
        static GameState* GetInstance();

        GLFWwindow* GetWindow() const;
        Renderer2D* GetRenderer() const;
};