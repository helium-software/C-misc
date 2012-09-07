#include <stdio.h>

void main (int argc, char * argv[])
{
	int i;
	printf("called as main(%i, {", argc);
	for (i=0; i<argc; i++)
		if (i==0)
			printf("\"%s\"", argv[i]);
		else
			printf(",\"%s\"", argv[i]);
	puts("});\n");

	puts("Where the arguments are stored (probably on the stack):");
	printf("argv = 0x%x\n", argv);
	for (i=0; i<argc; i++)
		printf("argv[%i] = 0x%x\n", i, argv[i]);
	printf("You can now pmap me. My PID is: %i.\n"
	       "  Press Enter to continue: ", getpid());
	getchar();
}
