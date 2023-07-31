#pragma once
#include <string>

struct _TTF_Font;

namespace jojo
{
	class Font
	{
	public:
		Font() = default;
		Font(const std::string& fileName, int fontSize);
		~Font();

		void Load(const std::string& fileName, int fontSize);

		friend class Text;

	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}