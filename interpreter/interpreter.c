// This is where you put your VM code.
// I am trying to follow the coding style of the original.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minivm.h"

#define NUM_REGS   (256)
#define NUM_FUNCS  (256)
#define RepA (ctx->r[EXTRACT_B1(instr)].value)
#define RepB (ctx->r[EXTRACT_B2(instr)].value)
#define RepC (ctx->r[EXTRACT_B3(instr)].value) 

// Global variable that indicates if the process is running.
static bool is_running = true;

void halt() {
	is_running = false;
}

void load(struct VMContext* ctx, const uint32_t instr){
	//ctx->r[a].value = ctx->r[b].value;
}

void store(){
	//ctx->r[a].value = ctx->r[b].value;
}

void move(struct VMContext* ctx, const uint32_t instr){
}

void puti(struct VMContext* ctx, const uint32_t instr){
}

void add(struct VMContext* ctx, const uint32_t instr){
}

void sub(struct VMContext* ctx, const uint32_t instr){

}

void gt(struct VMContext* ctx, const uint32_t instr){

}

void ge(struct VMContext* ctx, const uint32_t instr){
}

void eq(struct VMContext* ctx, const uint32_t instr){

}

void ite(struct VMContext* ctx, const uint32_t instr){

}

void jump(struct VMContext* ctx, const uint32_t instr){
        ctx->pc = Extract_B1(instr);
}

/*void puts(struct VMContext* ctx, const uint32_t instr){
  const uint8_t a = EXTRACT_B1(instr);
  }*/

/*void gets(struct VMContext* ctx, const uint32_t instr){
	uint32_t str[50];
	printf("Please, type chars : ");
	scanf("%d", str);	
        ctx->r[RepA].value = str;
}*/

void usageExit() {
	// Show usage
	printf("USAGE: interpreter [FILE]");
	exit(1);
}

void initFuncs(FunPtr *f, uint32_t cnt) {
	uint32_t i;
	for (i = 0; i < cnt; i++) {
		f[i] = NULL;
	}

	// Initialize function pointers
	f[0x00] = halt;
	f[0x10] = load;
	f[0x20] = store;
	f[0x30] = move;
	f[0x40] = puti;
	f[0x50] = add;
	f[0x60] = sub;
	f[0x70] = gt;
	f[0x80] = ge;
	f[0x90] = eq;
	f[0xa0] = ite;
	f[0xb0] = jump;
	//f[0xc0] = puts; conflicts with puts in <stdio.h>
	//f[0xd0] = gets;

}

void initRegs(Reg *r, uint32_t cnt)
{
	uint32_t i;
	for (i = 0; i < cnt; i++) {
		r[i].type = 0;
		r[i].value = 0;
	}
}

int main(int argc, char** argv) {
	VMContext vm;
	Reg r[NUM_REGS];
	FunPtr f[NUM_FUNCS];
	FILE* bytecode;
	int i = 0;
	uint32_t* pc;

	// There should be at least one argument.
	if (argc < 2) usageExit();

	// Initialize registers.
	initRegs(r, NUM_REGS);
	// Initialize interpretation functions.
	initFuncs(f, NUM_FUNCS);
	// Initialize VM context.
	initVMContext(&vm, NUM_REGS, NUM_FUNCS, r, f);

	// Load bytecode file
	bytecode = fopen(argv[1], "rb");
	if (bytecode == NULL) {
		perror("fopen");
		return 1;
	}


	while (is_running) {
		// Read 4-byte bytecode, and set the pc accordingly
		printf("Running instruction: %d -> [ '%c', '%d', '%d', '%d' ]\n", i, EXTRACT_B0(*pc), EXTRACT_B1(*pc), EXTRACT_B2(*pc), EXTRACT_B3(*pc));
		stepVMContext(&vm, &pc);
		i++;
	}

	fclose(bytecode);

	return 0;
}
