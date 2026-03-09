#pragma once

#include <glad/glad.h>
#include <string>

class Texture2D
{
    private:
        unsigned int m_ID;
        int m_Width, m_Height, m_Channels;

    public:
        Texture2D(const std::string& path);
        ~Texture2D();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
        unsigned int GetID() const { return m_ID; }
};