#include"sim.h"

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
    while(i<10){
        convert_buffer[i] = '\0';
        i++;
    }
    value = atoi(convert_buffer);
    return value;
}
void writeChunk(FILE *fout, int chunk){
    char strChunk[10] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    sprintf(strChunk,"%d ", chunk);
    fputs(strChunk, fout);
}
void ADD(int op1, int op2){
    printf("\n\t\tIN add: %d, %d, %d", op1, op2, byteflag);
    if(byteflag == 0){
        *registerArray[op1] = *registerArray[op1] + *registerArray[op2];
        PC = PC + 1;
        mem_counter = mem_counter+1;   
    }else{
        *registerArray[op1] = *registerArray[op1] + memory[op2];
        byteflag = 0;
        PC = PC + 2;
        mem_counter = mem_counter+2;
    }
    if(*registerArray[op1] == 0){
        SW = 10;
    }else{
        if(*registerArray[op1] > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
    printf("\n\t\tOut of ADD");
}

void ADI(int op1, int op2){
    *registerArray[op1] = *registerArray[op1] + op2;
    if(*registerArray[op1] == 0){
        SW = 10;
    }else{
        if(*registerArray[op1] > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
    PC = PC + 2;
    mem_counter = mem_counter+2;
}

void SUB(int op1, int op2){
    int result;
    if(byteflag == 0){
        result = *registerArray[op1] - *registerArray[op2];
        *registerArray[op1] = abs(*registerArray[op1] - *registerArray[op2]);
        PC = PC + 1;
        mem_counter = mem_counter+1;
    }else{
        result = *registerArray[op1] - *registerArray[op2];
        *registerArray[op1] = abs(*registerArray[op1] - memory[op2]);
        PC = PC + 2;
        byteflag = 0;
        mem_counter = mem_counter+2;
    }
    
    if(result == 0){
        SW = 10;
    }else{
        if(result > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
    byteflag = 0;
}

void SUI(int op1, int op2){
    int result = *registerArray[op1] - op2;
    *registerArray[op1] = abs(result);
    if(result == 0){
        SW = 10;
    }else{
        if(result > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
    PC = PC + 2;
    mem_counter = mem_counter+2;
}
void MUL(int op1, int op2){
    int result; 
    if(byteflag == 0){
        result = *registerArray[op1] * *registerArray[op2];
        *registerArray[op1] = abs(result);
        PC = PC + 1;
        mem_counter = mem_counter+1;
    }else{
        result = *registerArray[op1] * memory[op2];
        *registerArray[op1] = abs(result);
        PC = PC + 2;
        mem_counter = mem_counter+2;
        byteflag = 0;
    }
    if(result == 0){
        SW = 10;
    }else{
        if(result > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
}
void MUI(int op1, int op2){
*registerArray[op1] = *registerArray[op1] * op2;
    if(*registerArray[op1] == 0){
        SW = 10;
    }else{
        if(*registerArray[op1] > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
    PC = PC + 2;
    mem_counter = mem_counter+2;
}
void MOV(int op1, int op2){
    if(byteflag == 0){
        *registerArray[op1] = *registerArray[op2];
        PC = PC + 1;
        mem_counter = mem_counter + 1;
    }else{
        *registerArray[op1] = memory[op2];
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
    
}
void MVI(int op1, int op2){
    *registerArray[op1] = op2;
    PC = PC + 2;
    mem_counter = mem_counter+2;
}
void DIV(int op1, int op2){
    int result;
    if(byteflag == 1){
        op2 = memory[op2];
        byteflag = 0;
        PC = PC + 2;
        mem_counter = mem_counter + 2;
        byteflag = 0;
    }else{
        PC = PC +1;
        mem_counter = mem_counter + 2;
    }
    if(op2!=0){
        result = *registerArray[op1] / *registerArray[op2];
        *registerArray[op1] = abs(result);
        if(result == 0){
            SW = 10;
        }else{
            if(result > 0){
                SW = 00;
            }else{
                SW = 01;
            }
        }
    }else{
        *registerArray[op1] = 0;
    }
}
void DVI(int op1, int op2){
    if(op2 != 0){
        int result = *registerArray[op1] / op2;
        *registerArray[op1] = abs(result);
        if(result == 0){
            SW = 10;
        }else{
            if(result > 0){
                SW = 00;
            }else{
                SW = 01;
            }
        }

    }else{
        *registerArray[op1] = 0;    
    }
    PC = PC + 2;
    mem_counter = mem_counter + 2;
}
void CMP(int op1, int op2){
    
    int result;
    if(byteflag == 0){
        result = *registerArray[op1] - *registerArray[op2];
        PC = PC + 1;
        mem_counter = mem_counter + 1;
    }else{
        result = *registerArray[op1] - memory[op2];
        PC = PC + 2;
        byteflag = 0;
        mem_counter = mem_counter + 2;
    }
    if(result == 0){
        SW = 10;
    }else{
        if(result > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }

}
void CPI(int op1, int op2){
    int result;
    result = *registerArray[op1] - op2;
    if(result == 0){
        SW = 10;
    }else{
        if(result > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
    PC = PC + 2;
    mem_counter = mem_counter + 2;
}

void LDA(int op1, int op2){
    *registerArray[01] = memory[op2];
    PC = PC + 2;
    mem_counter = mem_counter + 2;
}
void STA(int op1, int op2){
    memory[op2] = *registerArray[1];
    PC = PC + 2;
    mem_counter = mem_counter + 2;
}
void CALL(int addr, int p){
    printf("\n\t\tIN CALL %0x, %d,");
    SP = &memory[mem_counter + 1];
    SP--;
    PC = &memory[addr];
    mem_counter = addr;
}
void CZ(int addr, int p){
    if(SW = 10){
        SP = &memory[mem_counter];
        SP--;
        PC = &memory[addr];
        mem_counter = addr;  
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
    
}
void CNZ(int addr, int p){
    if(SW != 10){
        SP = &memory[mem_counter];
        SP--;
        PC = &memory[addr];
        mem_counter = addr;  
    }else{
        PC = PC + 2;    
        mem_counter = mem_counter + 2;
    }
}
void CP(int addr, int p){
    if(SW%10 == 0){
        SP = &memory[mem_counter];
        SP--;
        PC = &memory[addr];
        mem_counter = addr;  
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void CNP(int addr, int p){
    if(SW%10 != 0){
        SP = &memory[mem_counter];
        SP--;
        PC = &memory[addr];
        mem_counter = addr;  
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void JMP(int addr, int p){
    PC = &memory[addr];
    mem_counter = addr;
}
void JZ(int addr, int p){
    if(SW == 10){
        PC = &memory[addr];
        mem_counter = addr;
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void JNZ(int addr, int p){
    if(SW != 10){
        PC = &memory[addr];
        mem_counter = addr;
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void JP(int addr, int p){
    if(SW%10 == 0){
        PC = &memory[addr];
        mem_counter = addr;
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void JNP(int addr, int p){
    if(SW%10 != 0){
        PC = &memory[addr];
        mem_counter = addr;
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void RET(int q, int p){
    printf("\n\t\tIN RET %d, %d",)
    SP++;
    PC = &(memory[*SP]);
    mem_counter = *SP;
    
}
void RZ(int q, int p){
    if(SW == 10){
        SP++;
        PC = &memory[*SP];
        mem_counter = *SP;
            
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void RNZ(int q, int p){
    if(SW != 10){
        SP++;
        PC = &memory[*SP];
        mem_counter = *SP;
            
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void RP(int q, int p){
    if(SW%10 == 0){
        SP++;
        PC = &memory[*SP];
        mem_counter = *SP;
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void RNP(int q, int p){
    if(SW%10 != 0){
        SP++;
        PC = &memory[*SP];
        mem_counter = *SP;
    }else{
        PC = PC + 2;
        mem_counter = mem_counter + 2;
    }
}
void INR(int op1, int p){
    int result = *registerArray[op1] + 1;
    if(result == 0){
        SW = 10;
    }else{
        if(result > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
    abs(result);
    printf("\n\t\tIN INR %d", *registerArray[op1]);
    PC = PC + 1;
    mem_counter = mem_counter + 1;
    byteflag = 0;
}
void DCR(int op1, int p){
    int result = *registerArray[op1] - 1;
    if(result == 0){
        SW = 10;
    }else{
        if(result > 0){
            SW = 00;
        }else{
            SW = 01;
        }
    }
    abs(result);
    printf("\n\t\tIN DCR %d", *registerArray[op1]);
    PC = PC + 1;
    mem_counter = mem_counter + 1;
    byteflag = 0;
}
void PUSH(int op1, int p){
    *SP = *registerArray[op1];
    SP--;
    PC = PC + 1;
    mem_counter = mem_counter + 1;
    byteflag = 0;
}
void POP(int op1, int p){
    SP++;
    *registerArray[op1] = *SP;
    PC = PC + 1;
    mem_counter = mem_counter + 1;
    byteflag = 0;
}


void (*instructionFunctionArray[33])(int, int) = {
                                                  &ADD, &ADI, &SUB, &SUI, &MUL, 
                                                  &MUI, &MOV, &MVI, &DIV, &DVI, 
                                                  &CMP, &CPI, &LDA, &STA, &CALL, 
                                                  &CZ, &CNZ, &CP, &CNP, &JMP, &JZ, 
                                                  &JNZ, &JP, &JNP, &RET, &RZ, &RNZ, 
                                                  &RP, &RNP, &INR, &DCR, &PUSH, &POP
                                                };


int execute(){
    int return_status = 0;
    int chunk = *PC;
   
    //using hash table for optimized code
   
    int opcode = chunk/10000;
    int oprn1 = (chunk%10000)/100;
    int oprn2 = (chunk%100);
    
    //check if opcode is valid
    if(opcode >= 0 && opcode <= 32){
        //check if instruction is of 2 operands
        if(opcode <= 23){
            if(oprn2 == 0){
                //instruction is 2 bytes for sure
                //take the operand 2 from the next byte
                byteflag = 1;
                //call the instruction function
                printf("\n%d %x %d, %d, %d, %d\n",mem_counter, PC, opcode, oprn1, oprn2, byteflag);
                (*instructionFunctionArray[opcode])(oprn1, *(PC + 1));
                
            }
            else{
                //instruction is of one byte
                //call the instruction function with the operands
                printf("\n%d %x %d, %d, %d, %d\n",mem_counter, PC, opcode, oprn1, oprn2, byteflag);
                (*instructionFunctionArray[opcode])(oprn1, oprn2);
            }
        }
        else{
            //instruction is one byte
            //call the instruction with its operands 
            printf("\n%d %x %d, %d, %d, %d\n",mem_counter, PC, opcode, oprn1, oprn2, byteflag);
            (*instructionFunctionArray[opcode])(oprn1, oprn2);
        }
    }
    else{
        return_status = 1;
    }
    byteflag = 0;
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
/*        for (i = 0; i < LEN; i += 1){*/
/*                printf("%d ", memory[i]);*/
/*        }*/
        close(fin);
        
        //initialize registers
        A = B = C = D = 0;
        SW = 10;
        PC = memory;
        SP = (memory + LEN);
        mem_counter = 0;
        M = memory;
        
        //simulate
        fout = fopen(argv[1],"w");
        fflush(fout);
        if(strcmp(argv[2], "quiet") == 0){
            printf("\nQuiet Mode\n===========\n");
            
            while(*PC != 0){
                execute();
            }
/*            for (i = 0; i < LEN; i += 1){*/
/*                printf("%d ", memory[i]);*/
/*            }*/
            
            for(i = 0; i < LEN; i++){
                writeChunk(fout, memory[i]);
            }            
        }else if(strcmp(argv[2],"trace") == 0){
            printf("\nTrace Mode\n=============\n");
            while(*PC != 0){
                execute();
                for(i = 0; i < LEN; i++){
                    writeChunk(fout, memory[i]);
                }
                fputs("=================================", fout);
            }
        
        }else if(strcmp(argv[2],"step") == 0){
            printf("\nStep Mode\n===========\n");
            while(*PC != 0){
                execute();
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
        printf("\nDONE\n=======");
        close(fout);    
    }
    
    return 0;
}
