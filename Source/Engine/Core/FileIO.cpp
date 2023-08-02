#include "FileIO.h"
#include "Core/Logger.h"
#include <fstream>
#include <iostream>

namespace jojo
{
	std::string getFilePath()
	{
		return std::filesystem::current_path().string();
	}

	bool setFilePath(const std::filesystem::path& path)
	{
		std::error_code ec;
		std::filesystem::current_path(path, ec);

		return ec.value() == 0;
	}

	std::string GetFileName(const std::filesystem::path& path)
	{
		return path.filename().string();
	}

	bool fileExsists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(path);
		
	}

	bool getFileSize(const std::filesystem::path& path, size_t& size)
	{
		std::error_code ec;
		size = std::filesystem::file_size(path, ec);

		return ec.value() == 0;
	}

	bool readFile(const std::filesystem::path& path, std::string& buffer)
	{
		if (!fileExsists(path))
		{
			WARNING_LOG("file not loaded: " << path.string());
			return false;
		}

		size_t size;
		if (!getFileSize(path, size)) return false;

		buffer.resize(size);

		std::ifstream stream(path);
		stream.read(buffer.data(), size);
		stream.close();

		return true;
	}

	void writeFile(const std::filesystem::path& path, std::string& text)
	{
		std::ofstream stream;

		stream.open(path);

		stream << text;

		stream.close();
	}

	std::string loadFile(const std::filesystem::path& path)
	{
		if (!fileExsists(path)) return "";

		size_t size;
		if (!getFileSize(path, size)) return "";

		std::string text;

		text.resize(size);

		std::ifstream stream(path);
		stream.read(text.data(), size);

		stream.close();

		return text;
	}
}