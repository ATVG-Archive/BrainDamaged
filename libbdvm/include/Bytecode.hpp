//
// Created by atjontv on 5/17/20.
//

#ifndef BRAINDAMAGED_BYTECODE_HPP
#define BRAINDAMAGED_BYTECODE_HPP

#define HLT 0x00
#define NOP 0x01
#define ADDI 0x05
#define SUBI 0x06
#define MULI 0x07
#define DIVI 0x08
#define DUP 0x09
#define CMP 0x0A // Compares SP-1 with SP
#define JE  0x0B // Jumps to SP if SP is 0
#define JNE 0x0C // Jumps to SP if SP is 1
#define JMP 0x0D // Jumps to SP
#define POP 0x0E
#define SWP 0x0F
#define INC 0x10
#define DEC 0x11
#define SPI 0x12
#define SPD 0x13
#define SPC 0x14 // Sets SP to 0
#define LDI 0x15
#define PSI 0x51
#define PSC 0x52
#define RSI 0x53
#define RSC 0x54
#define RSW 0x55
#define PSW 0x56

#endif //BRAINDAMAGED_BYTECODE_HPP
