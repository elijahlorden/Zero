#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "Core.h"
#include "System.h"
#include "FontParser.h"

using namespace std;

namespace ZeroSys {

	ScreenCharacter Screen[ScreenCols * ScreenRows];
	bool Font[(FontWidth * FontHeight) * 256];

	uint8_t InitMemory[InitMemorySize];

	Core* CPU;
	
	ScreenCharacter* GetScreenChar(int row, int col) { //Get a screen character, caller must unlock mutex after it has finished with it.
		ScreenCharacter* sChar = &Screen[(row * ScreenCols) + col];
		sChar->mutex.lock();
		return sChar;
	}

	//Screen bus interface read/write functions

	//Init Memory read/write functions

	bool ReadInitMem(uint32_t addr, uint8_t& data) {
		if (addr >= InitMemorySize) return false;
		data = InitMemory[addr];
		return true;
	}

	bool WriteInitMem(uint32_t addr, uint8_t data) {
		if (addr >= InitMemorySize) return false;
		InitMemory[addr] = data;
		return true;
	}

	//Bus map declaration

	BusDevice BusDevices[2] = {
		//Init RAM occupies 0x00000001 - 0x00008000
		{
			0x00000001u,
			0x00008000u,
			ReadInitMem,
			WriteInitMem
		},
		//VRAM starts at 0x00009000 and extends (ScreenCols * ScreenRows) bytes
		{
			0x00009000u,
			0x00009000u + (uint32_t)(ScreenCols * ScreenRows),


		},
	};

	//Main CPU bus read/write functions

	bool MainBusRead(uint32_t addr, uint8_t len, int32_t& data) {



		return true;
	}

	bool MainBusWrite(uint32_t addr, uint8_t len, int32_t data) {



		return true;
	}



	void Init() {
		cout << "Initializing ZeroSys" << std::endl;
		//Read font file into memory
		FontParser::ParseFontFile("Font", ZeroSys::Font, sizeof(ZeroSys::Font), ZeroSys::FontWidth, ZeroSys::FontHeight);
		
		//Initalize screen memory to null characters with a white foreground and black background
		for (int i = 0; i < ScreenCells; i++) {
			Screen[i].mutex.lock();
			Screen[i].Character = (unsigned char)0x00u;
			Screen[i].ForeColor = (unsigned char)0xFFu;
			Screen[i].BackColor = (unsigned char)0x00u;
			Screen[i].Dirty = true;
			Screen[i].mutex.unlock();
		}
		//Test assignment
		int x = 0;
		int y = 0;
		int rI;
		for (int i = 0; i < 256; i++) {
			rI = x + (y * ScreenCols);
			Screen[rI].mutex.lock();
			Screen[rI].Character = (uint8_t)i;
			Screen[rI].mutex.unlock();
			if (x == 15) {
				x = 0;
				y++;
			} else x++;
		}
		//Instantiate the CPU core
		CPU = new Core(128u);
		CPU->ConnectBus(MainBusRead, MainBusWrite);
	}


}