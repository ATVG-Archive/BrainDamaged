# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

# BrainDamagedVM

## [Unreleased]

### Added
- Instruction: DDM - Debug Dump Memory displays a hex memory dump when DBG is enabled
- Instruction: RSW - Read Stack Wide reads from stdin until a end of line was given
- Instruction: PSW - Print Stack Wide prints a string if sp is txt_end (0x03) and a txt_begin is found (0x02) (txt_begin and txt_end are from ASCII)
- Instruction: SPI - Stack Pointer Increment, increments the SP by 1
- Instruction: SPD - Stack Pointer Decrement, decrements the SP by 1
- Instruction: SPC - Stack Pointer Clear, Sets SP to the first spot from the back of stack memory (4096) which is not null

### Changed
- Program counter starts at 4096 making space for 4096 stack variables (about 15 kb)

## [0.2.0] - 2020-04-16
### Added
- Instruction: INC - Increments value at stack pointer
- Instruction: DEC - Decrements value at stack pointer
- Instruction: JMP - Adds stack pointer to program counter to skip x instructions (relative jumps)

## [0.1.0] - 2020-04-16
### Added
- First Implementation of BrainDamagedVM

# BrainFuckCompiler

## [Unreleased]
### Added
- Tried to do a first implementation (It is more complicated then though xD)