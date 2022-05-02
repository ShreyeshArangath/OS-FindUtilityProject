#!/bin/bash

make find_utility 
# ./find_utility -w testdir 
#./find_utility -w testdir -n test7 -a
echo "1. find where-to-look"
echo "Test Case: File where to look exists"
echo "./find_utility -w testdir"
 ./find_utility -w testdir

echo -e "\n"
echo "Test Case: File where to look does not exist"
echo "./find_utility -w testdir1"
./find_utility -w testdir1

echo -e "\n"
echo "Test Case: No where to look criterion is specified"
echo "./find_utlity"
./find_utility

echo -e "\n\n"

echo "2.1 find where-to-look -name <specified name>"

echo -e "\n"
echo "Test Case: File with specified name exists: "
echo "./find_utility -w testdir -n test7"
./find_utility -w testdir -n test7

echo -e "\n"
echo "Test Case: File with specified name does not exist: "
echo "./find_utility -w testdir -n test15"
./find_utility -w testdir -n test15

echo -e "\n\n"

echo "2.2 find where-to-look -mmin <specified number of minutes>"

echo -e "\n"
echo "Test Case: +10 mins"
echo "./find_utility -w testdir -m +10"
./find_utility -w testdir -m +10

echo -e "\n"
echo "Test Case: -10 mins"
echo "./find_utility -w testdir -m -10"
./find_utility -w testdir -m -10

echo -e "\n"
echo "Test Case: 10 mins"
echo "./find_utility -w testdir -m 10"
./find_utility -w testdir -m 10


echo -e "\n\n"

echo "2.3 find where-to-look -inum <specified i-node number>"
echo -e "\n"
echo "Test Case: I-Node does not exist"
echo "./find_utility -w testdir -i 10"
./find_utility -w testdir -i 10

echo -e "\n"
echo "Test Case: I-Node exists"
echo "./find_utility -w testdir -i 32797605"
./find_utility -w testdir -i 32797605

echo -e "\n\n"

echo "3. find where-to-look criteria -delete" 
echo -e "\n"
echo "Test Case: Delete file"
echo "./find_utility -w testdir -a delete"
./find_utility -w testdir -n test3 -a delete 

make clean 
