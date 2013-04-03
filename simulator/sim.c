#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LEN = 4096

//registers and data space

int memory[4096];

int A = 0, B = 0, C = 0, D = 0;

int SW, *SP = (memory+4095), *PC = memory;

//functions

int readChunk(FILE* fin){
    char convert_buffer[10];
    char c;
    int count, i;
    int value;
    i = 0;
    while(c = getc(fin) != ' ' && c != '\0' && c != '\n' && c != EOF){
        convert_buffer[i] = c;
        i++;
    }
    value = atoi(convert_buffer);
    printf("%d ",value);
    return value;
}
void writeChunk(FILE *fout, int chunk){
    char strChunk[10];
    sprintf(strChunk,"%d ", chunk);
    fputs(strChunk, fout);
}

int execute(int *PC){
   return 0; 
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
        //load all the program into the memory space
        
        for(i = 0; i < 4096; i++){
            memory[i] = readChunk(fin);
        }
        close(fin);
        
        //initialize registers
        A = B = C = D = 0;
        SW = 00;
        PC = memory;
        SP = (memory + 4095);
        
        //simulate
        fout = fopen(argv[1],"w");
        fflush(fout);
        if(strcmp(argv[2], "quiet") == 0){
            while(*PC != 0){
                execute(PC);
                PC = PC+1;
            }
            for(i = 0; i < 4096; i++){
                writeChunk(fout, memory[i]);
            }            
        }else if(strcmp(argv[2],"trace") == 0){
            printf("\nTrace Mode\n=============\n");
            while(*PC != 0){
                execute(PC);
                for(i = 0; i < 4096; i++){
                    writeChunk(fout, memory[i]);
                }
                fputs("=================================", fout);
                PC++;
            }
        
        }else if(strcmp(argv[2],"step") == 0){
            printf("\nStep Mode\n===========\n");
            while(*PC != 0){
                execute(PC);
                for(i = 0; i < 4096; i++){
                    writeChunk(fout, memory[i]);
                }
                fputs("=================================", fout);
                printf("Print any key to continue....");
                gets(&c);
                PC++;
            }
        }else{
            printf("\nINVALID OPTION: %s\n",argv[2]);
        }
        close(fout);    
    }
    
    return 0;
}
