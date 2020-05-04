# BrainDamaged

BrainDamaged is a project that builds the multiple Projects.

* BrainDamagedVM a 32-bit Bytecode Virtual Machine
* BrainDamagedAssembler compiles Assembly into Bytecode
* ~~BrainFuckCompiler a BrainFuck to BrainDamagedVM Bytecode compiler.~~

# BrainDamaged VM

Location: `bdvm/`  
Version: 0.5.0

## Architecture

* All Instructions are 32-Bit.
* Maximum Stack size is 4096 variables (4096 * 32 bits ~= 16KB)
* Maximum Program size is dynamic with no upper limits, the default allocation is 4096 (4096 * 32 bits ~= 16KB)

+ This VM has a Memory size from at least 32 KB.
  * ~16 KB is addressable Stack memory
  * ~16 KB is at least program code memory

Observing the Memory on Linux, we use about 1721 KB with a 3 instruction program (0x01, RSI, HLT).

## Instruction Set

* pc = Program Counter (Current executing Instruction)
* sp = Stack Pointer (Current top of Stack)
* tos = Top of Stack

| Name | Bytecode | ARGC | Description | Stack Action | Since |
|------|-----------|----------------|-------------|--------------|-------|
| HLT | 0x40000000 | - | Halts the VM | - | 0.1.0 |
| NOP | 0x40000001 | - | Does Nothing | - | 0.1.0 |
|  -  | 0x40000002 | - | RESERVED | - | - |
|  -  | 0x40000003 | - | RESERVED | - | - |
|  -  | 0x40000004 | - | RESERVED | - | - |
| ADD | 0x40000005 | - | Adds two numbers | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| SUB | 0x40000006 | - | Subtracts two numbers | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| MUL | 0x40000007 | - | Multiplies two numbers | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| DIV | 0x40000008 | - | Divides two numbers | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| DUP | 0x40000009 | - | Duplicates top of stack | Copies top of stack into tos (sp++) | 0.1.0 |
| JE  | 0x4000000A | 1 | Skips `x` instructions when tos is 1 | POPs once (sp--) | 0.1.0/0.3.0 |
| JNE | 0x4000000B | 1 | Skips `x` instructions when tos is 0 | POPs once (sp--) | 0.1.0/0.3.0 |
| CMP | 0x4000000C | - | Compares two values and puts 0 or 1 | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| POP | 0x4000000D | - | Removes from tos | POPs once (sp--) | 0.1.0 |
| SWP | 0x4000000E | - | Switches tos | POPs twice (sp-2), puts both switched to stack (sp+2) | 0.1.0 |
| INC | 0x4000000F | - | Increments tos | - | 0.2.0 |
| DEC | 0x40000010 | - | Decrements tos | - | 0.2.0 |
| JMP | 0x40000011 | 1 | Skips `x` instructions | - | 0.2.0/0.3.0 |
| SPI | 0x40000012 | - | Increments sp | (sp++) | 0.3.0 |
| SPD | 0x40000013 | - | Decrements sp | (sp--) | 0.3.0 |
| SPC | 0x40000014 | - | Resets sp | (sp = first non-null location from end of stack) | 0.3.0 |
| LDI | 0x40000015 | - | Adds a value to the stack | Puts value on tos (sp++) | 0.5.0 |
| - | - | - | - | - | - |
| PSI | 0x40000051 | - | Prints tos as Int to stdout | POPs tos (sp--) | 0.1.0 |
| PSC | 0x40000052 | - | Prints tos as ASCII Char to stdout | POPs tos (sp--) | 0.1.0 |
| RSI | 0x40000053 | - | Reads from stdin to tos as Int | Puts to tos (sp++) | 0.1.0 |
| RSC | 0x40000054 | - | Reads from stdin to tos as ASCII Char | Puts to tos (sp++) | 0.1.0 |
| RSW | 0x40000055 | - | Reads from stdin to stack as ASCII until end of line (Max 1024 bytes) | Puts to tos (sp += in bytes / 3) | 0.3.0 |
| PSW | 0x40000056 | - | Prints to stdout from stack in reverse as ASCII | POPs from tos (sp -= (in bytes / 3) + 2) | 0.3.0 |

# BrainDamaged Assembler

Location: `bdasm/`  
Version: 0.3.0

# Disclaimer
**Please don't expect this to work. This is the first Bytecode Compiler and Bytecode VM I wrote in C++.**

# Attributes

BrainDamaged logo made by [Freepik](https://www.flaticon.com/authors/freepik) from [Flaticon](https://www.flaticon.com/)

# License

Just don't bother yet. Do with the code what you want, if you event want to touch it ..