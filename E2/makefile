#makefile for LSN exercises 2.*
#gilberto.nardi@studenti.unimi.it

CC = g++

all: RW Integrals

RW: RW.o random.o;\
  $(CC) $^ -o $@

RW.o: RW.cpp random.h;\
  $(CC) $< -c

Integrals: Integrals.o IntegralMC.o random.o;\
  $(CC) $^ -o $@

Integrals.o: Integrals.cpp IntegralMC.h Funzioni.h;\
  $(CC) $< -c

IntegralMC.o: IntegralMC.cpp random.h;\
	$(CC) $< -c

clean:;\
  rm *.o
