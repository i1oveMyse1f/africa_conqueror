#!/bin/bash

dist_matrix="dist_matrix.txt"

echo "Generate dist_matrix..."
python "./gen_dist_matrix.py" > $dist_matrix

g++ -std=c++17 -o validator -Wall validator.cpp 
./validator < $dist_matrix
if [ $? -eq 0 ]; then
	echo "Validator OK."
else
	echo "Validator Failed."
	exit 1
fi

echo "Done."

echo ""
echo "The problem solution searching..."

answer=answer.txt
g++ -std=c++17 -o solver -Wall -O3 $1
./solver < $dist_matrix > $answer

if [ $? -eq 0 ]; then
	echo "Checker OK."
else
	echo "Checker Failed."
	exit 1
fi

echo "Solution founded!"
