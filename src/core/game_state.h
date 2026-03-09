#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../graphics/renderer2D.h"
#include "../graphics/texture_manager.h"

class GameState
{
    private:
        static GameState* s_Instance;

        GLFWwindow* m_Window;
        Renderer2D* m_Renderer2D;
        TextureManager* m_TextureManager;

        GameState(GLFWwindow* window, Renderer2D* renderer2D, TextureManager* textureManager);

    public:
        static void Init(GLFWwindow* window, Renderer2D* renderer2D, TextureManager* textureManager);
        static GameState* GetInstance();

        GLFWwindow* GetWindow() const;
        Renderer2D* GetRenderer() const;
        TextureManager* GetTextureManager() const;
};