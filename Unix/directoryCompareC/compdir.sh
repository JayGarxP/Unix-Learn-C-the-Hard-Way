#!/bin/bash
# @file compdir
# Joseph Fallon  4/20/18 - 5/5/2018 UNIX 240 Monday
# ASSIGNMENT 2 COMPDIR bash Script

# This script compdir **1** processes the command line (see USAGE)
# then compdir **2** runs 'find' on the directories to compare the files inside
# MODIFIED files are present in the base dir and the modified dir
# DELETED files are present in the base dir but missing from the modified dir
# NEW files are missing from the base dir but are present in the modified dir

# comment out this to disable debug messages
# DEBUG=1

# U S A G E
USAGE="usage: compdir [-R] [-D] <base_dir> <modified_dir> \n\
       -R		compare base and modded directories files recusively\n\
       -D		show differences between modified files\n\
       base 		directory to compare against\n\
       modified	directory that may contain differences\n"

# error codes (use as many as possible so other scripts can use the output)
       E_INVALID_OPTION=-1
       E_NO_ARGUMENTS=-2
       E_GT_2ARGS=-3
       E_INVALID_ARG=-4
       E_MISSING_ARGUMENT=-5

# option flags
       recurse=
       diffa=

# DEBUG COLOR ANSI EsCAPe Codez
       RED='\033[0;31m'
       ERR='\033[1;31m'
       GRN='\033[1;32m'
       CYN='\033[1;36m'
       DB='\033[0;32m'
       NC='\033[0m'
       BOLD=`tput bold`
# end color constants
       if [[ -n "$DEBUG" ]]; then echo -e "${DB}DEBUG: ${GRN}enabled${NC}"; fi

# $1 is string dBug msg
       f_prtDBug () {
	 if [[ -n "$DEBUG" ]]; then echo -e "${DB}DEBUG: ${NC}$1${NC}"; fi
       }

# $1 is string error msg
# $2 is error code
f_prtERR () {
  echo -e "${RED}ERROR: ${ERR}$1${NC}" >> /dev/stderr
    printf "$USAGE" >> /dev/stderr
    exit $2
}

# base and modified directory variables
base_dir=
modified_dir=


# **1**  process command line  **1**
if [[ $# -eq 0 ]]; then
f_prtERR "No Args... Gimme Sumtin!" $E_NO_ARGUMENTS; fi
# For all cmd args, decide if option or dir argument
for x in $*
do	
f_prtDBug "Processing Param:    $x"

if [[ "${x:0:1}" == "-" ]]; then
# option
if [[ "${x^^}" == "-R"  ]]; then
recurse=on
f_prtDBug "${CYN}~Recursive Mode~"
elif [[ "$x" == "-D" || "$x" == "-d" ]]; then
f_prtDBug "${CYN}~Difference Mode~"
diffa=on

elif [[ "$x" == "-?" ]]; then
printf "$USAGE"
exit
else
# invalid option used!
echo "Error: Invalid option $x" >> /dev/stderr
printf "$USAGE" >> /dev/stderr
exit $E_INVALID_OPTION

fi
else # expecting two arguments, base dir then modded dir in order
# if bd unset set it else if modset set it else error
if [[ -z "$base_dir" ]]; then
if [[ -d $x ]]; then
base_dir=$x
else
f_prtERR " $x ??? Dat NOT directory!" $E_INVALID_ARG
fi
elif [[ -z "$modified_dir" ]]; then
if [[ -d $x ]]; then
modified_dir=$x
else
f_prtERR " $x NOT directory!" $E_INVALID_ARG
fi
else
# too many args WYD?!?!
f_prtERR "Too many dir arguments!" $E_GT_2ARGS
fi
fi

done
#if [[ `find -name $x` ]]; then

if [[ -z "$base_dir" ]]; then
f_prtERR "No given base dir: $base_dir!" $E_MISSING_ARGUMENT; fi
if [[ -z "$modified_dir" ]]; then
f_prtERR "No given modified_dir: $modified_dir!" $E_MISSING_ARGUMENT; fi



# **2** COMPARE modified_dir FILES TO base_dir **2**
declare -a base_dir_files
declare -a mod_dir_files

if [[ -n "$recurse" ]]; then
# cmd substitute find command output into base_dir_files
base_dir_files=(`find $base_dir -mindepth 1 -type f -printf "%P\n"`)
mod_dir_files=(`find $modified_dir -mindepth 1 -type f -printf "%P\n"`)
else
# do not recurse
base_dir_files=(`find $base_dir -mindepth 1  -maxdepth 1 -type f -printf "%P\n"`)
mod_dir_files=(`find $modified_dir -mindepth 1  -maxdepth 1 -type f -printf "%P\n"`)
fi

#echo " base dir files...."
#echo "${base_dir_files[*]}"
#echo " mod dir files...."
#echo "${mod_dir_files[*]}"

#flag if file found if not raised then file is deleted
foundfile=
for file in "${base_dir_files[@]}"
do
foundfile=0
f_prtDBug "Checking if $file is in $modified_dir"
for modfile in "${mod_dir_files[@]}"
do
if [[ "$file" == "$modfile" ]]; then
f_prtDBug "$file found"
foundfile=1
basepath="$base_dir/$file"
modpath="$modified_dir/$modfile"
f_prtDBug "$basepath  vs  $modpath"
stamp1=`stat --format %Y $basepath`
stamp2=`stat --format %Y $modpath`
if [[ $stamp1 < $stamp2 ]]; then

echo "$file MODIFIED"
if [[ -n "$diffa" ]]; then
#colordiff approximation
#echo "`diff -u $basepath $modpath | sed 's/^-/\x1b[41m-/;s/^+/\x1b[42m+/;s/^@/\x1b[34m@/;s/$/\x1b[0m/'`"

#normal diff
echo "`diff $basepath $modpath`"


fi
fi

fi
done
if [[ $foundfile == 0 ]]; then
f_prtDBug "$file never found in $modified_dir"
echo "$file DELETED"
fi
done

#Throwing away information gathered in above base vs moddir comparison
# Is a tree structure needed to flag comparisons as 'visited'?
# Would an associative array or more complex data type avoid having to re-traverse?
for modfile in "${mod_dir_files[@]}"
do
foundfile=0
f_prtDBug "Checking if $modfile is in $base_dir"
for file in "${base_dir_files[@]}"
do
if [[ "$file" == "$modfile" ]]; then
f_prtDBug "$modfile found"
foundfile=1
fi
done
if [[ $foundfile == 0 ]]; then
f_prtDBug "$modfile never found in $base_dir"
echo "$modfile NEW"
fi

done

