#include "AseraiEnginePCH.h"
#include "AseraiEngine/Platform/FileDialog.h"

#include <commdlg.h>

namespace Aserai
{
	std::string FileDialog::OpenFile(const char* filter)
	{
		char szFile[256] = {};
		OPENFILENAMEA ofn = {};
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn))
			return ofn.lpstrFile;

		return {};
	}

	std::string FileDialog::SaveFile(const char* filter)
	{
		char szFile[256] = {};
		OPENFILENAMEA ofn = {};
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileNameA(&ofn))
			return ofn.lpstrFile;

		return {};
	}
}
