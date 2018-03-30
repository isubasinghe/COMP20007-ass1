# # # # # # #
# Makefile for assignment 1
#
# created Mar 2018
# Matt Farrugia <matt.farrugia@unimelb.edu.au>
#

CC     = gcc
# Added the -g flag since we need debugging symbols for assert to work.
# O2 since O2 will likey be faster than O3 in the conditions given.
# std=c99 since for(int i) style is used.
# Others for being very picky about errors.
CFLAGS = -Wall -Werror -pedantic -std=c99 -g -O2
EXE    = a1
OBJ    = main.o query.o index.o list.o heap.o
#				add any new object files here ^

# top (default) target
all: $(EXE)

# how to link executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# other dependencies
main.o: query.h index.h
query.o: query.h index.h list.h heap.h
index.o: index.h list.h
list.o: list.h
heap.o: heap.h

# ^ add any new dependencies here

# phony targets (do not represent actual files)
.PHONY: clean cleanly all CLEAN
# `make clean` to remove all object files
# `make CLEAN` to remove all object and executable files
# `make cleanly` to `make` then immediately remove object files (inefficient)
clean:
	rm -f $(OBJ)
CLEAN: clean
	rm -f $(EXE)
cleanly: all clean
