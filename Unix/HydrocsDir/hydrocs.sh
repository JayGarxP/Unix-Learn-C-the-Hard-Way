#!/bin/bash
# @file hydrocs.sh
# Joseph Fallon  06/13/18
echo "Running Hydrocs.exe"
make
./hydrocs srccode.txt UNIX_A4/out.html
echo "out.html generated in UNIX_A4"
cd UNIX_A4

