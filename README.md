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
  
SW (Status word) format
shows whether arithmetic operation had the following properties
+ Result is Zero/Non-Zero
+ Result is Negative/Positive

