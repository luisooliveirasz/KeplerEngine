#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

class Shader
{
	private:
		static GLint GetUniformLocation(GLuint program, const std::string& name);

	public:
		unsigned int ID;
		
		Shader(const char* vertexPath, const char* fragmentPath);
		
		void Use();
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetIntArray(const std::string& name, int* values, uint32_t count) const;
		void SetMat4(const std::string& name, const glm::mat4& mat) const;
};