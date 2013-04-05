/*
 *contains prototypes for sim.c functions
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LEN 4096

//registers and data space

int memory[LEN];

int A, B, C, D;

int *M;

int SW, *SP, *PC;

int* registerArray[5] = {&SW, &A, &B, &C, &D};

int mem_counter;
 
int byteflag = 0;

int readChunk(FILE*);
/*Reads the characters form the file and returns the int value*/

void writeChunk(FILE*, int);
/*the int value is written on to the file*/

int execute();
/*executes the instruction
 *and increments the PC according to the instruction
 *
 *return_status codes
 * 0 successful
 * 1 opcode invalid
 * 2 invalid argument
 *
 *
 *instruction codes
 *Op    num length(bytes)
 *==    === =============
 *ADD   00  1/2
 *ADI   01  2
 *SUB   02  1/2
 *SUI   03  2
 *MUL   04  1/2
 *MUI   05  2
 *MOV   06  1/2
 *MVI   07  2
 *DIV   08  1/2
 *DVI   09  2
 *CMP   10  1/2
 *CPI   11  2
 *LDA   12  2
 *STA   13  2
 *CALL  14  2
 *CZ    15  2
 *CNZ   16  2
 *CP    17  2
 *CNP   18  2
 *JMP   19  2
 *JZ    20  2
 *JNZ   21  2
 *JP    22  2
 *JNP   23  2
 *RET   24  1
 *RZ    25  1
 *RNZ   26  1
 *RP    27  1
 *RNP   28  1
 *INR   29  1
 *DCR   30  1
 *PUSH  31  1
 *POP   32  1
 *
 */
 
void ADD(int, int);
//add with normal register addressing

void ADI(int, int);
//imidiate addressing, the 3rd argument gives the address
//from where the 3rd argument will be obtained

void SUB(int, int);
void SUI(int, int);
void MUL(int, int);
void MUI(int, int);
void MOV(int, int);
void MVI(int, int);
void DIV(int, int);
void DVI(int, int);
void CMP(int, int);
void CPI(int, int);
void LDA(int, int);
void STA(int, int);
void CALL(int, int);
void CZ(int, int);
void CNZ(int, int);
void CP(int, int);
void CNP(int, int);
void JMP(int, int);
void JP(int, int);
void JNP(int, int);
void JZ(int, int);
void JNZ(int, int);
void RET(int, int);
void RZ(int, int);
void RNZ(int, int);
void RP(int, int);
void RNP(int, int);
void INR(int, int);
void DCR(int, int);
void PUSH(int, int);
void POP(int, int);

