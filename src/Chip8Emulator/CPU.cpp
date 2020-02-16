#include "CPU.h"

#include <iostream>

CPU::CPU(byte* memory)
{
    this->_memory = memory;

    this->reset();
}

CPU::~CPU()
{
    std::cout << "Destroying CPU";
}

void CPU::reset()
{
    this->_programCounter = CHIP_8_EXECUTABLE_ADDRESS;
    this->_stackPointer = 0;
    this->_indexRegister = 0;

    this->clearStack();
    this->clearRegisters();
    // this->resetTimers();
}

void CPU::clearStack()
{
    this->_stackPointer = 0;
    memset(this->_stack, 0, sizeof(this->_stack));
}

void CPU::clearRegisters()
{
    memset(this->_V, 0, sizeof(this->_V));
    ;
}

void CPU::run()
{
    for (;;) {
        this->cycle();
    }
}

void CPU::cycle()
{
    if (this->_programCounter >= CHIP_8_MEMORY_SIZE) {
        //TODO return error
        std::cerr << "Instruction Address outside memory bounds. Expected: 0.." << CHIP_8_MEMORY_SIZE << ", Got: " << this->_programCounter << "\n";
        exit(2);
    }

    const Opcode opcode = this->fetchOpcode();

    this->_programCounter += 2;

    this->decodeOpcode(opcode);
}

Opcode CPU::fetchOpcode()
{
    return this->_memory[this->_programCounter] << 8 | this->_memory[this->_programCounter + 1];
}

void CPU::decodeOpcode(const Opcode opcode)
{
    const byte x = (opcode & 0x0f00) >> 8;
    const byte y = (opcode & 0x00f0) >> 4;

    const byte vx = this->_V[x];
    const byte vy = this->_V[y];

    const byte nn = (opcode & 0x00ff);
    const uint16_t nnn = (opcode & 0x0FFF);

    if (opcode == 0x00E0) {
        this->clearScreen();
    } else if (opcode == 0x00EE) {
        this->returnFromSubroutine();
    } else if ((opcode & 0xF000) == 0x0000) {
        this->callProgramAtAddressNNN(opcode);
    } else if ((opcode & 0xF000) == 0x1000) {
        this->jumpToAddressNNN(nnn);
    } else if ((opcode & 0xF000) == 0x2000) {
        this->invokeSubroutine(nnn);
    } else if ((opcode & 0xF000) == 0x3000) {
        this->skipNextIfVxEqualsNN(vx, nn);
    } else if ((opcode & 0xF000) == 0x4000) {
        this->skipNextIfVxNotEqualsNN(vx, nn);
    } else if ((opcode & 0xF00F) == 0x5000) {
        this->skipNextIfVxEqualsVy(vx, vy);
    } else if ((opcode & 0xF000) == 0x6000) {
        this->setVxToNN(x, nn);
    } else if ((opcode & 0xF000) == 0x7000) {
        this->addNNtoVx(x, nn);
    } else if ((opcode & 0xF00F) == 0x8000) {
        this->setVxToVy(x, y);
    } else if ((opcode & 0xF00F) == 0x8001) {
        this->bitwiseOr(x, y);
    } else if ((opcode & 0xF00F) == 0x8002) {
        this->bitwiseAnd(x, y);
    } else if ((opcode & 0xF00F) == 0x8003) {
        this->bitwiseXor(x, y);
    } else if ((opcode & 0xF00F) == 0x8004) {
        this->sumWithVariable(x, vx, vy);
    } else if ((opcode & 0xF00F) == 0x8005) {
        this->subtractVyFromVx(x, vx, vy);
    } else if ((opcode & 0xF00F) == 0x8006) {
        this->bitwiseShiftRightByOne(x);
    } else if ((opcode & 0xF00F) == 0x8007) {
        this->subtractWithDifference(x, vx, vy);
    } else if ((opcode & 0xF00F) == 0x800E) {
        this->bitwiseShiftLeftByOne(x);
    } else if ((opcode & 0xF00F) == 0x9000) {
        this->skipNextIfVxNotEqualsVy(vx, vy);
    } else if ((opcode & 0xF000) == 0xA000) {
        this->setIndexRegisterAddress(nnn);
    } else if ((opcode & 0xF000) == 0xB000) {
        this->jumpToAddressNNNPlusV0(nnn);
    } else if ((opcode & 0xF000) == 0xC000) {
        this->setVxToBitwiseAndOfRandomNumberAndNN(opcode);
    } else if ((opcode & 0xF000) == 0xD000) {
        this->drawSprite(opcode);
    } else if ((opcode & 0xF0FF) == 0xE09E) {
        this->skipNextIfKeyInVxIsPressed(opcode);
    } else if ((opcode & 0xF0FF) == 0xE0A1) {
        this->skipNextIfKeyInVxIsNotPressed(opcode);
    } else if ((opcode & 0xF0FF) == 0xF007) {
        this->assignDelayTimerToVx(opcode);
    } else if ((opcode & 0xF0FF) == 0xF00A) {
        this->getKey(opcode);
    } else if ((opcode & 0xF0FF) == 0xF015) {
        this->setVxToDelayTimer(opcode);
    } else if ((opcode & 0xF0FF) == 0xF018) {
        this->setVxToSoundTimer(opcode);
    } else if ((opcode & 0xF0FF) == 0xF01E) {
        this->addVxToIndexRegister(opcode);
    } else if ((opcode & 0xF0FF) == 0xF029) {
        this->setIndexRegisterToSpriteLocation(opcode);
    } else if ((opcode & 0xF0FF) == 0xF033) {
        this->setBinaryCodedDecimalAtVx(opcode);
    } else if ((opcode & 0xF0FF) == 0xF055) {
        this->dumpRegisters(opcode);
    } else if ((opcode & 0xF0FF) == 0xF065) {
        this->loadRegisters(opcode);
    } else {
        std::cerr << "Unknwown opcode: '" << opcode << "'\n";
    }
}

