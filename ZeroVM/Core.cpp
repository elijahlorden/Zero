#include "Core.h"
namespace ZeroSys {

	Core::Core(uint32_t stackSize) {
		this->StackSize = stackSize;
		this->DataStack.resize(stackSize * 3, 0);
		this->ReturnStack.resize(stackSize * 3, 0);
		this->Mode = System;
		for (int i = 0; i < 6; i++) {
			this->DataStackPtrs[i] = 0;
			this->ReturnStackPtrs[i] = 0;
		}
	}

	void Core::ConnectBus(CoreBusReadFunction readF, CoreBusWriteFunction writeF) {
		this->BusRead = readF;
		this->BusWrite = writeF;
	}

}