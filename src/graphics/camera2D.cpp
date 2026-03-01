#include "camera2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera2D::Camera2D(float viewWidth, float viewHeight)
	: m_ViewSize(viewWidth, viewHeight)
{
	m_ProjectionMatrix = glm::ortho(0.0f, viewWidth, 0.0f, viewHeight);
	m_Rotation = 0.0f;
	m_Zoom = 1.0f;
	UpdateViewMatrix();
}

void Camera2D::SetPosition(const glm::vec2& newPosition)
{
	m_Position = newPosition;
}

void Camera2D::Move(const glm::vec2& delta)
{
	m_Position += delta;
}

void Camera2D::SetRotation(float newRotation)
{
	m_Rotation = newRotation;
}
void Camera2D::Rotate(float delta)
{
	m_Rotation += delta;
}

void Camera2D::SetZoom(float newZoom)
{
	m_Zoom = newZoom;
}
void Camera2D::Zoom(float delta)
{
	m_Zoom += delta;
}

void Camera2D::UpdateViewMatrix()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(m_ViewSize.x / 2, m_ViewSize.y / 2, 0.0f));
	view = glm::translate(view, glm::vec3(-m_Position.x, -m_Position.y, 0.0f));
	view = glm::rotate(view, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::scale(view, glm::vec3(m_Zoom, m_Zoom, 1.0f));
	
	m_ViewMatrix = view;
}

// Getters
const glm::mat4& Camera2D::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

const glm::mat4& Camera2D::GetViewMatrix()
{
	UpdateViewMatrix();
	return m_ViewMatrix;
}

const glm::mat4& Camera2D::GetViewProjectionMatrix()
{
	return m_ProjectionMatrix * GetViewMatrix(); // Projection matrix never changes, but the view matrix does (so we need to call the function)
}

const glm::vec2& Camera2D::GetPosition() const
{
	return m_Position;
}
const glm::vec2& Camera2D::GetViewSize() const
{
	return m_ViewSize;
}
float Camera2D::GetRotation()
{
	return m_Rotation;
}
float Camera2D::GetZoom()
{
	return m_Zoom;
}