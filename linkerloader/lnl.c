#include "lnl.h"
void flushbuff(char *array){
    int i;
    for (i = 0; i < MAX; i += 1){
        array[i] = '\0';
    }

}
int mkestable(int programCount, char* argv[]){
    char input[10], name[10], symbol[10];
    int paddr = 0, psize = 0, size = 0, addr, i;
    int count = 0;
    FILE* fin;
    
    printf("%10s\t %10s\t %10s\t %10s\n","PNAME","EXTSYM", "ADDR", "LEN" );
    
    for (i = 1; i < programCount; i++){
        fin = fopen(argv[i], "r");
        fflush(fin);
        fscanf(fin,"%s",input);
        while(strcmp(input, "E") != 0){
            if(strcmp(input, "H") == 0){
                printf("H");
                fscanf(fin,"%s",name);
                strcpy(es[count].progname, name);
                
                strcpy(es[count].extsym, "**");
                
                size = paddr;
                fscanf(fin,"%d",&paddr);
                
                paddr += (psize+ size);          
                es[count].address = paddr;
                
                fscanf(fin, "%d", &psize);
                es[count].length = psize;
                
/*                printf("%10s\t %10s\t %10d\t %10d\n", es[count].progname, */
/*                        es[count].extsym, es[count].address, es[count].length);*/
            }else if(strcmp(input,"D")==0){
                while(strcmp(input,"R")!=0){
                    
                    strcpy(es[count].progname,"**");
                    
                    fscanf(fin, "%s", symbol);
                    strcpy(es[count].extsym,symbol);
                    
                    fscanf(fin,"%d",&addr);
                    es[count].address = addr+paddr;
                    
                    es[count].length=1;
                    
/*                    printf("%10s\t %10s\t %10d\t %10d\n", es[count].progname, */
/*                            es[count].extsym, es[count].address, es[count].length);*/
                    count++;
                    fscanf(fin,"%s",input);
                }
            }
            count++;
            fscanf(fin, "%s", input);
            
        }
        close(fin);
    }//end of making estable
    return count;
}

int main (int argc, char *argv[]){
    if(argc <= 1){
        printf("\nERROR:\n=====\nNo Input file given\n");
    }else{
        int i;
        int programCount = argc;
        int extsymCount = 0;
        
/*        printf("\nInput files:");*/
/*        for (i = 1; i < programCount; i += 1){*/
/*            printf("%s\t", argv[i]);*/
/*        }*/
        printf("\n");
        extsymCount = mkestable(programCount, argv);
        
    }
    return 0;
}
