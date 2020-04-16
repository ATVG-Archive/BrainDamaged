# BrainDamaged

BrainDamaged is a project that builds the multiple Projects.

* BrainDamagedVM a 32-bit Bytecode Virtual Machine
* ~~BrainFuckCompiler a BrainFuck to BrainDamagedVM Bytecode compiler.~~

# BrainDamaged VM

Location: `bdvm/`  
Version: 0.2.0

## Architecture

* All Instructions are 32-Bit.
* Maximum Stack size is 4096 variables (4096 * 30 bits)
* Maximum Program size is 995_904 instructions

+ This VM has a Memory size from at least 4 MB.
  * ~15.36 KB are addressable Stack memory
  * ~3.983 MB are program code memory

## Instruction Set

* pc = Program Counter (Current executing Instruction)
* sp = Stack Pointer (Current top of Stack)
* tos = Top of Stack

| Name | Bytecode | Description | Stack Action | Since |
|------|----------|-------------|--------------|-------|
| HLT | 0x40000000 | Halts the VM | - | 0.1.0 |
| NOP | 0x40000001 | Does Nothing | - | 0.1.0 |
| DBG | 0x40000002 | Enables Debug loggin of the VM | - | 0.1.0 |
| - | 0x40000003 | RESERVED | - |
| - | 0x40000004 | RESERVED | - |
| ADD | 0x40000005 | Adds two numbers | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| SUB | 0x40000006 | Subtracts two numbers | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| MUL | 0x40000007 | Multiplies two numbers | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| DIV | 0x40000008 | Divides two numbers | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| DUP | 0x40000009 | Duplicates top of stack | Copies top of stack into tos (sp++) | 0.1.0 |
| JE  | 0x4000000A | Skips `x` instructions when tos is 1 | POPs twice (sp-2), adds sp to pc | 0.1.0 |
| JNE | 0x4000000B | Skips `x` instructions when tos is 0 | POPs twice (sp-2), adds sp to pc | 0.1.0 |
| CMP | 0x4000000C | Compares two values and puts 0 or 1 | POPs twice (sp-2), puts result on tos (sp++) | 0.1.0 |
| POP | 0x4000000D | Removes from tos | POPs once (sp--) | 0.1.0 |
| SWP | 0x4000000E | Switches tos | POPs twice (sp-2), puts both switched to stack (sp+2) | 0.1.0 |
| INC | 0x4000000F | Increments tos | - | 0.2.0 |
| DEC | 0x40000010 | Decrements tos | - | 0.2.0 |
| JMP | 0x40000011 | Skips `x` instructions | POPs once (sp--), adds sp to pc | 0.2.0 |
| - | - | - | - |
| PSI | 0x40000051 | Prints tos as Int to stdout | POPs tos (sp--) | 0.1.0 |
| PSC | 0x40000052 | Prints tos as ASCII Char to stdout | POPs tos (sp--) | 0.1.0 |
| RSI | 0x40000053 | Reads from stdout to tos as Int | Puts to tos (sp++) | 0.1.0 |
| RSC | 0x40000054 | Reads from stdout to tos as ASCII Char | Puts to tos (sp++) | 0.1.0 |

### Disclaimer
**Please dont expect this to work. This is the first Bytecode Compiler and Bytecode VM I wrote in C++.**

# Attributes

BrainDamaged logo made by [Freepik](https://www.flaticon.com/authors/freepik) from [Flaticon](https://www.flaticon.com/)

# License

Just dont bother. Do with the code what you want, if you event want to touch it ..