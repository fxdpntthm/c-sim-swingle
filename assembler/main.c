#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int memoryMap[4096],lineCtr=1,locCtr=0,symCtr=0,litCtr=0,tabCtr=0,address;
char c='\0', name[6]="Sample";

struct reg
{
    char name[2];
    int code;
} GPR[5]={"A",0,"B",1,"C",2,"D",3,"M",4},SPR[3]={"SP",5,"PC",6,"SW",7};

struct instructionSet
{
    char name[5];
    int code;
    int length;
}OPTAB[33]={ "ADD",0,1,
            "ADI",1,2,
            "SUB",2,1,
            "SUI",3,2,
            "MUL",4,1,
            "MUI",5,2,
            "LDA",6,1,
            "STA",7,1,
            "CALL",8,2,
            "CZ",9,2,
            "CNZ",10,2,
            "CP",11,2,
            "CNP",12,2,
            "JMP",13,2,
            "JZ",14,2,
            "JNZ",15,2,
            "JP",16,2,
            "JNP",17,2,
            "RET",18,1,
            "RZ",19,1,
            "RNZ",20,1,
            "RP",21,1,
            "RNP",22,1,
            "MOV",23,1,
            "MVI",24,2,
            "INR",25,1,
            "DCR",26,1,
            "PUSH",27,1,
            "POP",28,1,
            "DIV",29,1,
            "DVI",30,2,
            "CMP",31,1,
            "CPI",32,2};
struct directive
{
    char name[10];
    int code;
}PSEUDOOPTAB[5]={"START",0,
                 "STOP",1,
                 "LTORG",2,
                 "EXTDEF",3,
                 "EXTREF",4};


struct dclcode
{
     char mne[5];
     int address;
}DCL[2]={"DS",1,"DC",2};



struct buffer
{
     char lbl[10];
     char m[10];
     char op1[10];
     char op2[10];
}buf;

struct symbol
{
     char symbol[10];
     int add;
}SYMTAB[100];

struct literal
{
     char lit[10];
     int add;
}LITTAB[50];

struct tab_inc
{
     int index;
     long fpos;
     int type;
}t_inc[10];

int GetDirective(char a[10])
{
    int i=0;
    while(i<5)
    {
        if(strcmp(PSEUDOOPTAB[i].name,a)==0)
        {
            return PSEUDOOPTAB[i].code ;
        }
        i++;
    }
    return -1;
}
void UpdateSYMTAB(FILE *fe)
{
    int i,j;
    for(i=0;i<symCtr;i++)
    {
        if(strcmp(SYMTAB[i].symbol,buf.m)==0)
        {
            if(SYMTAB[i].add==0)
            {
                SYMTAB[i].add=locCtr;
            }
            else
            {
                printf("\nMultiple declaration of %s",buf.m);
                fprintf(fe,"\nMultiple declaration of %s",buf.m);
                exit(1);
            }
            return;
         }
     }
}


int GetSymbol(char s[10])
{
      int i,len=strlen(s);
      if(s[0]=='=')
      {
            for(i=0;i<litCtr;i++)
            {
                if(strcmp(LITTAB[i].lit,s)==0)
                {
                    t_inc[tabCtr].type=0;
                    return i;
                }
            }
            strcpy(LITTAB[tabCtr].lit,s);
            litCtr++;
            t_inc[tabCtr].type=0;
            return (litCtr-1);
      }
      else if(s[len-1]==':')
      {
            s[len-1]='\0';
            strcpy(SYMTAB[symCtr].symbol,s);
            SYMTAB[symCtr].add=locCtr;
            symCtr++;
            return (symCtr-1);
      }
      else
      {
           for(i=0;i<symCtr;i++)
           {
                if(!strcmp(s,SYMTAB[i].symbol))
                {
                    t_inc[tabCtr].type=1;
                    return i;
                }
           }
           strcpy(SYMTAB[symCtr].symbol,s);
           t_inc[tabCtr].type=1;
           SYMTAB[symCtr].add=0;
           symCtr++;
           return (symCtr-1);
      }
}

int GetRegister(char a[2])
{
    int i;
    for(i=0;i<5;i++)
    {
        if(!strcmp(a,GPR[i].name))
        {
            return GPR[i].code;
        }
    }
    return 0;
}

