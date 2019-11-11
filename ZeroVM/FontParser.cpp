#include "FontParser.h"
#include <iostream>
#include <fstream>

namespace FontParser {
	
	bool TryParseInt(std::string *str, int *val) {
		std::string num = "";
		try {
			for (int i = 0; i < str->size(); i++) {
				char c = str->at(i);
				if (isspace(c)) break;
				if (!isdigit(c)) throw new std::invalid_argument("'" + *str + "' is an invalid Base10 number");
				num.push_back(c);
			}
			*val = std::stoi(num, nullptr, 10);
			return true;
		} catch (...) {
			return false;
		}
	}

	void ParseFontFile(std::string path, bool arr[], int arrSize, int fontWidth, int fontHeight) {
		int fontSize = fontWidth * fontHeight;
		for (int i = 0; i < arrSize; i++) { //Initalize array to alternating bit pattern


			arr[i] = ((i / fontWidth) % 2 == 0) ? (i % 2 == 0) : (i % 2 != 0);
		}
		std::ifstream fontfile(path);
		if (fontfile.is_open()) {
			int b = 0;
			int ln = 1;
			std::string line;
			while (getline(fontfile, line)) {
				if (line[0] == ':') {
					int nB = 0;
					if (TryParseInt(&line.substr(1, line.size() - 1), &nB)) {
						b = nB * fontSize;
						if (b >= arrSize) {
							std::cout << "Font character " + std::to_string(nB) + " is out of bounds" << std::endl;
							return;
						}
					} else {
						std::cout << "Invalid font char found on line " + std::to_string(ln) << std::endl;
						return;
					}
				} else if (line[0] == '|') {
					for (int i = 1; i < line.size(); i++) {
						if (line[i] == '|') break;
						if (line[i] == '#') {
							arr[b++] = true;
						} else {
							arr[b++] = false;
						}
						if (b >= arrSize) {
							std::cout << "Font array size exceeded on line " + std::to_string(ln) << std::endl;
							return;
						}
					}
				}
				ln++;
			}
		} else {
			std::cout << "Unable to open font file '" + path + "'" << std::endl;
		}
	}

}