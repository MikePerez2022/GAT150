#include "Font.h"
#include "Core/Logger.h"
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

	bool Font::Load(const std::string& fileName, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(fileName.c_str(), fontSize);
		if (!m_ttfFont) 
		{
			WARNING_LOG("Failed tp open font: " << fileName);
			return false;
		}
		return true;
	}

	bool Font::Create(std::string filename, ...)
	{
		va_list args;

		va_start(args, filename);

		int fontSize = va_arg(args, int);

		va_end(args);

		return Load(filename, fontSize);
	}
}