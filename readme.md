# This is a research project which we investigate the split into 3 alliances of African countries.

[africa_cins.csv](africa_cins.csv) contains all CINS and IOC data

[dist_cepii.xls](dist_cepii.xls) constains CommonColonizer, GeodesicDistance, contiguity info

\*\_solver.cpp is problem solvers

[statements_for_cpp_solvers.pdf](statements_for_cpp_solvers.pdf) contains the problem statement, input and output formats for solvers

[gen_input.py](gen_input.py) generate matrix data from africa_cins and dist_cepii to meet the conditions of solvers

[validator.cpp](validator.cpp) checks that matrrix_data is correct

[checker.cpp](checker.cpp) -matrix_data -answer check that it's solver's solution is correct

[runner.sh](runner.sh) -\*\_solver.cpp create data_matrix, run solver and checked that all data is correct

[answer.txt](answer.txt) is a conqueror contries into 3 alliances