int GetOpcode(char a[20])
{
      int i;
      for(i=0;i<33;i++)
      {
            if(strcmp(OPTAB[i].name,a)==0)
            {
                 return OPTAB[i].code;
            }
      }
      return -1;
}

int GetDcl(char a[10])
{
    int i;
    for(i=0;i<2;i++)
    {
        if(!strcmp(DCL[i].mne,a))
        {
            return DCL[i].address;
        }
    }
    return -1;
}

void CleanBuffer()
{
    strcpy(buf.lbl,"");
    strcpy(buf.m,"");
    strcpy(buf.op1,"");
    strcpy(buf.op2,"");
}



void Parser(FILE *fi)
{
    char a[20];
    int i;
    int ctr=0;
    while((c=getc(fi))!=EOF && (c!='\n'))
    {
        if((c!=' ') && (c!='\t') && (c!='\n'))
        {
            i=0;
            a[i++]=c;
            while(((c=getc(fi))!=' ') && (c!=' ') && (c!='\n') && (c!=EOF) && (c!=','))
            {
                 a[i++]=c;
                 //printf("\nhere:%c",c);
            }
            a[i]='\0';
            if(a[0]!='\0')
            {
                if(ctr==0)
                {
                     if(a[i-1]==':')
                     {
                            strcpy(buf.lbl,a);
                            printf("\nlbl:%s",buf.lbl);
                            continue;
                     }
                     else
                     {
                            strcpy(buf.m,a);
                            printf("\nm:%s",buf.m);
                            ctr++;
                     }
                }
                else if(ctr==1)
                {
                      strcpy(buf.op1,a);
                      printf("\nop1:%s",buf.op1);
                      ctr++;
                }
                else if(ctr==2)
                {
                      strcpy(buf.op2,a);
                      printf("\nop2:%s",buf.op2);
                      ctr=0;
                }
            }
            if(c=='\n')
            {
                ctr=0;
                lineCtr++;
                return;
            }
        }
    }
}


int DecodeLiteral(char a[10],FILE *fe)
{
    int i,length,j=0;
    char val[5];
    length=strlen(a);
    for(i=0;i<litCtr;i++)
    {
        if(!strcmp(LITTAB[i].lit,buf.m))
        {
            if(LITTAB[i].add==0)
            {
                LITTAB[i].add=locCtr;
            }
            else
            {
                printf("\n Multiple declaration of %s",buf.m);
                fprintf(fe,"\n Multiple declaration of %s",buf.m);
                exit(1);
            }
        }
    }
    for(i=2;i<length;i++,j++)
    {
        val[j]=a[i];
    }
    return atoi(val);
}

