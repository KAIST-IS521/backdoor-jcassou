//-----------------------------------------------------------------------------
// minivm.c -- The basic definitions for the vm.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include "minivm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Op1 (ctx->r[EXTRACT_B1(instr)].value)
#define Op2 (ctx->r[EXTRACT_B2(instr)].value)
#define Op3 (ctx->r[EXTRACT_B3(instr)].value) 

extern bool is_running;

//---------------------------------------------------------
// FUNCTION IMPLEMENTATIONS:

void halt() {
	is_running = false;
}

void load(struct VMContext* ctx, const uint32_t instr){
	Op1 = ctx->heap[Op2];
}

void store(struct VMContext* ctx, const uint32_t instr){
	ctx->heap[Op1] = Op2;
}


void move(struct VMContext* ctx, const uint32_t instr){
	Op1 = Op2;
}

void puti(struct VMContext* ctx, const uint32_t instr){
	Op1 = EXTRACT_B2(instr);
}

void add(struct VMContext* ctx, const uint32_t instr){
	Op1 = Op2 + Op3;
}

void sub(struct VMContext* ctx, const uint32_t instr){
	Op1 = Op2 - Op3;
}

void gt(struct VMContext* ctx, const uint32_t instr){
	Op1 = Op2 > Op3 ? 1 : 0;
}

void ge(struct VMContext* ctx, const uint32_t instr){
	Op1 = Op2 >= Op3 ? 1 : 0;
}

void eq(struct VMContext* ctx, const uint32_t instr){
	Op1 = Op2 == Op3 ? 1 : 0;
}

// TODO

/*void ite(struct VMContext* ctx, const uint32_t instr){
}

void jump(struct VMContext* ctx, const uint32_t instr){
}*/

//TODO : HOW TO TAKE CARE OF THE PROBLEM

/*void puts(struct VMContext* ctx, const uint32_t instr){
  const uint8_t a = EXTRACT_B1(instr);
}

void gets(struct VMContext* ctx, const uint32_t instr){
  uint32_t str[50];
  printf("Please, type chars : ");
  scanf("%d", str);       
  ctx->r[RepA].value = str;
}*/



// Defers decoding of register args to the called function.
// dispatch :: VMContext -> uint32_t -> Effect()
void dispatch(struct VMContext* ctx, const uint32_t instr) {
	const uint8_t i = EXTRACT_B0(instr);
	(*ctx->funtable[i])(ctx, instr);
}


// Initializes a VMContext in-place.
// initVMContext :: VMContext -> uint32_t -> uint32_t -> [Reg] -> [FunPtr] -> Effect()
void initVMContext(struct VMContext* ctx, const uint32_t numRegs, const uint32_t numFuns, Reg* registers, FunPtr* funtable) {
	ctx->numRegs    = numRegs;
	ctx->numFuns    = numFuns;
	ctx->r          = registers;
	ctx->funtable   = funtable;
	ctx->pc         = 0;
	ctx->opcode     = 0;
        memset(ctx->heap, 0, 8192);	
}


// Reads an instruction, executes it, then steps to the next instruction.
// stepVMContext :: VMContext -> uint32_t** -> Effect()
void stepVMContext(struct VMContext* ctx, uint32_t** pc) {
	// Read a 32-bit bytecode instruction.
	uint32_t instr = **pc;

	// Dispatch to an opcode-handler.
	dispatch(ctx, instr);

	// Increment to next instruction.
	(*pc)++;
}

