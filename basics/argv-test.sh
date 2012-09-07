#!/bin/bash

function do_and_echo () {
	echo -e "\\E[1;32m$*\\E[0m"
	eval $*
}
function title () {
	echo -e "\\n\\E[1;31m$*\\E[0m\\n"
}

if [ argv.c -nt argv  -o  ! -x argv ]
then
	do_and_echo gcc argv.c -o argv || exit 1
fi

do_and_echo ./argv
do_and_echo ./argv a b c d e
