#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "System.h"
#include "FontParser.h"


class EngineInterface : public olc::PixelGameEngine {
public:
	EngineInterface() {
		sAppName = "ZeroCPU Virtual Test Environment";
	}
private:
	olc::Pixel charToPixel(uint8_t color) { //Convert an 8-bit truecolor value into a pixel with a 32-bit truecolor value
		return { (uint8_t)((((float)((color & (uint8_t)0xE0) >> 5 ) / 7.0f) * 255.0f)), (uint8_t)((((float)((color & (uint8_t)0x1C) >> 2) / 7.0f) * 255.0f)), (uint8_t)((((float)((color & (uint8_t)0x03)) / 3.0f) * 255.0f)) };
	}

	void DrawChar(int sX, int sY, uint8_t character, olc::Pixel forePixel, olc::Pixel backPixel) { //Draw a single character
		int i = ZeroSys::FontSize * character;
		int mxY = sY + ZeroSys::FontHeight;
		int mxX = sX + ZeroSys::FontWidth;
		for (int y = sY; y < mxY; y++) {
			for (int x = sX; x < mxX; x++) {
				if (ZeroSys::Font[i++]) {
					Draw(x, y, forePixel);
				} else {
					Draw(x, y, backPixel);
				}
			}
		}
	}

	void DrawScreen() { //Draw the screen buffer, may cause calling thread to block
		int y;
		for (int row = 0; row < ZeroSys::ScreenRows; row++) {
			y = row * ZeroSys::FontHeight;
			for (int col = 0; col < ZeroSys::ScreenCols; col++) {
				ZeroSys::ScreenCharacter *character = ZeroSys::GetScreenChar(row, col);
				if (character->Dirty) {
					character->Dirty = false;
					DrawChar(col * ZeroSys::FontWidth, y, character->Character, charToPixel(character->ForeColor), charToPixel(character->BackColor));
				}
				character->mutex.unlock();
			}
		}
	}

	void DrawStr(int x, int y, std::string str, olc::Pixel forePixel, olc::Pixel backPixel) { //Draw a string of characters

	}

	void DrawState(int x, int y) { //Draw the CPU state information
		const std::string stateText[3] = {"Interrupt", "System", "User"};
		const uint32_t stateWidth = (stateText[0].length() * ZeroSys::FontWidth) + ZeroSys::FontWidth;
		DrawRect(x, y, stateWidth, ZeroSys::FontHeight * 4);



	}

	void DrawStack(int x, int y, int32_t *stack, uint32_t sPtr) { //Draw a CPU stack

	}

public:
	bool OnUserCreate() override {
		ZeroSys::Init();
		DrawLine(ZeroSys::ScreenWidth, 0, ZeroSys::ScreenWidth, ZeroSys::ScreenHeight); //Right side screen border
		DrawLine(0, ZeroSys::ScreenHeight, ZeroSys::ScreenWidth, ZeroSys::ScreenHeight); //Bottom side screen border
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		//Draw dirty screen characters
		DrawScreen();
		//Draw CPU state information
		DrawChar(ZeroSys::ScreenWidth + 50, 16, 'F', charToPixel((uint8_t)0xFFFF), charToPixel((uint8_t)0x0000));

		return true;
	}



};

int main() {
	EngineInterface eInterface;
	if (eInterface.Construct(ZeroSys::ScreenWidth + 200, ZeroSys::ScreenHeight, 1, 1)) eInterface.Start();
	return 0;
};