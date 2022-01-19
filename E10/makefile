CC = g++
PARALLELCC = mpicxx

all: mainSA mainPGA

mainSA: mainSA.o random.o;\
  $(CC) $^ -o $@

mainSA.o: mainSA.cpp random.h tsp.h;\
  $(CC) $< -c

mainPGA: mainPGA.o random.o;\
  $(PARALLELCC) $^ -o $@

mainPGA.o: mainPGA.cpp random.h proc_tsp.h;\
  $(PARALLELCC) $< -c

clean:;\
  rm *.o