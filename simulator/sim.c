#include<stdio.h>
#define LEN = 4096

//registers and data space

int memory[4096];

int A = 0, B = 0, C = 0, D = 0;

int SW, *SP = (memory+4095), *PC = memory;

//functions
int readChunk(FILE* fin){
    char convert_buffer[10];
    int count;
    int value;
    for (i = 0; i < 4; i += 1){
        convert_buffer[i] = getc(fin);
    }
    value = (convert_buffer[2]-'0') + 10*(convert_buffer[1]-'0') + (convert_buffer[0]-'0');
    return value;
}
void writeChunk(FILE *fout){
    char
}

int main (int argc, char *argv[]){
    FILE *fin;
    FILE *fout;
    char buffer[50];
    int i, j;
    char mem_buff[4];
    
    int flag = 1;
    if(argc !=2){
        printf("ERROR:\n======\nCORRECT FORMAT:\nmain.out <filename>\n");
    }else{
        fin = fopen(argv[1],"r");
        fflush(fin);
        //load all the program into the memory space
        
        for(i = 0; i < 4096; i++){
            memory[i] = readChunk(fin);
        }
        //initialize registers
        A = B = C = D = 0;
        SW = 00;
        PC = memory;
        SP = (memory + 4095);
        //simulate
        while(*PC != 0){
            execute(*PC);
            PC++;
        }
        fout = fopen(argv[1],"w");
        fflush(fout);
        for(i = 0 i < 4096; i++){
            printChunk(fout);
        }
    }
    
    return 0;
}