void pass1(FILE *fe,FILE *fo)
{
    int code,opcode,dcode;
    static int fstop=1,fend=1;
    long fpos;
    if(fstop)
    {
        if(strcmp(buf.lbl,""))
        {
            GetSymbol(buf.lbl);
        }
        opcode=GetOpcode(buf.m);
        if(opcode==0)
        {
            fstop=0;
            fprintf(fo,"0 000 \n",locCtr);
            locCtr++;
            return;
        }
        if(opcode!=-1)
        {
            fprintf(fo,"%d",opcode);
            code=GetRegister(buf.op1);
            if(code==0)
            {
                strcpy(buf.op2,buf.op1);
            }
            fprintf(fo,"%d",code);
            code=GetSymbol(buf.op2);
            fpos=ftell(fo);
            t_inc[tabCtr].index=code;
            t_inc[tabCtr].fpos=fpos;
            tabCtr++;
            locCtr++;
            fprintf(fo,"   \n");
        }
        else
        {
            dcode=GetDirective(buf.m);
            printf("%s",buf.m);
            if(dcode!=-1)
            {
                switch(dcode)
                {
                      case 1:
                                locCtr=atoi(buf.op1);
                                address=locCtr;
                                break;
                }
            }
            else
            {
                fprintf(fo,"***");
                code=GetRegister(buf.op1);
                if(code==0)
                {
                    if(!strcmp(buf.op2,""))
                    {
                        strcpy(buf.op2,buf.op1);
                    }
                    else
                    {
                        fprintf(fo," *** ");
                        fprintf(fe," Error at line %d :: Illegal register %s",lineCtr-1,buf.op1);
                        code=GetSymbol(buf.op2);
                        fpos=ftell(fo);
                        t_inc[tabCtr].index=code;
                        t_inc[tabCtr].fpos=fpos;
                        tabCtr++;
                        locCtr++;
                    }
                }
                fprintf(fo," %d",code);
                code=GetSymbol(buf.op2);
                fpos=ftell(fo);
                t_inc[tabCtr].index=code;
                t_inc[tabCtr].fpos=fpos;
                tabCtr++;
                locCtr++;
                fprintf(fo," \n");
                printf("\n Error at line %d :: Unknown mnemonics: %s",lineCtr-1,buf.m);
                fprintf(fe,"\n Error at line %d :: Unknown mnemonics: %s",lineCtr-1,buf.m);
                exit(1);
              }
        }
    }
    else
    {
        if(fend)
        {
            if(!strcmp(buf.m,"end"))
            {
                fprintf(fo,"\n");
                locCtr++;
                fend=0;
            }
            else
            {
                code=GetDcl(buf.op1);
                switch(code)
                {
                    case 1:
                            fprintf(fo,"\n");
                            UpdateSYMTAB(fe);
                            locCtr+=atoi(buf.op2);
                            break;
                    case 2:
                            fprintf(fo,"00 0 00%d\n",*buf.op2);
                            UpdateSYMTAB(fe);
                            locCtr++;
                            break;
                }
            }
        }
        else if(strcmp(buf.m,""))
        {
            code=DecodeLiteral(buf.m,fe);
            fprintf(fo,"00 0 %d  \n",code);
            locCtr++;
        }
    }
    CleanBuffer();
    return;
}

void pass2(FILE *fop)
{
      int i,adr,x;
      long pos;
      for(i=0;i<tabCtr;i++)
      {
            pos=t_inc[i].fpos;
            adr=t_inc[i].index;
            fseek(fop,pos,0);
            if(t_inc[i].type==0)
            {
                if(LITTAB[adr].add!=0)
                {
                    fprintf(fop,"%d \t",LITTAB[adr].add);
                }
                else
                {
                    fprintf(fop,"***");
                    printf("\n Undelared literal: %s",LITTAB[adr].lit);
                    fprintf(fop,"\n Undelared literal: %s",LITTAB[adr].lit);
                    exit(1);
                }
            }
            else
            {
                if(SYMTAB[adr].add!=0)
                {
                    fprintf(fop,"%d\t",SYMTAB[adr].add);
                }
                else
                {
                    fprintf(fop,"***");
                    printf("\n Undeclared symbol: %s",SYMTAB[adr].symbol);
                    fprintf(fop,"\n Undeclared symbol: %s",SYMTAB[adr].symbol);
                    exit(1);
                }
            }
      }
}
void objectFile(FILE *fop, FILE *fob)
{
    int length = locCtr-101,text[10],i,j;
    fprintf(fob,"H%s%d%d\n",name,address,length);
    char line[50];
    while(fgets(line,50,fop)!=NULL)
    {
        i=0;
        if(line[0] != '\n'){
            fprintf(fob,"T");
            while(line[i]!='\n'){
                fprintf(fob,"%c",line[i]);
                i++;
            }
        fprintf(fob,"\n");
        }

    }
    fprintf(fob,"E%d",address);

}







int main(int argc, char *argv[])
{
FILE *fi,*fe,*fo,*fob;
    fi=fopen("input","r");
    fe=fopen("input","a+");
    fo=fopen("intermediate","w");
    fob=fopen("object","w");
    fprintf(fe,"\n\n");
    fflush(fi);
    while(c!=EOF)
    {
        Parser(fi);
        printf("\n");
        pass1(fe,fo);
    }
    pass2(fo);
    fclose(fo);
    fo=fopen("intermediate","r");
    fflush(fo);
    objectFile(fo,fob);
    fclose(fi);
    fclose(fe);
    fclose(fo);
    fclose(fob);
    
  return 0;
}
