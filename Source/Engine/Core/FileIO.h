#pragma once
#include <filesystem>
#include <string>

namespace jojo
{
	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& path);
	std::string GetFileName(const std::filesystem::path& path);

	bool fileExsists(const std::filesystem::path& path);
	bool getFileSize(const std::filesystem::path& path, size_t& size);
	bool readFile(const std::filesystem::path& path, std::string& buffer);
	void writeFile(const std::filesystem::path& path, std::string& text);
	std::string loadFile(const std::filesystem::path& path); 

}
