#pragma once
#include "Framework/Resource/Resource.h"
#include <string>

struct _TTF_Font;

namespace jojo
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& fileName, int fontSize);
		~Font();

		bool Load(const std::string& fileName, int fontSize);

		friend class Text;

		// Inherited via Resource
		virtual bool Create(std::string filename, ...) override;

	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}