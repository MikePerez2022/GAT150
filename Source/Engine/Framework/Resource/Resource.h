#pragma once
#include <string>

namespace jojo
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) = 0;
	};
}