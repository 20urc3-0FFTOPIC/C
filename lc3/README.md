#  Simple VM using LC3 architecture

A simple implementation of the LC3 architecture in C 

Want to learn yourself ? Here are some links
- https://en.wikipedia.org/wiki/Little_Computer_3
- https://www.jmeiners.com/lc3-vm/
- https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C

## Instruction set:

```c
Instruction 	OpCode  Hex 	C function 	        Comments
br 	        0x0 	0b0000 	void br(uint16_t i) 	Conditional branch
add 	        0x1 	0b0001 	void and(uint16_t i) 	Used for addition.
ld 	        0x2 	0b0010 	void ld(uint16_t i) 	Load RPC + offset
st 	        0x3 	0b0011 	void st(uint16_t i) 	Store
jsr 	        0x4 	0b0100 	void jsr(uint16_t i) 	Jump to subroutine
and 	        0x5 	0b0101 	void and(uint16_t i) 	Bitwise logical AND
ldr 	        0x6 	0b0110 	void ldr(uint16_t i) 	Load Base+Offset
str 	        0x7 	0b0111 	void str(uint16_t i) 	Store base + offset
rti 	        0x8 	0b1000 	void rti(uint16_t i) 	Return from interrupt (not implemented)
not 	        0x9 	0b1001 	void not(uint16_t i) 	Bitwise complement
ldi 	        0xA 	0b1010 	void ldi(uint16_t i) 	Load indirect
sti 	        0xB 	0b1011 	void sti(uint16_t i) 	Store indirect
jmp 	        0xC 	0b1100 	void jmp(uint16_t i) 	Jump/Return to subroutine
  	        0xD 	0b1101 	  	                Unused OpCode
lea 	        0xE 	0b1110 	void lea(uint16_t i) 	Load effective address
trap 	        0xF 	0b1111 	void trap(uint16_t i)   System trap/call
```

## Register:

```c
enum regist { R0 = 0, R1, R2, R3, R4, R5, R6, R7, RPC, RCND, RCNT };
uint16_t reg[RCNT] = {0};
```

## Usage:

```c
0xF026    //  1111 0000 0010 0110  TRAP tinu16      ;read an uint16_t in R0
0x1220    //  0001 0010 0010 0000  ADD R1,R0,x0     ;add contents of R0 to R1
0xF026    //  1111 0000 0010 0110  TRAP tinu16      ;read an uint16_t in R0
0x1240    //  0001 0010 0010 0000  ADD R1,R1,R0     ;add contents of R0 to R1
0x1060    //  0001 0000 0110 0000  ADD R0,R1,x0     ;add contents of R1 to R0
0xF027    //  1111 0000 0010 0111  TRAP toutu16     ;show the contents of R0 to stdout
0xF025    //  1111 0000 0010 0101  HALT             ;halt
```

## Compiling:

```bash
gcc -Wall LC3_vm.c
```
