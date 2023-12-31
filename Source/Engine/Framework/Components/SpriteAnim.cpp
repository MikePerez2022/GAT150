#include "SpriteAnim.h"
#include "Framework/Resource/ResourceManager.h"
#include "Renderer/Renderer.h"

namespace jojo
{
	CLASS_DEFINITION(SpriteAnim);

	bool SpriteAnim::Initialize()
	{
		Sprite::Initialize();

		SetSequence(defaultSequenceName, false);
		if(source.w == 0 && source.h == 0) UpdateSource();

		return true;
	}

	void jojo::SpriteAnim::Update(float dt)
	{
		frameTime -= dt;
		if (frameTime <= 0)
		{
			frameTime = 1.0f / m_sequence->fps;
			frame++;
			if (frame > m_sequence->endFrame)
			{
				frame = (m_sequence->loop) ? m_sequence->startFrame : m_sequence->endFrame;
			}

		}

		UpdateSource();
	}

	void SpriteAnim::SetSequence(const std::string& name, bool update)
	{
		if (m_sequence && m_sequence->name == name) return;

		if (m_sequences.find(name) != m_sequences.end())
		{
			m_sequence = &m_sequences[name];
			if(m_sequence->texture) m_texture = m_sequence->texture;
			frame = m_sequence->startFrame;
			frameTime = 1.0f / m_sequence->fps;

			if(update) UpdateSource();
		}
	}

	void SpriteAnim::UpdateSource()
	{
		vec2 cellSize = m_texture->GetSize() / vec2{m_sequence->numColumns, m_sequence->numRows};

		int collum = (frame - 1) % m_sequence->numColumns;
		int row = (frame - 1) / m_sequence->numColumns;

		source.x = (int)(collum * cellSize.x);
		source.y = (int)(row * cellSize.y);
		source.w = (int)(cellSize.x);
		source.h = (int)(cellSize.y);
	}

	void SpriteAnim::Read(const rapidjson::Value& value)
	{
		Sprite::Read(value);

		// read in animation sequences
		if (HAS_DATA(value, sequences) && GET_DATA(value, sequences).IsArray())
		{
			for (auto& sequenceValue : GET_DATA(value, sequences).GetArray())
			{
				AnimSequence sequence;

				READ_NAME_DATA(sequenceValue, "name", sequence.name);
				READ_NAME_DATA(sequenceValue, "fps", sequence.fps);
				READ_NAME_DATA(sequenceValue, "numColumns", sequence.numColumns);
				READ_NAME_DATA(sequenceValue, "numRows", sequence.numRows);
				READ_NAME_DATA(sequenceValue, "startFrame", sequence.startFrame);
				READ_NAME_DATA(sequenceValue, "endFrame", sequence.endFrame);

				// read texture
				std::string textureName;
				READ_DATA(sequenceValue, textureName);
				sequence.texture = GET_RESOURCE(Texture, textureName, g_renderer);

				m_sequences[sequence.name] = sequence;
			}
		}

		if (!READ_DATA(value, defaultSequenceName))
		{
			// if default sequence not specified, use the first sequence in the sequences map
			defaultSequenceName = m_sequences.begin()->first;
		}

	}
}