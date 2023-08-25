#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace jojo
{
	CLASS_DEFINITION(Sprite)

	bool Sprite::Initialize()
	{
		if (!texturename.empty()) m_texture = GET_RESOURCE(Texture,texturename, g_renderer);
		if (source.w == 0 && source.h == 0)
		{
			if (m_texture)
			{
				source.x = 0;
				source.y = 0;
				source.w = int(m_texture->GetSize().x);
				source.h = int(m_texture->GetSize().y);
			}
		}

		return true;
	}

	void jojo::Sprite::Update(float dt)
	{
		//
	}

	void jojo::Sprite::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), source, m_owner->transform);
	}

	void Sprite::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, texturename);
		READ_DATA(value, source);
	}
}
