#include "AseraiEnginePCH.h"
#include "AseraiEngine/Utils/FileIO.h"
#include "AseraiEngine/Core/Logger.h"

#include <fstream>
#include <sstream>

namespace Aserai
{
	std::string FileIO::ReadFileContent(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		if (stream.fail())
		{
			ASERAI_LOG_ERROR("FILEIO FAILED TO OPEN {}", filepath);
			return {};
		}

		std::stringstream ss;
		std::string line;
		while (std::getline(stream, line))
			ss << line << "\n";

		stream.close();
		return ss.str();
	}

	void FileIO::WriteFileContent(const std::string& filepath, const std::string& data)
	{
		std::ofstream fout(filepath);
		fout << data.c_str();
	}
}
