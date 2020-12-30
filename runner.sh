#!/bin/bash

if [ $# -eq 0 ]
then
	echo "To run script write:"
	echo "./runner.sh solvers/local_optimization_solver.cpp"
	exit 1
fi

dist_matrix=dist_matrix.txt

echo "Generate dist_matrix..."
python "./data/gen_dist_matrix.py" > $dist_matrix

g++ -std=c++17 -o checks/validator -Wall checks/validator.cpp
if [ $? -ne 0 ]; then
	exit 1
fi

./checks/validator < $dist_matrix
if [ $? -eq 0 ]; then
	rm checks/validator
	echo "Validator OK."
else
	rm checks/validator
	echo "Validator Failed."
	exit 1
fi

echo "Done."

echo ""
echo "The problem solution searching..."

answer=answer.txt
g++ -std=c++17 -o solvers/solver -Wall -O3 $1
if [ $? -ne 0 ]; then
	exit 1
fi

./solvers/solver < $dist_matrix > $answer
rm solvers/solver

g++ -std=c++17 -o checks/checker -Wall checks/checker.cpp 
if [ $? -ne 0 ]; then
	exit 1
fi

./checks/checker $dist_matrix $answer
if [ $? -eq 0 ]; then
	rm ./checks/checker
	echo "Checker OK."
else
	rm ./checks/checker
	echo "Checker Failed."
	exit 1
fi

echo "Solution founded!"

if [ "$2" == "-v" ] || [ "$2" == "--v" ]
then
	echo ""
	echo "Start visualisation..."
	./visualisation.sh
	echo "Done."
fi

