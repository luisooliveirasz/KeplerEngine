#include "game_object.h"
#include "../core/game_state.h"
#include "../graphics/renderer2D.h"
#include <cmath>

GameObject::GameObject()
    : m_Position(0.0f, 0.0f),
    m_Speed(0.0f, 0.0f),
    m_Scale(1.0f, 1.0f),
    m_Rotation(0.0f),
    m_Active(true),
    m_SpriteIndex(nullptr),
    m_Depth(0.0f)
{
}

GameObject::GameObject(const glm::vec2& position)
    : m_Position(position),
    m_Speed(0.0f, 0.0f),
    m_Scale(1.0f, 1.0f),
    m_Rotation(0.0f),
    m_Active(true),
    m_SpriteIndex(nullptr),
    m_Depth(0.0f)
{
}

const glm::vec2& GameObject::GetPosition() const
{
    return m_Position;
}

const glm::vec2& GameObject::GetSpeed() const
{
    return m_Speed;
}

const glm::vec2& GameObject::GetScale() const
{
    return m_Scale;
}

float GameObject::GetRotation() const
{
    return m_Rotation;
}

bool GameObject::IsActive() const
{
    return m_Active;
}

void GameObject::SetPosition(const glm::vec2& position)
{
    m_Position = position;
}

void GameObject::SetSpeed(const glm::vec2& speed)
{
    m_Speed = speed;
}

void GameObject::SetScale(const glm::vec2& scale)
{
    m_Scale = scale;
}

void GameObject::SetRotation(float rotation)
{
    m_Rotation = rotation;
}


void GameObject::SetSprite(Sprite* sprite)
{
    m_SpriteIndex = sprite;
}

void GameObject::SetActive(bool active)
{
    m_Active = active;
}

void GameObject::Translate(const glm::vec2& delta)
{
    m_Position += delta;
}

void GameObject::Rotate(float deltaAngle)
{
    m_Rotation += deltaAngle;
}

void GameObject::Scale(const glm::vec2& scaleFactor)
{
    m_Scale *= scaleFactor;
}

void GameObject::Update(float deltaTime)
{
    if (!m_Active)
        return;

    m_Position += m_Speed * deltaTime;
}

void GameObject::Draw()
{
    if (m_SpriteIndex == nullptr)
        return;

    Renderer2D* renderer = GameState::GetInstance()->GetRenderer();

    if (renderer == nullptr)
        return;

    glm::vec3 threeDPosition = glm::vec3(m_Position.x, m_Position.y, m_Depth);
    renderer->DrawSprite(m_SpriteIndex, threeDPosition, m_Scale);
}

void GameObject::Move(const glm::vec2& direction, float speed)
{
    if (glm::length(direction) > 0.0f)
    {
        glm::vec2 normalized = glm::normalize(direction);
        m_Position += normalized * speed;
    }
}

void GameObject::Reset()
{
    m_Position = glm::vec2(0.0f, 0.0f);
    m_Speed = glm::vec2(0.0f, 0.0f);
    m_Scale = glm::vec2(1.0f, 1.0f);
    m_Rotation = 0.0f;
    m_Active = true;
}

float GameObject::DistanceTo(const GameObject& other) const
{
    return glm::distance(m_Position, other.m_Position);
}