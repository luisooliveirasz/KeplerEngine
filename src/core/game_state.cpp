#include "game_state.h"
#include <stdexcept>

GameState* GameState::s_Instance = nullptr;

GameState::GameState(GLFWwindow* window, Renderer2D* renderer2D)
    : m_Window(window), m_Renderer2D(renderer2D)
{
}

void GameState::Init(GLFWwindow* window, Renderer2D* renderer2D)
{
    if (s_Instance != nullptr)
        throw std::runtime_error("GameState already initialized!");

    s_Instance = new GameState(window, renderer2D);
}

GameState* GameState::GetInstance()
{
    return s_Instance;
}

GLFWwindow* GameState::GetWindow() const
{
    return m_Window;
}

Renderer2D* GameState::GetRenderer() const
{
    return m_Renderer2D;
}