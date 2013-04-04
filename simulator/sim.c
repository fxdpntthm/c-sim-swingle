#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"sim.h"

#define LEN 4096

void *structions[32];

//registers and data space

int memory[LEN];

int A = 0, B = 0, C = 0, D = 0;
int *M = memory;
int SW, *SP = (memory+LEN), *PC = memory;

//functions
int readChunk(FILE* fin){
    char convert_buffer[10];
    char c;
    int count, i;
    int value;
    i = 0;
    c = getc(fin);
    while(c != ' ' && c != '\0' && c != '\n' && c != EOF){
        convert_buffer[i] = c;
        c = getc(fin);
        i++;
    }
    value = atoi(convert_buffer);
    return value;
}
void writeChunk(FILE *fout, int chunk){
    char strChunk[10];
    sprintf(strChunk,"%d ", chunk);
    fputs(strChunk, fout);
}

int execute(){
    int return_status = 0;
    int chunk = *PC;
   
    //use switch case right now
    //convert to hash table later on for optimized code
   
    int opcode = chunk/10000;
    int oprnd1 = (chunk%10000)/100;
    int oprnd2 = (chunk%100);
   
    //check if opcode is valid
    if(opcode >= 0 && opcode <= 32){
        //check if instruction is of 1 or 2 bytes
        if(opcode <= 17){
            if(oprnd2 == 0){
                //instruction is 2 bytes for sure
                //take the operand 2 from the next byte
                oprnd2 = *(PC+1);
                PC = PC + 2;
            }
        }
        else{
            //instruction is one byte
            PC = PC + 1;
        }
    }
    else{
        return_status = 1
    }
    return return_status;
}

int main (int argc, char *argv[]){
    FILE *fin;
    FILE *fout;
    char buffer[50];
    int i, j;
    char mem_buff[4];
    char c;
    int flag = 1;
    
    if(argc !=3){
        printf("ERROR:\n======\nCORRECT FORMAT:\nmain.out <filename> <option>\n");
    }else{
        fin = fopen(argv[1],"r");
        fflush(fin);
        //load memory space
                
        for(i = 0; i < LEN; i++){
            memory[i] = readChunk(fin);
        }
        close(fin);
        
        //initialize registers
        A = B = C = D = 0;
        SW = 0;
        PC = memory;
        SP = (memory + LEN);
        
        //simulate
        fout = fopen(argv[1],"w");
        fflush(fout);
        if(strcmp(argv[2], "quiet") == 0){
            printf("\nQuiet Mode\n===========\n");
            while(*PC != 0){
                execute(PC);
            }
            for(i = 0; i < LEN; i++){
                writeChunk(fout, memory[i]);
            }            
        }else if(strcmp(argv[2],"trace") == 0){
            printf("\nTrace Mode\n=============\n");
            while(*PC != 0){
                execute(PC);
                for(i = 0; i < LEN; i++){
                    writeChunk(fout, memory[i]);
                }
                fputs("=================================", fout);
            }
        
        }else if(strcmp(argv[2],"step") == 0){
            printf("\nStep Mode\n===========\n");
            while(*PC != 0){
                execute(PC);
                for(i = 0; i < LEN; i++){
                    writeChunk(fout, memory[i]);
                }
                fputs("=================================", fout);
                printf("Print any key to continue....");
                gets(&c);
            }
        }else{
            printf("\nINVALID OPTION: %s\n",argv[2]);
        }
        close(fout);    
    }
    
    return 0;
}
