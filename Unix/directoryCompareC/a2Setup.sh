#!/bin/bash

#
# This script creates the example directories used in CST240 Assign2
#


rm -rf dir1
rm -rf dir2

mkdir dir1
cd dir1
touch -t 200806200000 foo
touch -t 200806200000 bar
echo "hello" > haha
touch -t 200806200000 haha
touch -t 200806200000 bob
mkdir sub-dir
cd sub-dir
echo "joe" > joe
touch -t 200806200000 joe
cd ..
touch -t 200806200000 sub-dir
cd ..

mkdir dir2
cd dir2
touch -t 200806250000 foo
echo "there" > haha
touch -t 200806260000 haha
touch -t 200806210000 blah
touch -t 200806200000 bob
mkdir sub-dir
cd sub-dir
echo "was here" > joe
touch -t 200806250000 joe
cd ..
touch -t 200806250000 sub-dir
cd ..


