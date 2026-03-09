#include "game_state.h"
#include "../graphics/renderer2D.h"
#include "../graphics/texture_manager.h"

#include <stdexcept>

GameState* GameState::s_Instance = nullptr;

GameState::GameState(GLFWwindow* window, Renderer2D* renderer2D, TextureManager* textureManager)
    : m_Window(window), m_Renderer2D(renderer2D), m_TextureManager(textureManager)
{
}

void GameState::Init(GLFWwindow* window, Renderer2D* renderer2D, TextureManager* textureManager)
{
    if (s_Instance != nullptr)
        throw std::runtime_error("GameState already initialized!");

    s_Instance = new GameState(window, renderer2D, textureManager);
}

GameState* GameState::GetInstance() { return s_Instance; }
GLFWwindow* GameState::GetWindow() const { return m_Window; }
Renderer2D* GameState::GetRenderer() const { return m_Renderer2D; }
TextureManager* GameState::GetTextureManager() const { return m_TextureManager; }