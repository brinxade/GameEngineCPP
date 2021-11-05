#pragma once
#include<string>

namespace Utility
{
	class StringFunctions
	{
	public:
		static std::string getFilenameFromPath(std::string path, bool stripExt = false);
	};
	
}