#!/bin/bash
# @file a2testCase.sh
# Joseph Fallon  05/20/18
#CST 240 - Assignment 2 and 3 Test Cases


#Command lines that should work correctly:
#Can't run withot ./ infront going to try a symlink inside a 'bin' dir
#ln -s /path_to_script/myscript /bin/myscriptLink 
#Didn't work. :( has to be THE BIN dir, I don't have access sadly.
#./compdir dir1 dir2
#./compdir dir1 dir2 -R
#./compdir dir1 dir2 -R -D
#./compdir dir1 dir2 -D
#./compdir -?			#usage statement
#NO ERRORS IN SHELL SCRIPT

#Command lines that should give errors:
./compdir –x			# invalid option
./compdir dir1 dir2 dir3		# too many arguments
./compdir				# not enough arguments
./compdir dir1			# not enough arguments
./compdir -R			# not enough arguments
./compdir -R -D			# not enough arguments
./compdir dir1 -R -D		# not enough arguments
./compdir dir1 dir3 		# invalid argument, dir3 does not exist
./compdir dir3 dir2 		# invalid argument, dir3 does not exist
./compdir compdir.c dir2		# invalid argument, compdir.c is not a directory

./compdir dir1 compdir.c		
#// invalid argument, compdir.c is not a directory

