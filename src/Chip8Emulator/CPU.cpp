#include "CPU.h"

#include <iostream>

CPU::CPU(Memory* memory)
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

    // this->clearStack();
    // this->clearRegisters();
    // this->resetTimers();
}

void CPU::run()
{
    for (;;) {
        this->cycle();
    }
}

void CPU::cycle()
{
    this->decodeOpcode(this->fetchOpcode());
    this->_programCounter += 2;
}

Opcode CPU::fetchOpcode()
{
    return this->_memory[this->_programCounter] << 8 | this->_memory[this->_programCounter + 1];
}

void CPU::decodeOpcode(const Opcode opcode)
{
    if (opcode == 0x00E0) {
        this->clearScreen();
    } else if (opcode == 0x00EE) {
        this->returnFromSubroutine();
    } else if ((opcode & 0xF000) == 0x0000) {
        this->callProgramAtAddressNNN(opcode);
    } else if ((opcode & 0xF000) == 0x1000) {
        this->jumpToAddressNNN(opcode);
    } else if ((opcode & 0xF000) == 0x2000) {
        this->invokeSubroutine(opcode);
    } else if ((opcode & 0xF000) == 0x3000) {
        this->skipNextIfEqualsConstant(opcode);
    } else if ((opcode & 0xF000) == 0x4000) {
        this->skipNextIfNotEqualsConstant(opcode);
    } else if ((opcode & 0xF00F) == 0x5000) {
        this->skipNextIfEqualsVariable(opcode);
    } else if ((opcode & 0xF000) == 0x6000) {
        this->set(opcode);
    } else if ((opcode & 0xF000) == 0x7000) {
        this->sumWithConstant(opcode);
    } else if ((opcode & 0xF00F) == 0x8000) {
        this->assign(opcode);
    } else if ((opcode & 0xF00F) == 0x8001) {
        this->bitwiseOr(opcode);
    } else if ((opcode & 0xF00F) == 0x8002) {
        this->bitwiseAnd(opcode);
    } else if ((opcode & 0xF00F) == 0x8003) {
        this->bitwiseXor(opcode);
    } else if ((opcode & 0xF00F) == 0x8004) {
        this->sumWithVariable(opcode);
    } else if ((opcode & 0xF00F) == 0x8005) {
        this->subtractWithVariable(opcode);
    } else if ((opcode & 0xF00F) == 0x8006) {
        this->bitwiseShiftRightByOne(opcode);
    } else if ((opcode & 0xF00F) == 0x8007) {
        this->subtractWithDifference(opcode);
    } else if ((opcode & 0xF00F) == 0x800E) {
        this->bitwiseShiftLeftByOne(opcode);
    } else if ((opcode & 0xF00F) == 0x9000) {
        this->skipNextIfNotEqualsVariable(opcode);
    } else if ((opcode & 0xF000) == 0xA000) {
        this->setIndexRegisterAddress(opcode);
    } else if ((opcode & 0xF000) == 0xB000) {
        this->jumpToAddressNNNPlusV0(opcode);
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
        //TODO return error
        std::cerr << "Unknwown opcode: '" << opcode << "'\n";
    }
}

inline void CPU::callProgramAtAddressNNN(const Opcode Opcode)
{
}

inline void CPU::clearScreen()
{
}

inline void CPU::returnFromSubroutine()
{
}

inline void CPU::jumpToAddressNNN(const Opcode opcode)
{
}

inline void CPU::invokeSubroutine(const Opcode opcode)
{
}

inline void CPU::skipNextIfEqualsConstant(const Opcode opcode)
{
}

inline void CPU::skipNextIfNotEqualsConstant(const Opcode opcode)
{
}

inline void CPU::skipNextIfEqualsVariable(const Opcode opcode)
{
}

inline void CPU::set(const Opcode opcode)
{
}

inline void CPU::sumWithConstant(const Opcode opcode)
{
}

inline void CPU::assign(const Opcode opcode)
{
}

inline void CPU::bitwiseOr(const Opcode opcode)
{
}

inline void CPU::bitwiseAnd(const Opcode opcode)
{
}

inline void CPU::bitwiseXor(const Opcode opcode)
{
}

inline void CPU::sumWithVariable(const Opcode opcode)
{
}

inline void CPU::subtractWithVariable(const Opcode opcode)
{
}

inline void CPU::bitwiseShiftRightByOne(const Opcode opcode)
{
}

inline void CPU::subtractWithDifference(const Opcode opcode)
{
}

inline void CPU::bitwiseShiftLeftByOne(const Opcode opcode)
{
}

inline void CPU::skipNextIfNotEqualsVariable(const Opcode opcode)
{
}

inline void CPU::setIndexRegisterAddress(const Opcode opcode)
{
}

inline void CPU::jumpToAddressNNNPlusV0(const Opcode opcode)
{
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