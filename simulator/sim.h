/*
 *contains prototypes for sim.c functions
 */
 
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
 *MOV   23  1/2
 *MVI   24  2
 *DIV   29  1/2
 *DVI   30  2
 *CMP   31  1/2
 *CPI   32  2
 *LDA   06  2
 *STA   07  2
 *CAL   08  2
 *CZ    09  2
 *CNZ   10  2
 *CP    11  2
 *CNP   12  2
 *JMP   13  2
 *JZ    14  2
 *JNZ   15  2
 *JP    16  2
 *JNP   17  2
 *RET   18  1
 *RZ    19  1
 *RNZ   20  1
 *RP    21  1
 *RNP   22  1
 *INR   25  1
 *DCR   26  1
 *PUSH  27  1
 *POP   28  1
 *
 */
