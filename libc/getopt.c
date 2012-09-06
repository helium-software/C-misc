#include <unistd.h>
#include <stdio.h>


void printargs (int argc, char **argv)
{
	int i;
	for (i=0; i<argc; i++)
		printf("Argument %2i is '%s'\n", i, argv[i]);
}

void main (int argc, char **argv)
{

	int calls = 0;
	while (1) {
		int oc = getopt(argc, argv, "ace:k");
		printf("#%i getopt call returned ", ++calls);
		if (oc==-1) {
			puts("-1");
			break;
		}
		if (optarg)
			printf("'%c', optarg='%s'\n", oc, optarg);
		else
			printf("'%c', optarg=NULL\n", oc);
	}

	printargs(argc, argv);  /* see how getopt permuted argv */
	printf("optind = %i\n", optind);
	if (optind==argc)
		puts("  Non-option arguments: none.");
	else {
		int i;
		for (i=optind; i<argc; i++)
			printf("  Non-option argument %i: %s\n", i, argv[i]);
	}
}
