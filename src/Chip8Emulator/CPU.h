#pragma once

#include "Memory.h"
#include "Opcode.h"

class CPU{
private:
	int _programCounter;
	int _stackPointer;
	int _indexRegister;
	Memory * _memory;

	void reset();

	void clearStack();
	void clearRegisters();
	void resetTimers();

	/* Loop Cycle */

	void cycle();

	Opcode fetchOpcode();
	void decodeOpcode(Opcode opcode);

	/* Instructions */

	void callProgramAtAddressNNN(const Opcode Opcode);

	void clearScreen();

	void returnFromSubroutine();

	void jumpToAddressNNN(const Opcode opcode);

	void invokeSubroutine(const Opcode opcode);

	void skipNextIfEqualsConstant(const Opcode opcode);

	void skipNextIfNotEqualsConstant(const Opcode opcode);

	void skipNextIfEqualsVariable(const Opcode opcode);

	void set(const Opcode opcode);

	void sumWithConstant(const Opcode opcode);

	void assign(const Opcode opcode);

	void bitwiseOr(const Opcode opcode);

	void bitwiseAnd(const Opcode opcode);

	void bitwiseXor(const Opcode opcode);

	void sumWithVariable(const Opcode opcode);

	void subtractWithVariable(const Opcode opcode);

	void bitwiseShiftRightByOne(const Opcode opcode);

	void subtractWithDifference(const Opcode opcode);

	void bitwiseShiftLeftByOne(const Opcode opcode);

	void skipNextIfNotEqualsVariable(const Opcode opcode);

	void setIndexRegisterAddress(const Opcode opcode);

	void jumpToAddressNNNPlusV0(const Opcode opcode);

	void setVxToBitwiseAndOfRandomNumberAndNN(const Opcode opcode);

	void drawSprite(const Opcode opcode);

	void skipNextIfKeyInVxIsPressed(const Opcode opcode);

	void skipNextIfKeyInVxIsNotPressed(const Opcode opcode);

	void assignDelayTimerToVx(const Opcode opcode);

	void getKey(const Opcode opcode);

	void setVxToDelayTimer(const Opcode opcode);

	void setVxToSoundTimer(const Opcode opcode);

	void addVxToIndexRegister(const Opcode opcode);

	void setIndexRegisterToSpriteLocation(const Opcode opcode);

	void setBinaryCodedDecimalAtVx(const Opcode opcode);

	void dumpRegisters(const Opcode opcode);

	void loadRegisters(const Opcode opcode);

public:
	CPU(Memory * memory);
	void run();
	~ CPU();
};