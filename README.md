simulator for an abstract machine

contains a GUI for assembler, linker loader and executing the program
on the virtual environment

Machine Architecture
====================

+ can address 4096 memory
+ word addressable
+ 4 general purpose registers A, B, C, D
+ 1 memory pointer M
+ Special purpose registers SP, SW, PC

instruction in the form of
Label(opt) opcode operand1, operand2(opt)

3 Addressing Modes
+ Register Addressing (Register number given)
+ Immediate Addressing (Data given in instruction)

Register Addressing and Indirect Addressing format:
+ XXYYZZ (ext ref)
 (XX)->Opcode
 (YY)->Operand1
 (ZZ)->Operand2

Immediate Addressing Format(2 bytes): 
+ XXYY00 data
  (XX)->Opcode
  (YY)->operand1
  (00)->operand2
  data->stored in next byte
  
SW (Status word) format X1X0
shows whether arithmetic operation had the following properties
+ Result is Zero/Non-Zero
+ Result is Negative/Positive
+ Zero is considered as positive
+ X1 = 1 indicates result is zero X1 = 0 indicates result is nonzero
+ X0 = 1 indicates result is negative X0 = 0 indicates result is positive

Instruction codes
 Op    num length(bytes)
 ==    === =============
*ADD   00  1/2 (checked)
*ADI   01  2   (checked)
*SUB   02  1/2 (checked)
*SUI   03  2   (checked)
*MUL   04  1/2 (checked)
*MUI   05  2   (checked)
*MOV   06  1/2 
*MVI   07  2   (checked)
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
*INR   29  1   (checked)
*DCR   30  1   (checked) 
*PUSH  31  1   (checked)
*POP   32  1

