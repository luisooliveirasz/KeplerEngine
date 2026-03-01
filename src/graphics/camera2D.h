#pragma once

#include <glm/glm.hpp>

class Camera2D
{
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec2 m_Position = { 0.0f, 0.0f };
		glm::vec2 m_Offset = { 0.0f, 0.0f };
		glm::vec2 m_ViewSize;
		float m_Rotation = 0.0f;
		float m_Zoom;

	public:
		Camera2D(float viewWidth, float viewHeight);

		void SetPosition(const glm::vec2& newPosition);
		void Move(const glm::vec2& delta);

		void SetRotation(float newRotation);
		void Rotate(float delta);

		void SetZoom(float newZoom);
		void Zoom(float delta);

		void UpdateViewMatrix();

		// Getters
		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4& GetViewMatrix();
		const glm::mat4& GetViewProjectionMatrix();

		const glm::vec2& GetPosition() const;
		const glm::vec2& GetViewSize() const;
		float GetRotation();
		float GetZoom();
};