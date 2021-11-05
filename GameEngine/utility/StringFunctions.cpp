#include"StringFunctions.h"

namespace Utility
{
	std::string StringFunctions::getFilenameFromPath(std::string path, bool stripExt)
	{
		std::string filename = path.substr(path.find_last_of("/") + 1, path.length() - 1);

		if (stripExt)
			return filename.substr(0, filename.find_first_of("."));
		return filename;
	}
}