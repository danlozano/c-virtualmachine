#include "vm.h"

#include <stdio.h>
#include <stdbool.h>

#include "instruction_set.h"
#include "registers.h"
#include "program.h"

#define STACK_SIZE 256

static int stack[STACK_SIZE];
static int registers[NUM_OF_REGISTERS];
static bool running = true;

#define IP (registers[IP]) // instruction pointer
#define SP (registers[SP]) // stack pointer

void run() 
{
    IP = 0;
    SP = -1;
    while (running) 
    {
        eval(fetch());
        IP++;
    }
}

int fetch() 
{
    return program[IP];
}

void eval(int instruction) 
{
    switch (instruction)
    {
    case HLT: {
        running = false;
        break;
    }
    case PSH: {
        SP++;
        stack[SP] = program[++IP];
        break;
    }
    case POP: {
        int val_popped = stack[SP--];
        printf("popped %d\n", val_popped);
        break;
    }
    case ADD: {
        int a = stack[SP--];
        int b = stack[SP--];
        int result = b + a;

        SP++;
        stack[SP] = result;

        break;
    }
    }
}
