#pragma once
#include <string>

namespace FontParser {

	void ParseFontFile(std::string path, bool arr[], int arrSize, int fontWidth, int fontHeight);

	bool TryParseInt(std::string *str, int *val);

}