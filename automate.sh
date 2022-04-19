#!/bin/bash

echo "find"
make find_utility 
./find_utility -w testdir 
make clean 
