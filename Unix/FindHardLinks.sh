#!/bin/bash
# @file FindHardLinks.sh
# Remixer:JP FALLON 05/18/18 Original Author: paxdiablo
#script copied from:
# https://superuser.com/questions/12972/how-can-you-see-the-actual-hard-link-by-ls
#given a filename this script will search for it in ~ home dir
#    and all inodes matching it will be printed
if [[ $# -lt 1 ]] ; then
	echo "Usage: findhardlinks <fileOrDirToFindFor> ..."
	exit 1
fi

while [[ $# -ge 1 ]] ; do
	echo "Processing '$1'"
	if [[ ! -r "$1" ]] ; then
		echo "   '$1' is not accessible"
	else
		numlinks=$(ls -ld "$1" | awk '{print $2}')
		inode=$(ls -id "$1" | awk '{print $1}' | head -1l)
		#device=$(df "$1" | tail -1l | awk '{print $6}')
		device="~"
		echo "'$1' has $numlinks  inode(s) ${inode} on mount point '${device}'"

		find ~ -inum ${inode} | sed 's/^/  /'
	fi
	shift
done


