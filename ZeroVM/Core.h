#pragma once
#include <cstdint>
#include <vector>
namespace ZeroSys {
	enum CoreMode { Irq, System, User };

	typedef bool(*CoreBusReadFunction)(uint32_t addr, uint8_t len, int32_t& data);
	typedef bool(*CoreBusWriteFunction)(uint32_t addr, uint8_t len, int32_t data);

	class Core {
	public:
		std::vector<int32_t> DataStack;
		std::vector<int32_t> ReturnStack;
		uint32_t DataStackPtrs[3];
		uint32_t ReturnStackPtrs[3];
		uint32_t StackSize;
		CoreMode Mode;
		CoreBusReadFunction BusRead;
		CoreBusWriteFunction BusWrite;
	public:
		Core(uint32_t stackSize);
		
		void ConnectBus(CoreBusReadFunction readF, CoreBusWriteFunction writeF); //Connect the core to an external bus
		
		/*void Cycle(); //Perform a single instruction cycle
		void VectoredReset(); //Perform a reset using the in-memory reset vector
		void FixedReset(uint32_t vector); //Perform a reset to a specified fixed location
		void Irq(); //Raise an interrupt
		void Nmi(); //Raise a non-maskable interrupt
		*/


	};


}



