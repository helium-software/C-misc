#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

#include <stdlib.h>
#include <errno.h>
#define die() exit(EXIT_FAILURE)

static void printargs (int argc, char **argv)
{
	int i;
	for (i=0; i < argc; i++)
		printf("Argument %2i is '%s'\n", i, argv[i]);
}
/* compact version of printargs */
static void printcmdline (int argc, char **argv)
{
	printf("%s", "Permuted command line:\n ");
	int i; for (i=0; i < argc; i++)
		printf(" %s", argv[i]);
	puts("");
}

/* ============================================================================ */

/* definition of short options (same as in getopt.c) */
char * shortopts = "ace:k";

/* definition of long options */
/* explanation of fields:
     # char *  optname    : Name of the option = how it should be entered on the console
     # int     takes arg? : Specifies whether the option takes an argument, like --color=green
                            Consists of constants included from <getopt.h>
     # int *   flag       : if != NULL, instructs getopt_long() to store VALUE at the address contained
     # int     value      : integer that identifies that option; either returned by getopt_long() or stored at *flag */

/* meaning of VALUE contents */
#define OPT_VERBOSE 1
#define OPT_COLOR   2
#define OPT_SWITCH  4

static struct option longopts[] = {
/*	 optname    takes arg?         flag  value */
	{"verbose", no_argument,       NULL, OPT_VERBOSE},
	{"color",   required_argument, NULL, OPT_COLOR  },
	{"switch",  optional_argument, NULL, OPT_SWITCH },
	{0,         0,                 NULL, 0          }
};

/* ============================================================================ */

static void printgetopt (int call, int opt)
{
	/* output opt as a number */
	printf("#%i getopt call returned %i", call, opt);
	/* output opt as a character */
	if (opt >= ' ' && opt <= '~')
		printf(" = '%c'", opt);
	/* output opt in terms of our constants */
	switch (opt) {
	case OPT_VERBOSE:
		printf("%s", " = OPT_VERBOSE");
		break;
	case OPT_COLOR:
		printf("%s", " = OPT_COLOR");
		break;
	case OPT_SWITCH:
		printf("%s", " = OPT_SWITCH");
		break;
	}
	/* output optarg */
	if (opt == -1)
		puts("");
	else if (optarg)
		printf(", optarg='%s'\n", optarg);
	else
		puts(", optarg=NULL");
}

/* ============================================================================ */

/* global variables for custom high-level representation of options */
int	optionflags = 0;
char *  opt_color = NULL;  /* Note that these variables can only store _one_ option argument. */
char *  opt_switch = NULL; /* At the end of the getopt_long loop, they will contain the last argument specified. */
                           /* This is consistent with e.g. "ls --color=always --color=never" doing uncolored output. */

void main (int argc, char **argv)
{
	/* loop through the command line with getopt_long() */
	int calls = 0;
	while (1) {
		int opt = getopt_long(argc, argv, shortopts, longopts, NULL);
		printgetopt(++calls, opt);
		if (opt == -1)
			break;
		if (opt == '?')
			die(); /* error messages have already been issued by getopt_long() */

		switch (opt) {
		case OPT_VERBOSE:
			optionflags |= OPT_VERBOSE;
			break;
		case OPT_COLOR:
			optionflags |= OPT_COLOR;
			opt_color = optarg;
			break;
		case OPT_SWITCH:
			optionflags |= OPT_SWITCH;
			opt_switch = optarg;
			break;
		}
	}

	/* see how getopt permuted argv */
	printcmdline(argc, argv);
	// printargs(argc, argv);

	/* print non-option arguments */
	printf("optind = %i\n", optind);
	if (optind==argc)
		puts("  Non-option arguments: none.");
	else {
		int i;
		for (i=optind; i<argc; i++)
			printf("  Non-option argument %i: %s\n", i, argv[i]);
	}

	/* print the high-level option data */
	puts("Result:");
	if (optionflags & OPT_VERBOSE)
		puts("  Verbose:  yes");  else  puts("  Verbose:  no");
	if (optionflags & OPT_COLOR)
		printf("  Color:    \"%s\"\n", opt_color);  else  puts("  Color:    none");
	if (optionflags & OPT_SWITCH)
		if (opt_switch)   printf("  Switch:   \"%s\"\n", opt_switch);
		else              puts("  Switch:   on");
	else                      puts("  Switch:   off");
}