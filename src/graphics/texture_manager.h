#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include "texture2D.h"

class TextureManager
{
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures;

	public:
		TextureManager()
		{

		}

		std::shared_ptr<Texture2D> Load(const std::string& path)
		{
			auto it = m_Textures.find(path);
			if (it != m_Textures.end())
				return it->second;

			auto texture = std::make_shared<Texture2D>(path);
			m_Textures[path] = texture;

			return texture;
		}
};