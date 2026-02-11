################################
# Makefile
#
# author: Wei Yu (based on He Zhang's code)
# edited by: 08/2024
################################

CC=g++
DEPS=src/main.h src/PairConstraints.h src/PairConstraints.cpp src/Utils/energy_parameter.h src/Utils/feature_weight.h src/Utils/intl11.h src/Utils/intl21.h src/Utils/intl22.h src/Utils/utility_v.h src/Utils/utility.h src/Sampling.cpp src/LinearPartition.cpp src/LinearPartition.h src/bpp.cpp
OPENMP_FLAGS=$(shell echo | $(CC) -fopenmp -dM -E - >/dev/null 2>&1 && echo -fopenmp)
CFLAGS=-std=c++17 -O3 $(OPENMP_FLAGS)
.PHONY : clean main
objects=bin/main

main: src/main.cpp $(DEPS) 
		chmod +x main
		mkdir -p bin
		$(CC) src/main.cpp src/PairConstraints.cpp $(CFLAGS) -Dlpv -DSPECIAL_HP -o bin/main

# for testing purposes
test: src/main.cpp $(DEPS) 
		chmod +x main
		mkdir -p bin
		$(CC) src/main.cpp src/PairConstraints.cpp $(CFLAGS) -Dlv -Dlpv -DSPECIAL_HP -o bin/main_test

clean:
	-rm $(objects)
