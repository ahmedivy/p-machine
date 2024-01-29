#include <stdio.h>

#define MAX_PAS_SIZE 500

int PAS[MAX_PAS_SIZE] = {0};

typedef struct
{
    int OP;
    int L;
    int M;
} INS;

int BP, SP, PC;
INS IR;

void loadProgram(const char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    int i = 0;
    while (fscanf(fp, "%d %d %d", &PAS[i], &PAS[i + 1], &PAS[i + 2]) != EOF && i < MAX_PAS_SIZE)
    {
        i += 3;
    }

    fclose(fp);
}

// Appendix A
// Instruction Set Architecture (ISA) – (eventually we will use “stack” to refer to the stack
// segment in PAS)
// In the following tables, italicized names (such as p) are meta-variables that refer to integers. If
// an instruction’s field is notated as “-“, then its value does not matter (we use 0 as a placeholder
// for such values in examples).
// ISA:
// 01 – LIT 0, M Pushes a constant value (literal) M onto the stack
// 02 – OPR 0, M Operation to be performed on the data at the top of the stack.
// (or return from function)
// 03 – LOD L, M Load value to top of stack from the stack location at
// offset M from L lexicographical levels down
// 04 – STO L, M Store value at top of stack in the stack location at offset M
// from L lexicographical levels down
// 05 – CAL L, M Call procedure at code index M (generates new
// Activation Record and PC M)
// 06 – INC 0, M Allocate M memory words (increment SP by M). First four
// are reserved to Static Link (SL), Dynamic Link (DL),
// and Return Address (RA)
// 07 – JMP 0, M Jump to instruction M (PC M)
// 08 – JPC 0, M Jump to instruction M if top stack element is 0
// 09 – SYS 0, 1 Write the top stack element to the screen
//      SYS 0, 2 Read in input from the user and store it on top of the stack
//      SYS 0, 3 End of program (Set “eop” flag to zero)

char *opcodes[10] = {"LIT", "OPR", "LOD", "STO", "CAL",
                     "INC", "JMP", "JPC", "SYS", "ERR"};

void printStack()
{
    // print stack from base to top (stock goes down)
    for (int i = BP; i <= SP; i++)
    {
        printf("%d ", PAS[i]);
    }
}

int main()
{
    loadProgram("input.txt");

    SP = 500;
    BP = SP - 1;
    PC = 0;
    IR.OP = 0;
    IR.L = 0;
    IR.M = 0;

    // printf("                 PC BP SP stack\n");
    // printf("Initial values: %-4d %-4d %-4d\n\n", PC, BP, SP);

    // instead print in nice columns
    printf("%-11s %-4s %-4s %-4s stack\n", "", "PC", "BP", "SP");

    int i = 0;
    // infinite loop
    while (i < 2)
    {

        // fetch
        IR.OP = PAS[PC];
        IR.L = PAS[PC + 1];
        IR.M = PAS[PC + 2];

        // increment PC
        PC += 3;

        // print fetch
        printf("    %3s %2d %2d ", opcodes[IR.OP - 1], IR.L, IR.M);

        // execute
        switch (IR.OP)
        {
        case 7: // JMP
            PC = IR.M;
            printStack();
            break;

        case 6: // INC
            SP -= IR.M;
            printStack();
            break;

            break;
        }

        // print execute
        printf("%2d %3d %3d\n", PC, BP, SP);
        i++;
    }
    return 0;
}
