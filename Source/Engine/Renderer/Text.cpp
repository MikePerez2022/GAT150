#include "Text.h"
#include "Font.h"
#include "SDL2-2.28.0/include/SDL_ttf.h"
#include "Renderer.h"

namespace jojo
{
	Text::~Text()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	void Text::Create(Renderer& renderer, const std::string& text, const Color& color)
	{
		SDL_Color c{ Color::ToInt(color.r), Color::ToInt(color.g), Color::ToInt(color.b), Color::ToInt(color.a) };

		SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
	}

	void Text::Draw(Renderer& renderer, int x, int y)
	{
		int width, height;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);

		SDL_Rect rect{ x, y, width, height };
		SDL_RenderCopy(renderer.m_renderer, m_texture, NULL, &rect);



	}

	void Text::Draw(Renderer& renderer, const Transform& transform)
	{
		int width, height;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
		mat3 mx = transform.GetMatrix();
		vec2 position = mx.GetTranslation();
		vec2 size = vec2{ width, height } *mx.GetScale();
		SDL_Rect dest;
		dest.x = (int)(position.x - (size.x * 0.5f));
		dest.y = (int)(position.y - (size.y * 0.5f));
		dest.w = (int)size.x;
		dest.h = (int)size.y;
		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(renderer.m_renderer, m_texture, nullptr, &dest, jojo::RadiansToDegrees(mx.GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}
