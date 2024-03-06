#pragma once

#include <string>

namespace Aserai2D
{
	class FileIO
	{
	public:
		static std::string ReadFileContent(const std::string& filepath);
		static void WriteFileContent(const std::string& filepath, const std::string& data);
	};
}
