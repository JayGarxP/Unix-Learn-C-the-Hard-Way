#!/bin/bash
#compare
#given two signed integer arguments:
#	<x> is <comparison> <y>
#	x is first number, y is second number
#	comparison is 'equal to' 'greater than' 'less than'
#	exit status is: 
#	  '0 if equal' '1 if less than'  '8 if gt'  '4 if err'

#test exit code with `echo $?`

#exit 4 if too many args, otherwise fill up args for readability
if [ "$#" -ne 2 ]; then
echo "Usage: ./compare int1 int2"
exit 4
fi

fNum=$1
sNum=$2

#Case statement pattern matching w/ wildcard* to exit 4
#		if args can't be treated as integers (numeric compare)
case ${fNum#-} in
''|*[!0-9]*) 
echo "Signed integers only, nono-> '$fNum' "
echo "Usage: ./compare int1 int2"
exit 4
;; #No non numbers chars matched
*) :
;;
esac
#Same case statement, couldn't figure out how to combine them :(
#		to exit 4 if second arg can't atoi
case ${sNum#-} in
''|*[!0-9]*) 
echo "Signed integers only, nono-> '$sNum' "
echo "Usage: ./compare int1 int2"
exit 4
;; #No non numbers chars matched, can finally compare numbers now
*) 
if [[ fNum -lt sNum ]]; then
echo "$fNum is less than $sNum"
exit 1
elif [[ fNum -gt sNum ]]; then
echo "$fNum is greater than $sNum"
exit 8
elif [[ fNum -eq sNum ]]; then
echo "$fNum is equal to $sNum"
exit 0
fi
;;
esac
#see links below for more info 
# On comparisons 
#  string vs num    [[ vs [     (( vs (    == vs -eq
# http://www.tldp.org/LDP/abs/html/comparison-ops.html

#Where did you copy the nasty case statement from?
#  https://stackoverflow.com/questions/806906/how-do-i-test-if-a-variable-is-a-number-in-bash
