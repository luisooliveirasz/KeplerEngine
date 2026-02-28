#include "Sprite.h"
#include "texture2D.h"

Sprite::Sprite(const std::shared_ptr<Texture2D>& texture,
    const glm::vec3& position,
    const glm::vec2& size)
    : m_Texture(texture),
    m_Position(position),
    m_Size(size)
{
}

void Sprite::SetPosition(const glm::vec3& position)
{
    m_Position = position;
}

void Sprite::SetSize(const glm::vec2& size)
{
    m_Size = size;
}

void Sprite::SetColor(const glm::vec4& color)
{
    m_Color = color;
}

GLuint Sprite::GetTextureID() const
{
    return m_Texture ? m_Texture->GetID() : 0;
}