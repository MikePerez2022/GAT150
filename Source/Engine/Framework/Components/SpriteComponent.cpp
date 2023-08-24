#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace jojo
{
	CLASS_DEFINITION(Sprite)

	bool Sprite::Initialize()
	{
		if (texturename.empty()) return false;
		
		m_texture = GET_RESOURCE(Texture,texturename, g_renderer);

		return true;
	}

	void jojo::Sprite::Update(float dt)
	{
		//
	}

	void jojo::Sprite::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void Sprite::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, texturename);
	}
}
