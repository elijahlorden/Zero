#pragma once
#include "Core.h"
#include <mutex>

namespace ZeroSys {

	typedef bool(*BusReadFunction)(uint32_t addr, uint8_t& data);
	typedef bool(*BusWriteFunction)(uint32_t addr, uint8_t data);

	struct ScreenCharacter  {
		unsigned char Character;
		unsigned char BackColor;
		unsigned char ForeColor;
		bool Dirty;
		std::mutex mutex;
	};

	struct BusDevice {
		uint32_t LowerBound;
		uint32_t UpperBound;
		BusReadFunction Read;
		BusWriteFunction Write;
	};

	//800x600 pixel screen with an 8x12 font = 100 columns and 50 rows

	const int ScreenWidth = 800;
	const int ScreenHeight = 600;
	const int FontWidth = 8;
	const int FontHeight = 12;
	const int FontSize = FontWidth * FontHeight;
	const int ScreenCols = (int)(((float)ScreenWidth) / ((float)FontWidth));
	const int ScreenRows = (int)(((float)ScreenHeight) / ((float)FontHeight));
	const int ScreenCells = ScreenCols * ScreenRows;

	const int InitMemorySize = 32768;

	extern ScreenCharacter Screen[];
	extern bool Font[];
	extern BusDevice BusDevices[];

	extern Core* CPU;

	void Init();
	ScreenCharacter* GetScreenChar(int row, int col);


}
