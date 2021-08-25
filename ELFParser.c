#include "ELFParser.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define MAX_BUF_SIZE 4*1024*1024

/* for getopt_long() */
const char* shortopts = "h";
struct option longopts[] = {
	{"header",no_argument,NULL,'h'}
};

void get_header(const char* buf)
{
	Elf32_Ehdr *elf_file_header;
	elf_file_header = (Elf32_Ehdr *)buf;	
	printf("Entry Address:\t\t%x\n",elf_file_header->e_entry);
	printf("Program Address:\t%x\n",elf_file_header->e_phoff);
	printf("Section Address:\t%x\n",elf_file_header->e_shoff);
}



int main(int argc,char* argv[])
{
	
	FILE* fp;
	unsigned char buf[MAX_BUF_SIZE];
	int c;
	
	//can only read , need to chmod 755
	fp = fopen(argv[1],"rb");
	if(!fp)
	{
		printf("File can not be opened.\n");
		exit(-1);
	}
	int flen = fread(buf,1,MAX_BUF_SIZE,fp);
	buf[flen]='\0';
	
	
	while((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1)
	{
		switch(c)
		{
			case 'h':
				get_header(buf);
				break;
		}
		
		
		
	}
	
	return 0;
}

