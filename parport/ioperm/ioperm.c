#include <stdio.h> 
#include <sys/io.h> 
#define BASEADDR 0x378 
int main(int argc, char **argv) 
{ 
	char val;
	if(ioperm(BASEADDR, 4, 1) < 0) {
		fprintf(stderr, "could not get i/o permission. are you root ?\n"); 
		return 5; 
	} 
	outb(0x1f, BASEADDR);
	val = inb(BASEADDR);
	printf("VAL is %x\n", val);
	outb(0xff, BASEADDR);
	val = inb(BASEADDR);
	printf("VAL is %x\n", val);
 
	ioperm(BASEADDR, 4, 0); 
	return 0; 
}
