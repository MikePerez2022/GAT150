#include "Font.h"
#include "../ThirdParty/SDL2-2.28.0/include/SDL_ttf.h"

namespace jojo
{
	Font::Font(const std::string& fileName, int fontSize)
	{
		Load(fileName,fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont != NULL) 
		{
			TTF_CloseFont(m_ttfFont);
		}
	}

	void Font::Load(const std::string& fileName, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(fileName.c_str(), fontSize);
	}
}