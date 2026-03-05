#pragma once

#include <glm/glm.hpp>
#include "../graphics/sprite.h"

class GameObject
{
private:
    glm::vec2 m_Position;
    glm::vec2 m_Speed;
    glm::vec2 m_Scale;
    float     m_Depth;
    float     m_Rotation;
    Sprite*   m_SpriteIndex;
    bool      m_Active;

public:
    GameObject();
    GameObject(const glm::vec2& position);

    // ===== Getters =====
    const glm::vec2& GetPosition() const;
    const glm::vec2& GetSpeed() const;
    const glm::vec2& GetScale() const;
    float GetRotation() const;
    bool IsActive() const;

    // ===== Setters =====
    void SetPosition(const glm::vec2& position);
    void SetSpeed(const glm::vec2& speed);
    void SetScale(const glm::vec2& scale);
    void SetRotation(float rotation);
    void SetSprite(Sprite* sprite);
    void SetActive(bool active);

    void Translate(const glm::vec2& delta);
    void Rotate(float deltaAngle);
    void Scale(const glm::vec2& scaleFactor);

    void Update(float deltaTime);
    void Draw();
    void Move(const glm::vec2& direction, float speed);

    // ===== Utilidades =====
    void Reset();
    float DistanceTo(const GameObject& other) const;
};