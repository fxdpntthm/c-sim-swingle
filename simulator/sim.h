/*
 *contains prototypes for sim.c functions
 */
 
 int readChunk(FILE*);
 /*Reads the characters form the file and returns the int value*/
 
 int writeChunk(FILE*, int);
 /*the int value is written on to the file*/
 
 int execute(int *);
 /*Executes the instruction checking its opcode*/ 
 
 
