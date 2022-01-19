#makefile for LSN exercises 2.*
#gilberto.nardi@studenti.unimi.it

CC = g++

all: RW_simulation Integrals

RW_simulation: RW_simulation.o random.o;\
  $(CC) $^ -o $@

RW_simulation.o: RW_simulation.cpp random.h RW.h;\
  $(CC) $< -c

Integrals: Integrals.o IntegralMC.o random.o;\
  $(CC) $^ -o $@

Integrals.o: Integrals.cpp IntegralMC.h Funzioni.h random.h;\
  $(CC) $< -c

IntegralMC.o: IntegralMC.cpp random.h;\
	$(CC) $< -c

clean:;\
  rm *.o
