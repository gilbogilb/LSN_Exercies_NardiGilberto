###################################
#makefile for Exercises 04.*
#april 2021
#gilberto.nardi@studenti.unimi.it
###################################

CC = g++

all: MolDyn_NVE.exe 

MolDyn_NVE.exe: MolDyn_NVE.o DataBlocks.o;\
  $(CC) $^ -o $@

MolDyn_NVE.o: MolDyn_NVE.cpp DataBlocks.h;\
  $(CC) $< -c 

clean: ;\
  rm *.o