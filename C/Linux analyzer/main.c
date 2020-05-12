#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int ui;
//리눅스의 실행 파일은 ELF 모양으로 저장된다.
int main()
{
	int fp;
	int iRet;
	int size;
	ui uiCnt;
	Elf32_Ehdr *Ehdr;

	size = sizeof(Elf32_Ehdr);

	fp = open("main", O_RDONLY);

	if(fp < 0)
	{
		printf("File read Failed\n");
		return 100;
	}

	Ehdr = malloc(size);
	if(Ehdr == 0)
	{
		printf("Memory Not Enough\n");
		close(fp);
		return 200;
	}

	iRet = read(fp, Ehdr, size);
	if(iRet != size)
	{
		printf("Header read Failed");
		free(Ehdr);
		close(fp);
		return 300;
	}

	for(uiCnt = 0 ; uiCnt <EI_NIDENT; uiCnt++)
	{
		printf("%02X ",Ehdr->e_ident[uiCnt]);
	}
	putchar('\n');

	if(0 != strncmp((char*)Ehdr,ELFMAG,SELFMAG))
	{
		printf("Not ELF file\n");
		free(Ehdr);
		close(fp);
		return 400;
	}

	switch(Ehdr->e_ident[EI_CLASS])
	{
		case ELFCLASSNONE:
			printf("Invalid class\n");
			break;
		case ELFCLASS32:
			printf("32-bit architecture\n");
			break;
		case ELFCLASS64:
			printf("64-bit architecture\n");
			break;
	}

	switch(Ehdr->e_ident[EI_DATA])
	{
		case ELFCLASSNONE:
			printf("Unknown data format.\n");
			break;
		case ELFDATA2LSB:
			printf("Little-endian\n");
			break;
		case ELFDATA2MSB:
			printf("Big-endian\n");
			break;
	}

	switch(Ehdr->e_ident[EI_VERSION])
	{
		case EV_NONE:
			printf("Invalid version.\n");
			break;
		case EV_CURRENT:
			printf("Current version.\n");
			break;
	}

	switch(Ehdr->e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV:
			printf("UNIX System V ABI\n");
			break;  
		case ELFOSABI_HPUX: 
			printf("HP-UX ABI\n");
			break;  
		case ELFOSABI_NETBSD: 
			printf("NetBSD ABI\n");
			break;  
		case ELFOSABI_LINUX: 
			printf("Linux ABI\n");
			break;  
		case ELFOSABI_SOLARIS: 
			printf("Solaris ABI\n");
			break;  
		case ELFOSABI_IRIX: 
			printf("IRIX ABI\n");
			break;  
		case ELFOSABI_FREEBSD: 
			printf("FreeBSD ABI\n");
			break;  
		case ELFOSABI_TRU64: 
			printf("TRU64 UNIX ABI\n");
			break;  
		case ELFOSABI_ARM: 
			printf("ARM architecture ABI\n");
			break;  
		case ELFOSABI_STANDALONE: 
			printf("Stand-alone (embedded) ABI\n");
			break;  
	}

	printf("ABI version : %d\n", Ehdr -> e_ident[EI_ABIVERSION]);

	switch(Ehdr->e_type)
	{
		case ET_NONE:
			printf("An unknown type.\n");
			break;  
		case ET_REL:
			printf("A relocatable file.\n");
			break;  
		case ET_EXEC:
			printf("An executable file.\n");
			break;  
		case ET_DYN:
			printf("A shared object.\n");
			break;  
		case ET_CORE:
			printf("A core file.\n");
			break;
	}

	switch(Ehdr->e_machine)
	{
		case EM_NONE: 
			printf("An unknown machine\n");
			break;  
		case EM_M32: 
			printf("AT&T WE 32100\n");
			break;  
		case EM_SPARC: 
			printf("Sun Microsystems SPARC\n");
			break;  
		case EM_386: 
			printf("Intel 80386\n");
			break;  
		case EM_68K: 
			printf("Motorola 68000\n");
			break;  
		case EM_88K: 
			printf("Motorola 88000\n");
			break;  
		case EM_860: 
			printf("Intel 80860\n");
			break;  
		case EM_MIPS: 
			printf("MIPS RS3000 (big-endian only)\n");
			break;  
		case EM_PARISC: 
			printf("HP/PA\n");
			break;  
		case EM_SPARC32PLUS: 
			printf("SPARC with enhanced instruction set\n");
			break;  
		case EM_PPC: 
			printf("PowerPC\n");
			break;  
		case EM_PPC64: 
			printf("PowerPC 64-bit\n");
			break;  
		case EM_S390: 
			printf("IBM S/390\n");
			break;  
		case EM_ARM: 
			printf("Advanced RISC Machines\n");
			break;  
		case EM_SH: 
			printf("Renesas SuperH\n");
			break;  
		case EM_SPARCV9: 
			printf("SPARC v9 64-bit\n");
			break;  
		case EM_IA_64: 
			printf("Intel Itanium\n");
			break;  
		case EM_X86_64: 
			printf("AMD x86-64\n");
			break;  
		case EM_VAX: 
			printf("DEC Vax\n");
			break;  
	}

	switch(Ehdr->e_version)
	{
		case EV_NONE: 
			printf("Invalid version\n");
			break;
		case EV_CURRENT: 
			printf("Current version\n");
			break;
	}
	printf("Machine(number)                    :  %d\n", Ehdr->e_machine);
	printf("Version                            :  %p\n", Ehdr->e_version);
	printf("Entry point Address                :  %p\n", Ehdr->e_entry);
	printf("Program header table file Offset   :  %d (bytes into file)\n", Ehdr->e_phoff);
	printf("Section header table file Offset   :  %d (bytes into file)\n", Ehdr->e_shoff);
	printf("Flags                              :  %p\n", Ehdr->e_flags);
	printf("ELF header Size                    :  %d (bytes)\n", Ehdr->e_ehsize);
	printf("Program header Size                :  %d (bytes)\n", Ehdr->e_phentsize);
	printf("Program header Number              :  %d\n", Ehdr->e_phnum);
	printf("Section header Size                :  %d (bytes)\n", Ehdr->e_shentsize);
	printf("Section header Number              :  %d\n", Ehdr->e_shnum);
	printf("Section header string table index  :  %d\n", Ehdr->e_shstrndx);
	free(Ehdr);
	close(fp);

	return 0;
}
