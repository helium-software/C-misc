#!/bin/bash

exec 2>&1  # prepare for use with |less -r

function do_and_echo () {
	echo -e "\\E[1;32m$*\\E[0m"
	eval $*
}
function title () {
	echo -e "\\n\\E[1;31m$*\\E[0m\\n"
}

if [ getopt_long.c -nt getopt_long  -o  ! -x getopt_long ]
then
	do_and_echo gcc getopt_long.c -o getopt_long || exit 1
fi


title Correct usage '(--switch takes an optional argument)'

do_and_echo ./getopt_long --verbose --switch
do_and_echo ./getopt_long --verbose -a nonopt --switch -c
do_and_echo ./getopt_long nonopt --switch
do_and_echo ./getopt_long --switch switch1
do_and_echo ./getopt_long --switch=switch1

title --color takes a mandatory argument

do_and_echo ./getopt_long --color bittersweet haha
do_and_echo ./getopt_long --color bittersweet
do_and_echo ./getopt_long --color=orange -egreen -e violet --color blue

title Cases that should fail

do_and_echo ./getopt_long --blubb
do_and_echo ./getopt_long --verbose=no nonopt
do_and_echo ./getopt_long --color
do_and_echo ./getopt_long blue --color