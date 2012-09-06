#!/bin/bash

function do_and_echo () {
	echo -e "\\E[1;32m$*\\E[0m"
	eval $*
}
function title () {
	echo -e "\\n\\E[1;31m$*\\E[0m\\n"
}

if [ getopt.c -nt getopt  -o  ! -x getopt ]
then
	do_and_echo gcc getopt.c -o getopt || exit 1
fi


title Normal options

do_and_echo ./getopt
do_and_echo ./getopt nonopt
do_and_echo ./getopt -a -b nonopt
do_and_echo ./getopt -ab nonopt -k

title Option that requires an argument

do_and_echo ./getopt -a -e argument
do_and_echo ./getopt -a -eargument nonopt -k
do_and_echo ./getopt -aeargument
do_and_echo ./getopt -ae