inline void CPU::callProgramAtAddressNNN(const Opcode Opcode)
{
    // Do nothing
}

inline void CPU::clearScreen()
{
}

inline void CPU::returnFromSubroutine()
{
    if (this->_stackPointer == 0) {
        // TODO: raise error
        std::cerr << "Stack underflow";
        exit(1);
    }

    this->_programCounter = this->_stack[--this->_stackPointer];
}

inline void CPU::jumpToAddressNNN(const uint16_t nnn)
{
    this->_programCounter = nnn;
}

inline void CPU::invokeSubroutine(const uint16_t nnn)
{
    if (this->_stackPointer + 1 >= STACK_SIZE) {
        // TODO: raise error
        std::cerr << "Stack overflow\n";
        exit(1);
    }

    this->_stack[this->_stackPointer++] = this->_programCounter;
    this->_programCounter = nnn;
}

inline void CPU::skipNextIfVxEqualsNN(const byte vx, const byte nn)
{
    if (vx == nn) {
        this->_programCounter += 2;
    }
}

inline void CPU::skipNextIfVxNotEqualsNN(const byte vx, const byte nn)
{
    if (vx != nn) {
        this->_programCounter += 2;
    }
}

inline void CPU::skipNextIfVxEqualsVy(const byte vx, const byte vy)
{
    if (vx == vy) {
        this->_programCounter += 2;
    }
}

inline void CPU::setVxToNN(const byte x, const byte nn)
{
    this->_V[x] = nn;
}

inline void CPU::addNNtoVx(const byte x, const byte nn)
{
    this->_V[x] += nn;
}

inline void CPU::setVxToVy(const byte x, const byte y)
{
    this->_V[x] = this->_V[y];
}

inline void CPU::bitwiseOr(const byte x, const byte y)
{
    this->_V[x] = this->_V[x] | this->_V[y];
}

inline void CPU::bitwiseAnd(const byte x, const byte y)
{
    this->_V[x] = this->_V[x] & this->_V[y];
}

inline void CPU::bitwiseXor(const byte x, const byte y)
{
    this->_V[x] = this->_V[x] ^ this->_V[y];
}

inline void CPU::sumWithVariable(const byte x, const byte vx, const byte vy)
{
    this->_V[0xf] = (vy > (0xff - vx)) ? 1 : 0;
    this->_V[x] += vy;
}

inline void CPU::subtractVyFromVx(const byte x, const byte vx, const byte vy)
{
    this->_V[0xf] = (vy > vx) ? 0 : 1;
    this->_V[x] -= vy;
}

inline void CPU::bitwiseShiftRightByOne(const byte x)
{
    this->_V[0xf] = this->_V[x] & 1;
    this->_V[x] = this->_V[x] >> 1;
}

inline void CPU::subtractWithDifference(const byte x, const byte vx, const byte vy)
{
    this->_V[0xf] = (vx > vy) ? 0 : 1;
    this->_V[x] = vy - vx;
}

inline void CPU::bitwiseShiftLeftByOne(const byte x)
{
    this->_V[0xf] = this->_V[x] & 0b10000000;
    this->_V[x] = this->_V[x] << 1;
}

inline void CPU::skipNextIfVxNotEqualsVy(const byte vx, const byte vy)
{
    if (vx != vy) {
        this->_programCounter += 2;
    }
}

inline void CPU::setIndexRegisterAddress(const uint16_t nnn)
{
    this->_indexRegister = nnn;
}

inline void CPU::jumpToAddressNNNPlusV0(const uint16_t nnn)
{
    if (this->_stackPointer + 1 >= STACK_SIZE) {
        // TODO: raise error
        std::cerr << "Stack overflow\n";
        exit(1);
    }

    this->_stack[this->_stackPointer++] = this->_programCounter;
    this->_programCounter = nnn + this->_V[0];
}

inline void CPU::setVxToBitwiseAndOfRandomNumberAndNN(const Opcode opcode)
{
}

inline void CPU::drawSprite(const Opcode opcode)
{
}

inline void CPU::skipNextIfKeyInVxIsPressed(const Opcode opcode)
{
}

inline void CPU::skipNextIfKeyInVxIsNotPressed(const Opcode opcode)
{
}

inline void CPU::assignDelayTimerToVx(const Opcode opcode)
{
}

inline void CPU::getKey(const Opcode opcode)
{
}

inline void CPU::setVxToDelayTimer(const Opcode opcode)
{
}

inline void CPU::setVxToSoundTimer(const Opcode opcode)
{
}

inline void CPU::addVxToIndexRegister(const Opcode opcode)
{
}

inline void CPU::setIndexRegisterToSpriteLocation(const Opcode opcode)
{
}

inline void CPU::setBinaryCodedDecimalAtVx(const Opcode opcode)
{
}

inline void CPU::dumpRegisters(const Opcode opcode)
{
}

inline void CPU::loadRegisters(const Opcode opcode)
{
}