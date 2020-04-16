//
// Created by atjontv on 4/16/20.
//

#ifndef BRAINDAMAGED_BYTECODE_HPP
#define BRAINDAMAGED_BYTECODE_HPP

#define HLT 0x40000000
#define NOP 0x40000001
#define DBG 0x40000002
#define DDM 0x40000003 // Only available with DBG enabled
#define ADD 0x40000005
#define SUB 0x40000006
#define MUL 0x40000007
#define DIV 0x40000008
#define DUP 0x40000009
#define JE  0x4000000A // Jumps to SP if SP is 0
#define JNE 0x4000000B // Jumps to SP if SP is 1
#define CMP 0x4000000C // Compares SP-1 with SP
#define POP 0x4000000D
#define SWP 0x4000000E
#define INC 0x4000000F
#define DEC 0x40000010
#define JMP 0x40000011 // Jumps to SP
#define PSI 0x40000051
#define PSC 0x40000052
#define RSI 0x40000053
#define RSC 0x40000054
#define RSW 0x40000055
#define PSW 0x40000056

#endif //BRAINDAMAGED_BYTECODE_HPP
