#pragma once

#include <random>

#include "Memory.h"
#include "Opcode.h"

class CPU{

private:
	static const int STACK_SIZE = 16;
	static const int REGISTER_COUNT = 16;

	int _programCounter;
	int _stackPointer;
	uint16_t _indexRegister;
	byte _stack[STACK_SIZE];
	byte _V[REGISTER_COUNT];
	byte * _memory;
	byte _delayTimer;
	byte _soundTimer;

	std::mt19937 _randomNumberGenerator;
	std::uniform_real_distribution<byte> _randomNumberDistribution;

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

	void subtractVxFromVy(const byte x, const byte vx, const byte vy);

	void bitwiseShiftLeftByOne(const byte x);

	void skipNextIfVxNotEqualsVy(const byte vx, const byte vy);

	void setIndexRegisterAddress(const uint16_t nnn);

	void jumpToAddressNNNPlusV0(const uint16_t nnn);

	void setVxToBitwiseAndOfRandomNumberAndNN(const byte x, const byte nn);

	void drawSprite(const Opcode opcode);

	void skipNextIfKeyInVxIsPressed(const Opcode opcode);

	void skipNextIfKeyInVxIsNotPressed(const Opcode opcode);

	void assignDelayTimerToVx(const byte x);

	void getKey(const Opcode opcode);

	void setDelayTimerToVx(const byte vx);

	void setSoundTimerToVx(const byte vx);

	void addVxToIndexRegister(const byte x, const byte vx);

	void setIndexRegisterToSpriteLocation(const Opcode opcode);

	void setBinaryCodedDecimalAtVx(const byte vx);

	void dumpRegisters(const byte x);

	void loadRegisters(const byte x);

public:
	CPU(byte * memory);
	CPU(const CPU&)				= delete;
	void operator=(const CPU&)	= delete;
	
	void run();
	~ CPU();
};