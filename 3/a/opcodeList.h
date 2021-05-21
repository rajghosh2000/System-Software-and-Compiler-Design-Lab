#define OPCODE_STOP 0
#define OPCODE_ADD 1
#define OPCODE_SUB 2
#define OPCODE_MULT 3
#define OPCODE_LOAD 4
#define OPCODE_STORE 5
#define OPCODE_TRANS 6
#define OPCODE_TRIM 7
#define OPCODE_DIV 8
#define OPCODE_READ 9
#define OPCODE_PRINT 10
#define OPCODE_LIR 11
#define OPCODE_IIR 12
#define OPCODE_LOOP 13

struct opcodeKeeper {
	int op;
	int opCodePrint[2];
};

extern const struct opcodeKeeper opCode[];
