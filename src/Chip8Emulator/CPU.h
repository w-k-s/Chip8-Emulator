#pragma once

#include "Memory.h"
#include "Opcode.h"

class CPU{

private:
	static const int STACK_SIZE = 16;
	
	int _programCounter;
	int _stackPointer;
	uint16_t _indexRegister;
	byte _stack[STACK_SIZE];
	byte _V[16];
	byte * _memory;

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

	void jumpToAddressNNN(const uint16_t nnn);

	void invokeSubroutine(const uint16_t nnn);

	void skipNextIfVxEqualsNN(const byte vx, const byte nn);

	void skipNextIfVxNotEqualsNN(const byte vx, const byte nn);

	void skipNextIfVxEqualsVy(const byte vx, const byte vy);

	void setVxToNN(const byte x, const byte nn);

	void addNNtoVx(const byte x, const byte nn);

	void setVxToVy(const byte x, const byte y);

	void bitwiseOr(const byte x, const byte y);

	void bitwiseAnd(const byte x, const byte y);

	void bitwiseXor(const byte x, const byte y);

	void sumWithVariable(const byte x, const byte vx, const byte vy);

	void subtractVyFromVx(const byte x, const byte vx, const byte vy);

	void bitwiseShiftRightByOne(const byte x);

	void subtractWithDifference(const byte x, const byte vx, const byte vy);

	void bitwiseShiftLeftByOne(const byte xopcode);

	void skipNextIfVxNotEqualsVy(const byte vx, const byte vy);

	void setIndexRegisterAddress(const uint16_t nnn);

	void jumpToAddressNNNPlusV0(const uint16_t nnn);

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
	CPU(byte * memory);
	void run();
	~ CPU();
};