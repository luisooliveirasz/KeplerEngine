#pragma once

#include "Sprite.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <vector>
#include <stddef.h>

class Renderer2D
{
	private:
		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 TexCoord;
			float TexIndex;
		};

		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextures = 16;
		
		GLuint m_VAO, m_VBO, m_IBO;

		uint32_t m_IndexCount = 0;

		QuadVertex* m_VertexBufferBase = nullptr;
		QuadVertex* m_VertexBufferPtr = nullptr;

		std::array<GLuint, MaxTextures> m_TextureSlots;
		uint32_t m_TextureSlotIndex = 1;

		glm::vec4 m_QuadVertexPositions[4] =
		{
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{ +0.5f, -0.5f, 0.0f, 1.0f },
			{ +0.5f, +0.5f, 0.0f, 1.0f },
			{ -0.5f, +0.5f, 0.0f, 1.0f }
		};

	public:
		Renderer2D()
		{
			Init();
		}

		~Renderer2D()
		{
			delete[] m_VertexBufferBase;
			glDeleteBuffers(1, &m_VBO);
			glDeleteBuffers(1, &m_IBO);
			glDeleteVertexArrays(1, &m_VAO);
		}

		void Init()
		{
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(
				GL_ARRAY_BUFFER,
				MaxVertices * sizeof(QuadVertex),
				nullptr,
				GL_DYNAMIC_DRAW
			);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, Position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, Color));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, TexCoord));
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, TexIndex));
			glEnableVertexAttribArray(3);

			// Indices
			std::vector<uint32_t> indices(MaxIndices);
			uint32_t offset = 0;

			for (uint32_t i = 0; i < MaxIndices; i += 6)
			{
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;
				offset += 4;
			}

			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				indices.size() * sizeof(uint32_t),
				indices.data(),
				GL_STATIC_DRAW
			);

			m_VertexBufferBase = new QuadVertex[MaxVertices];
		}

		void BeginBatch()
		{
			m_IndexCount = 0;
			m_VertexBufferPtr = m_VertexBufferBase;
			m_TextureSlotIndex = 1;
		}

		void EndBatch()
		{
			GLsizeiptr size =
				(uint8_t*)m_VertexBufferPtr -
				(uint8_t*)m_VertexBufferBase;

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_VertexBufferBase);

			Flush();
		}

		void Flush()
		{
			for (uint32_t i = 0; i < m_TextureSlotIndex; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, m_IndexCount,
				GL_UNSIGNED_INT, nullptr);
		}

		void DrawQuad(const glm::vec3& position,
			const glm::vec2& size,
			GLuint textureID,
			const glm::vec4& color)
		{
			if (m_IndexCount >= MaxIndices)
			{
				EndBatch();
				BeginBatch();
			}

			float texIndex = 0.0f;

			for (uint32_t i = 1; i < m_TextureSlotIndex; i++)
			{
				if (m_TextureSlots[i] == textureID)
				{
					texIndex = (float)i;
					break;
				}
			}

			if (texIndex == 0.0f)
			{
				if (m_TextureSlotIndex >= MaxTextures)
				{
					EndBatch();
					BeginBatch();
				}

				texIndex = (float)m_TextureSlotIndex;
				m_TextureSlots[m_TextureSlotIndex] = textureID;
				m_TextureSlotIndex++;
			}

			glm::mat4 transform =
				glm::translate(glm::mat4(1.0f), position) *
				glm::scale(glm::mat4(1.0f),
					{ size.x, size.y, 1.0f });

			glm::vec2 texCoords[4] =
			{
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f}
			};

			for (int i = 0; i < 4; i++)
			{
				m_VertexBufferPtr->Position =
					transform * m_QuadVertexPositions[i];
				m_VertexBufferPtr->Color = color;
				m_VertexBufferPtr->TexCoord = texCoords[i];
				m_VertexBufferPtr->TexIndex = texIndex;
				m_VertexBufferPtr++;
			}

			m_IndexCount += 6;
		}

		void DrawSprite(const Sprite& sprite)
		{
			DrawQuad(
				sprite.GetPosition(),
				sprite.GetSize(),
				sprite.GetTextureID(),
				sprite.GetColor()
			);
		}
};