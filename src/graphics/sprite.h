#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "texture2D.h"

class Sprite
{
private:
    std::shared_ptr<Texture2D> m_Texture;

    glm::vec3 m_Position;
    glm::vec2 m_Size;
    glm::vec2 m_Scale;
    glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

public:
    Sprite(const std::shared_ptr<Texture2D>& texture,
        const glm::vec3& position,
        const glm::vec2& size);

    void SetPosition(const glm::vec3& position);
    void SetScale(const glm::vec2& scale);
    void SetColor(const glm::vec4& color);

    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::vec2& GetSize() const { return m_Size; }
    const glm::vec2& GetScale() const { return m_Scale; }
    const glm::vec4& GetColor() const { return m_Color; }

    GLuint GetTextureID() const;
};